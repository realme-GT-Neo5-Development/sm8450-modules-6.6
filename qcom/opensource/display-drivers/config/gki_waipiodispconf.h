/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (c) 2021, The Linux Foundation. All rights reserved.
 */

#define CONFIG_DRM_MSM 1
#define CONFIG_DRM_MSM_SDE 1
#define CONFIG_SYNC_FILE 1
#define CONFIG_DRM_MSM_DSI 1
#define CONFIG_DRM_MSM_DP 1
#define CONFIG_DRM_MSM_DP_MST 1
#define CONFIG_DSI_PARSER 1
#define CONFIG_DRM_SDE_WB 1
#define CONFIG_DRM_SDE_RSC 1
#define CONFIG_DRM_MSM_REGISTER_LOGGING 1
#define CONFIG_MSM_MMRM 1
#define CONFIG_DRM_SDE_EVTLOG_DEBUG 1
#define CONFIG_QCOM_MDSS_PLL 1
#define CONFIG_GKI_DISPLAY 1
#define CONFIG_MSM_EXT_DISPLAY 1
#define CONFIG_DRM_SDE_VM 1
#define CONFIG_HDCP_QSEECOM 1

/*
 * Pixelworks Iris5 display co-processor, present on senna ("pixelworks,iris"
 * and "pixelworks,iris-i2c" DT nodes).
 *
 * Qualcomm's 5.10 tree only sets CONFIG_PXLW_IRIS in the .conf (a make
 * variable gating objects), which would leave the `#if defined(CONFIG_PXLW_IRIS)`
 * hooks in the QC code compiled out. The OPlus 5.10 vendor code defines it
 * here as well so the hooks are active; do the same.
 */
#define CONFIG_PXLW_IRIS 1

/*
 * FORWARDPORT: OPlus display layer, from LineageOS sm8450 5.10. Provides
 * /sys/kernel/oplus_display/ (panel_serial_number, hbm, nit_brightness),
 * which the fingerprint HAL (@2.1-service_uff) reads directly; without it
 * the panel is reported with the wrong vendor and there is no HBM control
 * for under-display fingerprint.
 *
 * Note: OPLUS_FEATURE_DISPLAY is a global flag, set via KBUILD_CFLAGS in the
 * kernel Makefile. Dropping CONFIG_DRM_OPLUS alone does not compile out the
 * `#ifdef OPLUS_FEATURE_DISPLAY` blocks in msm/, which then reference symbols
 * from the unbuilt oplus/ directory. To disable the layer, also
 * `#undef OPLUS_FEATURE_DISPLAY` here: this header is `-include`d after the
 * command-line `-D` options are processed.
 */
#define CONFIG_DRM_OPLUS 1
#define CONFIG_DRM_OPLUS_NOTIFY 1

/*
 * OPlus layer sub-features, as in the LineageOS sm8450 5.10
 * gki_waipiodispconf.h. ONSCREENFINGERPRINT provides CONNECTOR_PROP_HBM_ENABLE
 * and the oplus_ofp_* fields in dsi_display_mode_priv_info, which
 * oplus_onscreenfingerprint.c (HBM control for fingerprint) requires.
 */
#define OPLUS_FEATURE_DISPLAY_TEMP_COMPENSATION 1
#define OPLUS_FEATURE_DISPLAY_ONSCREENFINGERPRINT 1
