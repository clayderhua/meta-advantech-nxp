SRC_URI += " \
    file://common/rtc/patch/0001-drivers-Add-delay-for-S35390A-RTC.patch \
    file://common/rtc/kconfig/rtc_support.cfg \
"

DELTA_KERNEL_DEFCONFIG += " \
    common/rtc/kconfig/rtc_support.cfg \
"

