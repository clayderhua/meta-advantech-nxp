SRC_URI += " \
    file://common/display/lt9211/patch/0001-LVDS-LT9211-modify-driver-to-support-U5-revision.patch \
    file://common/display/lt9211/patch/0002-LVDS-LT9211-force-driver-to-dual-port-output.patch \
    file://common/display/lt9211/patch/0003-LVDS-LT9211-support-RGD_CAPITAL_FST-option-for-PCR-unstable-issue.patch \
    file://common/display/lt9211/kconfig/0001-lvds-enable-lt9211.cfg \
"

DELTA_KERNEL_DEFCONFIG += " \
    common/display/lt9211/kconfig/0001-lvds-enable-lt9211.cfg \
"

