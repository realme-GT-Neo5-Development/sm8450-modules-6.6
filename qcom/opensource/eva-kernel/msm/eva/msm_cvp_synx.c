// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2020-2021, The Linux Foundation. All rights reserved.
 */

#include "msm_cvp_common.h"
#include "cvp_hfi_api.h"
#include "msm_cvp_debug.h"
#include "msm_cvp_core.h"
#include "msm_cvp_dsp.h"

#ifdef CVP_SYNX_ENABLED
int cvp_sess_init_synx(struct msm_cvp_inst *inst)
{
	/*
	 * synx v2 (the synx-kernel techpack on 6.6) returns the session as a
	 * pointer and requires a client ID, as in Qualcomm's 6.6 driver.
	 */
	struct synx_initialization_params params = { 0 };

	params.name = "cvp-kernel-client";
	params.id = SYNX_CLIENT_EVA_CTX0;
	inst->synx_session_id = synx_initialize(&params);
	if (IS_ERR_OR_NULL(inst->synx_session_id)) {
		dprintk(CVP_ERR, "%s synx_initialize failed\n", __func__);
		inst->synx_session_id = NULL;
		return -EFAULT;
	}

	return 0;
}

int cvp_sess_deinit_synx(struct msm_cvp_inst *inst)
{
	if (!inst) {
		dprintk(CVP_ERR, "Used invalid sess in deinit_synx\n");
		return -EINVAL;
	}
	synx_uninitialize(inst->synx_session_id);
	return 0;
}

void cvp_dump_fence_queue(struct msm_cvp_inst *inst)
{
	struct cvp_fence_queue *q;
	struct cvp_fence_command *f;
	struct synx_session *ssid;
	int i;

	q = &inst->fence_cmd_queue;
	ssid = inst->synx_session_id;
	mutex_lock(&q->lock);
	dprintk(CVP_WARN, "inst %x fence q mode %d, ssid %pK\n",
			hash32_ptr(inst->session), q->mode, ssid);

	dprintk(CVP_WARN, "fence cmdq wait list:\n");
	list_for_each_entry(f, &q->wait_list, list) {
		dprintk(CVP_WARN, "frame pkt type 0x%x\n", f->pkt->packet_type);
		for (i = 0; i < f->output_index; i++)
			dprintk(CVP_WARN, "idx %d client hdl %d, state %d\n",
				i, f->synx[i],
				synx_get_status(ssid, f->synx[i]));

	}

	dprintk(CVP_WARN, "fence cmdq schedule list:\n");
	list_for_each_entry(f, &q->sched_list, list) {
		dprintk(CVP_WARN, "frame pkt type 0x%x\n", f->pkt->packet_type);
		for (i = 0; i < f->output_index; i++)
			dprintk(CVP_WARN, "idx %d client hdl %d, state %d\n",
				i, f->synx[i],
				synx_get_status(ssid, f->synx[i]));

	}
	mutex_unlock(&q->lock);
}

int cvp_import_synx(struct msm_cvp_inst *inst, struct cvp_fence_command *fc,
		u32 *fence)
{
	int rc = 0, rr = 0;
	int i;
	struct cvp_fence_type *fs;
	struct synx_import_params params;
	s32 h_synx;
	struct synx_session *ssid;

	if (fc->signature != 0xFEEDFACE) {
		dprintk(CVP_ERR, "%s Deprecated synx path\n", __func__);
		return -EINVAL;
	}

	fs = (struct cvp_fence_type *)fence;
	ssid = inst->synx_session_id;

	for (i = 0; i < fc->num_fences; ++i) {
		h_synx = fs[i].h_synx;

		if (h_synx) {
			/*
			 * synx v2 reworked synx_import: instead of the
			 * {h_synx, secure_key} pair it takes a union with an
			 * individual variant and flags; local and global
			 * handles are distinguished by flags. Same layout as
			 * Qualcomm's 6.6 driver.
			 *
			 * TODO: fs[i].secure_key from the 5.10 UAPI is no
			 * longer used; verify fence import with senna's libcvp.
			 */
			params.type = SYNX_IMPORT_INDV_PARAMS;
			params.indv.fence = &h_synx;
			params.indv.flags = SYNX_IMPORT_SYNX_FENCE
					| SYNX_IMPORT_LOCAL_FENCE;
			params.indv.new_h_synx = &fc->synx[i];

			rc = synx_import(ssid, &params);
			if (rc) {
				dprintk(CVP_ERR,
					"%s: %d synx_import failed\n",
					__func__, h_synx);
				rr = rc;
			}
		}
	}

	return rr;
}

int cvp_release_synx(struct msm_cvp_inst *inst, struct cvp_fence_command *fc)
{
	int rc = 0;
	int i;
	s32 h_synx;
	struct synx_session *ssid;

	if (fc->signature != 0xFEEDFACE) {
		dprintk(CVP_ERR, "%s deprecated synx_path\n", __func__);
		return -EINVAL;
	}

	ssid = inst->synx_session_id;
	for (i = 0; i < fc->num_fences; ++i) {
		h_synx = fc->synx[i];
		if (h_synx) {
			rc = synx_release(ssid, h_synx);
			if (rc)
				dprintk(CVP_ERR,
				"%s: synx_release %d, %d failed\n",
				__func__, h_synx, i);
		}
	}
	return rc;
}

static int cvp_cancel_synx_impl(struct msm_cvp_inst *inst,
			enum cvp_synx_type type,
			struct cvp_fence_command *fc,
			int synx_state)
{
	int rc = 0;
	int i;
	int h_synx;
	struct synx_session *ssid;
	int start = 0, end = 0;

	ssid = inst->synx_session_id;

	if (type == CVP_INPUT_SYNX) {
		start = 0;
		end = fc->output_index;
	} else if (type == CVP_OUTPUT_SYNX) {
		start = fc->output_index;
		end = fc->num_fences;
	} else {
		dprintk(CVP_ERR, "%s Incorrect synx type\n", __func__);
		return -EINVAL;
	}

	for (i = start; i < end; ++i) {
		h_synx = fc->synx[i];
		if (h_synx) {
			rc = synx_signal(ssid, h_synx, synx_state);
			dprintk(CVP_SYNX, "Cancel synx %d session %pK\n",
					h_synx, inst);
			if (rc)
				dprintk(CVP_ERR,
					"%s: synx_signal %d %d %d failed\n",
				__func__, h_synx, i, synx_state);
		}
	}

	return rc;


}

int cvp_cancel_synx(struct msm_cvp_inst *inst, enum cvp_synx_type type,
		struct cvp_fence_command *fc, int synx_state)
{
	if (fc->signature != 0xFEEDFACE) {
		dprintk(CVP_ERR, "%s deprecated synx path\n", __func__);
			return -EINVAL;
		}

	return cvp_cancel_synx_impl(inst, type, fc, synx_state);
}

static int cvp_wait_synx(struct synx_session *ssid, u32 *synx, u32 num_synx,
		u32 *synx_state)
{
	int i = 0, rc = 0;
	unsigned long timeout_ms = 2000;
	int h_synx;

	while (i < num_synx) {
		h_synx = synx[i];
		if (h_synx) {
			rc = synx_wait(ssid, h_synx, timeout_ms);
			if (rc) {
				*synx_state = synx_get_status(ssid, h_synx);
				/*
				 * synx v2 may return non-zero from synx_wait()
				 * even though the fence was signaled successfully
				 * (state SYNX_STATE_SIGNALED_SUCCESS), so check the
				 * state as well, as Qualcomm's 6.6 driver does.
				 */
				if (*synx_state == SYNX_STATE_SIGNALED_SUCCESS) {
					dprintk(CVP_SYNX,
					"%s: synx_wait %d signaled success\n",
					current->comm, i);
					rc = 0;
					++i;
					continue;
				}
				if (*synx_state == SYNX_STATE_SIGNALED_CANCEL) {
					dprintk(CVP_SYNX,
					"%s: synx_wait %d cancel %d state %d\n",
					current->comm, i, rc, *synx_state);
				} else {
					dprintk(CVP_ERR,
					"%s: synx_wait %d failed %d state %d\n",
					current->comm, i, rc, *synx_state);
					/*
					 * Not SYNX_STATE_SIGNALED_ERROR (3): synx v2
					 * only accepts SUCCESS (2), CANCEL (4) or a
					 * value above SYNX_STATE_SIGNALED_MAX (64) and
					 * rejects 3 with "signaling with wrong status".
					 * Qualcomm's 6.6 driver uses CANCEL here too.
					 */
					*synx_state = SYNX_STATE_SIGNALED_CANCEL;
				}
				return rc;
			}
			dprintk(CVP_SYNX, "Wait synx %d returned succes\n",
					h_synx);
		}
		++i;
	}
	return rc;
}

static int cvp_signal_synx(struct synx_session *ssid, u32 *synx, u32 num_synx,
		u32 synx_state)
{
	int i = 0, rc = 0;
	int h_synx;

	while (i < num_synx) {
		h_synx = synx[i];
		if (h_synx) {
			rc = synx_signal(ssid, h_synx, synx_state);
			if (rc) {
				dprintk(CVP_ERR,
					"%s: synx_signal %d %d failed\n",
					current->comm, h_synx, i);
				/* as above - v2 rejects ERROR(3); the Qualcomm 6.6 driver uses CANCEL too */
				synx_state = SYNX_STATE_SIGNALED_CANCEL;
			}
			dprintk(CVP_SYNX, "Signaled synx %d\n", h_synx);
		}
		++i;
	}
	return rc;
}

int cvp_synx_ops(struct msm_cvp_inst *inst, enum cvp_synx_type type,
		struct cvp_fence_command *fc, u32 *synx_state)
{
	struct synx_session *ssid;

	ssid = inst->synx_session_id;

	if (fc->signature != 0xFEEDFACE) {
		dprintk(CVP_ERR, "%s deprecated synx, type %d\n", __func__, type);
				return -EINVAL;
	}

	if (type == CVP_INPUT_SYNX) {
		return cvp_wait_synx(ssid, fc->synx, fc->output_index,
				synx_state);
	} else if (type == CVP_OUTPUT_SYNX) {
		return cvp_signal_synx(ssid, &fc->synx[fc->output_index],
				(fc->num_fences - fc->output_index),
				*synx_state);
	} else {
		dprintk(CVP_ERR, "%s Incorrect SYNX type\n", __func__);
		return -EINVAL;
	}
}
#endif
