################################################################
# COMMON
################################################################
UFF_FP_DRIVER_INJECT_ENABLE := no
ifeq ($(TARGET_BUILD_VARIANT),userdebug)
UFF_FP_DRIVER_INJECT_ENABLE := yes
endif

ifeq ($(OPLUS_FEATURE_BSP_DRV_VND_INJECT_TEST),1)
UFF_FP_DRIVER_INJECT_ENABLE := yes
endif

# inject
ifeq ($(UFF_FP_DRIVER_INJECT_ENABLE),yes)
ccflags-y += -DCONFIG_FP_INJECT_ENABLE
endif

# gki
ccflags-y += -DCONFIG_OPLUS_FINGERPRINT_GKI_ENABLE

################################################################
# QCOM
################################################################
ccflags-y += -DQCOM_PLATFORM

#tp for gki
ccflags-y += -I$(src)/../../../../../../kernel/touchpanel/oplus_touchscreen_v2/touchpanel_notify

obj-m += oplus_bsp_uff_fp_driver.o
uff_fp_driver-y := fp_driver.o fp_platform.o fingerprint_event.o fp_health.o fp_netlink.o
uff_fp_driver-y += fp_fault_inject.o
oplus_bsp_uff_fp_driver-y := $(uff_fp_driver-y)

################################################################
# MTK
################################################################
ifeq ($(CONFIG_UFF_FINGERPRINT_MTK),y)
ccflags-y += -DMTK_PLATFORM
subdir-ccflags-y += -I$(srctree)/drivers/misc/mediatek/include
subdir-ccflags-y += -I$(srctree)/drivers/misc/mediatek/include/mt-plat/$(MTK_PLATFORM)/include
subdir-ccflags-y += -I$(srctree)/drivers/misc/mediatek/include/mt-plat
subdir-ccflags-y += -I$(srctree)/drivers/spi/mediatek/$(MTK_PLATFORM)
subdir-ccflags-y += -I$(srctree)/drivers/spi/trustzone/spi/Tlspi/inc

ifneq ($(filter kernel-4.19, $(LINUX_KERNEL_VERSION)),)
include $(srctree)/drivers/tee/gud/Makefile.include
else ifneq ($(filter kernel-4.14 kernel-4.9, $(LINUX_KERNEL_VERSION)),)
include $(srctree)/drivers/misc/mediatek/gud/Makefile.include
endif

#lcd uiready for gki
ccflags-$(CONFIG_DRM_MEDIATEK_V2) += -I$(srctree)/drivers/gpu/drm/mediatek/mediatek_v2/
ccflags-$(CONFIG_DRM_MEDIATEK_V2) += -DCONFIG_DRM_MEDIATEK_V2

# wl2868c supply for gki
ccflags-$(CONFIG_FP_SUPPLY_MODE_LDO) += -I$(srctree)/drivers/misc/mediatek/wl2868c
ccflags-$(CONFIG_FP_SUPPLY_MODE_LDO) += -DCONFIG_FP_SUPPLY_MODE_LDO

# DIO8018 power supply
ccflags-$(CONFIG_FP_SUPPLY_MODE_LDO_DIO8018) += -I$(srctree)/drivers/misc/mediatek/pmic/pmic_ldo_set
ccflags-$(CONFIG_FP_SUPPLY_MODE_LDO_DIO8018) += -DCONFIG_FP_SUPPLY_MODE_LDO_DIO8018

ifeq ($(CONFIG_OPLUS_FINGERPRINT_GKI_ENABLE),y)
#tp for gki
ccflags-y += -I$(srctree)/../vendor/oplus/kernel/touchpanel/oplus_touchscreen_v2/touchpanel_notify
endif

obj-$(CONFIG_UFF_FINGERPRINT) += uff_fp_driver.o
uff_fp_driver-y := fp_driver.o fp_platform.o fingerprint_event.o fp_health.o fp_netlink.o
ifeq ($(UFF_FP_DRIVER_INJECT_ENABLE),yes)
uff_fp_driver-y += fp_fault_inject.o
endif
endif

################################################################
# REE
################################################################
obj-$(CONFIG_UFF_FINGERPRINT_REE_SPI) += ree_spi/

# Defines taken from oplus_local_modules.bzl (local_defines).
# The OPlus module configuration lives in the Bazel files and is not set on
# the Makefile path, while some code has asymmetric guards - e.g. in
# fp_driver.c the #include is under CONFIG_TOUCHPANEL_NOTIFY but the struct
# usage is not. BUILD_BY_BAZEL (not a Bazel build) and CONFIG_OF (provided by
# the kernel) are omitted.
ccflags-y += -DCONFIG_TOUCHPANEL_NOTIFY
