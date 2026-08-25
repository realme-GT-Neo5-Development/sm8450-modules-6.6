// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (C) 2023-2026 Oplus. All rights reserved.
 */

#include "oplus_chg_ic_cfg.h"

static const char * const oplus_chg_ic_type_text[] = {
	[OPLUS_CHG_IC_BUCK] = "buck",
	[OPLUS_CHG_IC_BOOST] = "boost",
	[OPLUS_CHG_IC_BUCK_BOOST] = "buck&boost",
	[OPLUS_CHG_IC_CP_DIV2] = "cp_div2",
	[OPLUS_CHG_IC_CP_MUL2] = "cp_mul2",
	[OPLUS_CHG_IC_CP_TW2] = "cp_tw2",
	[OPLUS_CHG_IC_RX] = "wireless_rx",
	[OPLUS_CHG_IC_VIRTUAL_RX] = "virtual_rx",
	[OPLUS_CHG_IC_VIRTUAL_BUCK] = "virtual_buck",
	[OPLUS_CHG_IC_VIRTUAL_CP] = "virtual_cp",
	[OPLUS_CHG_IC_VIRTUAL_USB] = "virtual_usb",
	[OPLUS_CHG_IC_TYPEC] = "typec",
	[OPLUS_CHG_IC_GAUGE] = "gauge",
	[OPLUS_CHG_IC_VIRTUAL_GAUGE] = "virtual_gauge",
	[OPLUS_CHG_IC_ASIC] = "asic",
	[OPLUS_CHG_IC_VIRTUAL_ASIC] = "virtual_asic",
	[OPLUS_CHG_IC_VPHY] = "voocphy",
	[OPLUS_CHG_IC_VIRTUAL_VPHY] = "virtual_voocphy",
	[OPLUS_CHG_IC_SWITCH] = "switch",
	[OPLUS_CHG_IC_VIRTUAL_SWITCH] = "virtual_switch",
	[OPLUS_CHG_IC_CP] = "cp",
	[OPLUS_CHG_IC_VIRTUAL_UFCS] = "virtual_ufcs",
	[OPLUS_CHG_IC_MISC] = "misc",
	[OPLUS_CHG_IC_PPS] = "pps",
	[OPLUS_CHG_IC_VIRTUAL_PPS] = "virtual_pps",
	[OPLUS_CHG_IC_UFCS] = "ufcs",
	[OPLUS_CHG_IC_BATT_BAL] = "batt_bal",
	[OPLUS_CHG_IC_VIRTUAL_BATT_BAL] = "virtual batt_bal",
	[OPLUS_CHG_IC_LEVEL_SHIFT] = "level_shift",
	[OPLUS_CHG_IC_VIRTUAL_LEVEL_SHIFT] = "virtual level_shift",
};

const char *oplus_chg_ic_type_str(enum oplus_chg_ic_type id)
{
	if ((id < 0) || (id > 29))
		return "Invalid";
	return oplus_chg_ic_type_text[id];
}

static const char * const oplus_chg_ic_connect_type_text[] = {
	[OPLUS_CHG_IC_CONNECT_PARALLEL] = "NULL",
	[OPLUS_CHG_IC_CONNECT_SERIAL] = "NULL",
};

const char *oplus_chg_ic_connect_type_str(enum oplus_chg_ic_connect_type id)
{
	if ((id < 0) || (id > 1))
		return "Invalid";
	return oplus_chg_ic_connect_type_text[id];
}

static const char * const oplus_chg_ic_virq_id_text[] = {
	[OPLUS_IC_VIRQ_ERR] = "error",
	[OPLUS_IC_VIRQ_CC_DETECT] = "cc_detect",
	[OPLUS_IC_VIRQ_PLUGIN] = "plugin",
	[OPLUS_IC_VIRQ_CC_CHANGED] = "cc_changed",
	[OPLUS_IC_VIRQ_VOOC_DATA] = "vooc_data",
	[OPLUS_IC_VIRQ_SUSPEND_CHECK] = "suspend_check",
	[OPLUS_IC_VIRQ_CHG_TYPE_CHANGE] = "chg_type_change",
	[OPLUS_IC_VIRQ_OFFLINE] = "offline",
	[OPLUS_IC_VIRQ_RESUME] = "resume",
	[OPLUS_IC_VIRQ_SVID] = "svid",
	[OPLUS_IC_VIRQ_OTG_ENABLE] = "svid",
	[OPLUS_IC_VIRQ_VOLTAGE_CHANGED] = "voltage_change",
	[OPLUS_IC_VIRQ_CURRENT_CHANGED] = "current_change",
	[OPLUS_IC_VIRQ_BC12_COMPLETED] = "bc12_completed",
	[OPLUS_IC_VIRQ_DATA_ROLE_CHANGED] = "data_role_changed",
	[OPLUS_IC_VIRQ_ONLINE] = "online",
	[OPLUS_IC_VIRQ_TYPEC_STATE] = "typec_state",
	[OPLUS_IC_VIRQ_HARD_RESET] = "hard_reset",
	[OPLUS_IC_VIRQ_POWER_CHANGED] = "power_changed",
	[OPLUS_IC_VIRQ_PRESENT] = "present",
	[OPLUS_IC_VIRQ_EVENT_CHANGED] = "event_changed",
	[OPLUS_IC_VIRQ_BTB_STATE_CHANGE] = "btb_state_changed",
	[OPLUS_IC_VIRQ_FPGA_RST] = "FPGA_RST",
	[OPLUS_IC_VIRQ_PD_COMPLETED] = "pd_completed",
	[OPLUS_IC_VIRQ_HMAC_UPDATE] = "hmac_update",
};

const char *oplus_chg_ic_virq_id_str(enum oplus_chg_ic_virq_id id)
{
	if ((id < 0) || (id > 24))
		return "Invalid";
	return oplus_chg_ic_virq_id_text[id];
}

static const char * const oplus_chg_ic_err_text[] = {
	[OPLUS_IC_ERR_UNKNOWN] = "Unknown",
	[OPLUS_IC_ERR_I2C] = "I2C",
	[OPLUS_IC_ERR_GPIO] = "GPIO",
	[OPLUS_IC_ERR_PLAT_PMIC] = "PlatformPMIC",
	[OPLUS_IC_ERR_BUCK_BOOST] = "Buck/Boost",
	[OPLUS_IC_ERR_GAUGE] = "Gauge",
	[OPLUS_IC_ERR_WLS_RX] = "WirelessRX",
	[OPLUS_IC_ERR_CP] = "ChargePump",
	[OPLUS_IC_ERR_CC_LOGIC] = "CCLogic",
	[OPLUS_IC_ERR_PARALLEL_UNBALANCE] = "ParallelUnbalance",
	[OPLUS_IC_ERR_MOS_ERROR] = "MosError",
	[OPLUS_IC_ERR_OFFLINE] = "Offline",
	[OPLUS_IC_ERR_UFCS] = "UFCS",
	[OPLUS_IC_ERR_GAN_MOS_ERROR] = "GanMosError",
	[OPLUS_IC_ERR_BATT_ID] = "BATTID",
	[OPLUS_IC_ERR_NTC] = "NTC",
	[OPLUS_IC_ERR_BATT_BAL] = "BATT_BAL",
	[OPLUS_IC_ERR_FPGA] = "FPGA_RST",
	[OPLUS_IC_ERR_BURN] = "BURN",
};

const char *oplus_chg_ic_err_str(enum oplus_chg_ic_err id)
{
	if ((id < 0) || (id > 18))
		return "Invalid";
	return oplus_chg_ic_err_text[id];
}

static const char * const oplus_chg_ic_plat_pmic_err_text[] = {
	[PLAT_PMIC_ERR_UNKNOWN] = "NULL",
	[PLAT_PMIC_ERR_VCONN_OVP] = "NULL",
	[PLAT_PMIC_ERR_VCONN_UVP] = "NULL",
	[PLAT_PMIC_ERR_VCONN_RVP] = "NULL",
	[PLAT_PMIC_ERR_VCONN_OCP] = "NULL",
	[PLAT_PMIC_ERR_VCONN_OPEN] = "NULL",
	[PLAT_PMIC_ERR_VCONN_CLOSE] = "NULL",
	[PLAT_PMIC_ERR_VBUS_ABNORMAL] = "NULL",
};

const char *oplus_chg_ic_plat_pmic_err_str(enum oplus_chg_ic_plat_pmic_err id)
{
	if ((id < 0) || (id > 7))
		return "Invalid";
	return oplus_chg_ic_plat_pmic_err_text[id];
}

static const char * const oplus_chg_track_mos_device_error_text[] = {
	[TRACK_MOS_ERR_DEFAULT] = "NULL",
	[TRACK_MOS_SOC_NOT_FULL] = "NULL",
	[TRACK_MOS_SOC_GAP_TOO_BIG] = "NULL",
	[TRACK_MOS_CURRENT_UNBALANCE] = "NULL",
	[TRACK_MOS_I2C_ERROR] = "NULL",
	[TRACK_MOS_OPEN_ERROR] = "NULL",
	[TRACK_MOS_VBAT_GAP_BIG] = "NULL",
};

const char *oplus_chg_track_mos_device_error_str(enum oplus_chg_track_mos_device_error id)
{
	if ((id < 0) || (id > 6))
		return "Invalid";
	return oplus_chg_track_mos_device_error_text[id];
}

static const char * const oplus_chg_ic_ufcs_err_text[] = {
	[UFCS_ERR_READ] = "NULL",
	[UFCS_ERR_WRITE] = "NULL",
	[UFCS_ERR_REG_DUMP] = "NULL",
};

const char *oplus_chg_ic_ufcs_err_str(enum oplus_chg_ic_ufcs_err id)
{
	if ((id < 0) || (id > 2))
		return "Invalid";
	return oplus_chg_ic_ufcs_err_text[id];
}

static const char * const oplus_chg_ic_gpio_status_text[] = {
	[GPIO_STATUS_NC] = "NULL",
	[GPIO_STATUS_PD] = "NULL",
	[GPIO_STATUS_PU] = "NULL",
	[GPIO_STATUS_NOT_SUPPORT] = "NULL",
};

const char *oplus_chg_ic_gpio_status_str(enum oplus_chg_ic_gpio_status id)
{
	if ((id < 0) || (id > 3))
		return "Invalid";
	return oplus_chg_ic_gpio_status_text[id];
}

static const char * const oplus_chg_track_gague_device_error_text[] = {
	[TRACK_GAGUE_ERR_DEFAULT] = "default",
	[TRACK_GAGUE_ERR_SEAL] = "seal_fail",
	[TRACK_GAGUE_ERR_UNSEAL] = "unseal_fail",
	[TRACK_GAGUE_GENERAL_INFO] = "general_info",
	[TRACK_GAGUE_ERR_RSOC_JUMP] = "rsoc_jump",
	[TRACK_GAGUE_ERR_VOLT_SOC_NOT_MATCH] = "volt_soc_not_match",
	[TRACK_GAGUE_ERR_QMAX] = "qmax_err",
	[TRACK_GAGUE_ERR_FCC] = "fcc_err",
	[TRACK_GAGUE_ERR_RSOC_SMOOTH] = "rsoc_smooth_err",
	[TRACK_GAGUE_ERR_TEMP] = "temp_err",
	[TRACK_GAGUE_ERR_SOH_JUMP] = "soh_jump",
	[TRACK_GAGUE_ERR_CC_JUMP] = "cc_jump",
	[TRACK_GAGUE_SOC_1_PCT_INFO] = "soc1_info",
	[TRACK_GAGUE_ERR_SINGLE_DISCHG_TERM_VOLT] = "single_dichg_term_volt",
	[TRACK_GAGUE_ERR_MULTIPLE_DISCHG_TERM_VOLT] = "multiple_dichg_term_volt",
	[TRACK_GAGUE_ERR_CC_TERM_VOLT] = "cc_term_volt",
	[TRACK_GAGUE_ERR_BELOW_FIRMWARE_TERM_VOLT] = "below_firmware_term_volt",
	[TRACK_GAGUE_ERR_LIFETIME_OVER] = "lifetime_over",
	[TRACK_GAGUE_TERM_VOLT_OK] = "term_volt_ok",
	[TRACK_GAGUE_LIFETIME_INFO] = "lifetime_info",
	[TRACK_GAGUE_MTK_CALI_INFO] = "mtk_cali_info",
	[TRACK_GAGUE_ERR_SUB_BTB_CONNECT] = "batt_sub_btb",
	[TRACK_GAGUE_BATT_MONITOR_BY_SOC] = "batt_monitor_by_soc",
	[TRACK_GAGUE_BATT_MONITOR_BY_TIME] = "batt_monitor_by_time",
	[TRACK_GAGUE_QCOM_CALI_INFO] = "qcom_cali_info",
	[TRACK_GAGUE_ERR_MAX] = "unknown_err",
};

const char *oplus_chg_track_gague_device_error_str(enum oplus_chg_track_gague_device_error id)
{
	if ((id < 0) || (id > 25))
		return "Invalid";
	return oplus_chg_track_gague_device_error_text[id];
}

static const char * const oplus_chg_spec_version_text[] = {
	[OPLUS_CHG_SPEC_VER_UNKNOW] = "NULL",
	[OPLUS_CHG_SPEC_VER_V3P6] = "NULL",
	[OPLUS_CHG_SPEC_VER_V3P7] = "NULL",
	[OPLUS_CHG_SPEC_VER_MAX] = "NULL",
};

const char *oplus_chg_spec_version_str(enum oplus_chg_spec_version id)
{
	if ((id < 0) || (id > 3))
		return "Invalid";
	return oplus_chg_spec_version_text[id];
}

static const char * const oplus_chg_sili_alg_cfg_type_text[] = {
	[SILI_OCV_HYSTERESIS] = "NULL",
	[SILI_OCV_AGING_OFFSET] = "NULL",
	[SILI_DYNAMIC_DSG_CTRL] = "NULL",
	[SILI_STATIC_DSG_CTRL] = "NULL",
	[SILI_MONITOR_MODE] = "NULL",
	[SILI_CFG_TYPE_MAX] = "NULL",
};

const char *oplus_chg_sili_alg_cfg_type_str(enum oplus_chg_sili_alg_cfg_type id)
{
	if ((id < 0) || (id > 5))
		return "Invalid";
	return oplus_chg_sili_alg_cfg_type_text[id];
}

static const char * const oplus_region_list_index_text[] = {
	[ECO_DESIGN_SUPPORT_REGION] = "oplus,eco_region_list",
	[COMMON_CHG_SUPPORT_REGION] = "oplus,common_chg_region_list",
	[REGION_INDEX_MAX] = "NA",
};

const char *oplus_region_list_index_str(enum oplus_region_list_index id)
{
	if ((id < 0) || (id > 2))
		return "Invalid";
	return oplus_region_list_index_text[id];
}

static const char * const endurance_exit_reason_text[] = {
	[ENDURANCE_EXIT_SHUTDOWN] = "shutdown",
	[ENDURANCE_EXIT_CHARGING] = "charging",
	[ENDURANCE_EXIT_USER] = "user",
};

const char *endurance_exit_reason_str(enum endurance_exit_reason id)
{
	if ((id < 0) || (id > 2))
		return "Invalid";
	return endurance_exit_reason_text[id];
}

static const char * const vooc_frame_head_text[] = {
	[VOOC_FRAME_HEAD_VOOC20] = "vooc2.0",
	[VOOC_FRAME_HEAD_VOOC30] = "vooc3.0",
	[VOOC_FRAME_HEAD_SVOOC] = "svooc",
	[VOOC_FRAME_HEAD_MAX] = "unknown",
};

const char *vooc_frame_head_str(enum vooc_frame_head id)
{
	if ((id < 0) || (id > 3))
		return "Invalid";
	return vooc_frame_head_text[id];
}

static const char * const track_not_record_reason_text[] = {
	[NOT_RECORD_ENGINEER] = "dis808",
	[NOT_RECORD_SAFETY] = "user_disable",
	[NOT_RECORD_MMI] = "mmi",
	[NOT_RECORD_SLOW_CHG] = "slow_chg",
	[NOT_RECORD_PLC] = "plc",
	[NOT_RECORD_MAX] = "unknown",
};

const char *track_not_record_reason_str(enum track_not_record_reason id)
{
	if ((id < 0) || (id > 5))
		return "Invalid";
	return track_not_record_reason_text[id];
}

static const char * const batt_bal_ic_exit_reason_text[] = {
	[BATT_BAL_ERR_UNKNOW] = "unknow",
	[BATT_BAL_ERR_B1_OVP] = "b1_ovp",
	[BATT_BAL_ERR_B2_OVP] = "b2_ovp",
	[BATT_BAL_ERR_OT_WARM] = "ot_warm",
	[BATT_BAL_ERR_OT] = "ot",
	[BATT_BAL_ERR_B1_UV] = "b1_uv",
	[BATT_BAL_ERR_B2_UV] = "b2_uv",
	[BATT_BAL_ERR_L1_PEAK_CURR_LIMIT] = "l1_peak_curr_limit",
	[BATT_BAL_ERR_L2_PEAK_CURR_LIMIT] = "l2_peak_curr_limit",
	[BATT_BAL_ERR_WDG_TIMEOUT] = "wdg_timeout",
};

const char *batt_bal_ic_exit_reason_str(enum batt_bal_ic_exit_reason id)
{
	if ((id < 0) || (id > 9))
		return "Invalid";
	return batt_bal_ic_exit_reason_text[id];
}

static const char * const plc_enable_status_text[] = {
	[PLC_STATUS_NOT_SUPPORT] = "not_support",
	[PLC_STATUS_NOT_ALLOW] = "not_allow",
	[PLC_STATUS_DISABLE] = "disable",
	[PLC_STATUS_ENABLE] = "enable",
	[PLC_STATUS_WAIT] = "wait",
	[PLC_STATUS_MAX] = "unknown",
};

const char *plc_enable_status_str(enum plc_enable_status id)
{
	if ((id < 0) || (id > 5))
		return "Invalid";
	return plc_enable_status_text[id];
}

static const char * const sec_ic_err_text[] = {
	[SEC_IC_ERR_ECDSA_FAIL] = "ecdsa_fail",
	[SEC_IC_ERR_ECW_FAIL] = "ecw_fail",
	[SEC_IC_ERR_MEM_R_FAIL] = "mem_read_fail",
	[SEC_IC_ERR_MEM_W_FAIL] = "mem_write_fail",
	[SEC_IC_ERR_ROMID_FAIL] = "romid_fail",
	[SEC_IC_ERR_I2C] = "i2c_fail",
	[SEC_IC_MEM_REC] = "mem_rec",
	[SEC_IC_ERR_UNKNOW] = "unknow",
};

const char *sec_ic_err_str(enum sec_ic_err id)
{
	if ((id < 0) || (id > 7))
		return "Invalid";
	return sec_ic_err_text[id];
}

static const char * const track_cp_device_error_text[] = {
	[TRACK_CP_ERR_DEFAULT] = "err_cp_default",
	[TRACK_CP_ERR_NO_WORK] = "err_cp_no_work",
	[TRACK_CP_ERR_TSD] = "err_cp_tsd",
	[TRACK_CP_ERR_SS_TIMEOUT] = "err_cp_ss_timeout",
	[TRACK_CP_ERR_DIAG_FAIL] = "err_cp_pin_diag_fail",
	[TRACK_CP_ERR_WD_TIMEOUT] = "err_cp_wdt_timeout",
	[TRACK_CP_ERR_PMID2OUT_UVP] = "err_cp_pmidtout_uvp",
	[TRACK_CP_ERR_PMID2OUT_OVP] = "err_cp_pmidtout_ovp",
	[TRACK_CP_ERR_VOUT_OVP] = "err_cp_vout_ovp",
	[TRACK_CP_ERR_VBAT_OVP] = "err_cp_vbat_ovp",
	[TRACK_CP_ERR_IBAT_OCP] = "err_cp_ibat_ocp",
	[TRACK_CP_ERR_VBUS_OVP] = "err_cp_vbus_ovp",
	[TRACK_CP_ERR_IBUS_OCP] = "err_cp_ibus_ocp",
	[TRACK_CP_ERR_CP_EN_FAIL] = "err_cp_en_fail",
};

const char *track_cp_device_error_str(enum track_cp_device_error id)
{
	if ((id < 0) || (id > 13))
		return "Invalid";
	return track_cp_device_error_text[id];
}

static const char * const track_ufcs_sw_error_text[] = {
	[TRACK_UFCS_ERR_DEFAULT] = "ufcs_default",
	[TRACK_UFCS_ERR_IBUS_LIMIT] = "ibus_limit",
	[TRACK_UFCS_ERR_CP_ENABLE] = "cp_enable",
	[TRACK_UFCS_ERR_R_COOLDOWN] = "r_cooldown",
	[TRACK_UFCS_ERR_BATT_BTB_COOLDOWN] = "batbtb_cooldown",
	[TRACK_UFCS_ERR_IBAT_OVER] = "ibat_over",
	[TRACK_UFCS_ERR_BTB_OVER] = "btb_over",
	[TRACK_UFCS_ERR_MOS_OVER] = "mos_over",
	[TRACK_UFCS_ERR_USBTEMP_OVER] = "usbtemp_over",
	[TRACK_UFCS_ERR_TFG_OVER] = "tfg_over",
	[TRACK_UFCS_ERR_VBAT_DIFF] = "vbat_diff",
	[TRACK_UFCS_ERR_STARTUP_FAIL] = "startup_fail",
	[TRACK_UFCS_ERR_CIRCUIT_SWITCH] = "circuit_switch",
	[TRACK_UFCS_ERR_AUTHER_ERR] = "auther_err",
	[TRACK_UFCS_ERR_PDO_ERR] = "pdo_err",
};

const char *track_ufcs_sw_error_str(enum track_ufcs_sw_error id)
{
	if ((id < 0) || (id > 14))
		return "Invalid";
	return track_ufcs_sw_error_text[id];
}

static const char * const track_get_version_text[] = {
	[TRACK_VER_3_4] = "3.4",
	[TRACK_VER_4_0] = "4.0",
	[TRACK_VER_MAX] = "100.100",
};

const char *track_get_version_str(enum track_get_version id)
{
	if ((id < 0) || (id > 2))
		return "Invalid";
	return track_get_version_text[id];
}

static const char * const oplus_cp_work_mode_text[] = {
	[CP_WORK_MODE_UNKNOWN] = "unknown",
	[CP_WORK_MODE_AUTO] = "auto",
	[CP_WORK_MODE_BYPASS] = "bypass",
	[CP_WORK_MODE_2_TO_1] = "2:1",
	[CP_WORK_MODE_3_TO_1] = "3:1",
	[CP_WORK_MODE_4_TO_1] = "4:1",
	[CP_WORK_MODE_1_TO_2] = "1:2",
	[CP_WORK_MODE_1_TO_3] = "1:3",
	[CP_WORK_MODE_1_TO_4] = "1:4",
};

const char *oplus_cp_work_mode_str(enum oplus_cp_work_mode id)
{
	if ((id < 0) || (id > 8))
		return "Invalid";
	return oplus_cp_work_mode_text[id];
}

static const char * const oplus_cp_strategy_type_text[] = {
	[CP_STRAT_OPEN_ALL] = "open_all",
	[CP_STRAT_OPEN_BY_CURR] = "open_by_current",
};

const char *oplus_cp_strategy_type_str(enum oplus_cp_strategy_type id)
{
	if ((id < 0) || (id > 1))
		return "Invalid";
	return oplus_cp_strategy_type_text[id];
}

static const char * const oplus_chg_cp_error_text[] = {
	[CP_ERR_HW_OCP] = "hw_ocp",
	[CP_ERR_HW_OVP] = "hw_ovp",
	[CP_ERR_HW_UCP] = "hw_ucp",
	[CP_ERR_HW_UVP] = "hw_uvp",
	[CP_ERR_SW_OCP] = "sw_ocp",
	[CP_ERR_SW_OVP] = "sw_ovp",
	[CP_ERR_SW_UCP] = "sw_ucp",
	[CP_ERR_SW_UVP] = "sw_uvp",
	[CP_ERR_OPEN] = "open",
	[CP_ERR_I2C] = "i2c",
	[CP_ERR_REG_INFO] = "reg_info",
	[CP_ERR_ONLINE_CHANGE] = "online_change",
};

const char *oplus_chg_cp_error_str(enum oplus_chg_cp_error id)
{
	if ((id < 0) || (id > 11))
		return "Invalid";
	return oplus_chg_cp_error_text[id];
}

static const char * const oplus_sub_btb_state_text[] = {
	[BATT_BTB_STATE_CONNECT] = "btb_connect",
	[BATT_BTB_STATE_NOT_CONNECT] = "btb_disconnect",
	[BATT_BTB_STATE_NOT_SUPPORT] = "btb_state_not_support",
};

const char *oplus_sub_btb_state_str(enum oplus_sub_btb_state id)
{
	if ((id < 0) || (id > 2))
		return "Invalid";
	return oplus_sub_btb_state_text[id];
}

static const char * const oplus_dpdm_switch_mode_text[] = {
	[DPDM_SWITCH_TO_AP] = "ap",
	[DPDM_SWITCH_TO_VOOC] = "vooc",
	[DPDM_SWITCH_TO_UFCS] = "ufcs",
	[DPDM_SWITCH_TO_HEADPHONE] = "headphone",
};

const char *oplus_dpdm_switch_mode_str(enum oplus_dpdm_switch_mode id)
{
	if ((id < 0) || (id > 3))
		return "Invalid";
	return oplus_dpdm_switch_mode_text[id];
}

