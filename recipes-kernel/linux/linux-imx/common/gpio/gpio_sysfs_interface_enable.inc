SRC_URI += " \
    file://common/gpio/patch/0001-GPIO-Remove-expert-restriction-from-sysfs-configuration.patch \
    file://common/gpio/kconfig/0001-gpio-enable-sysfs-option.cfg \
"

DELTA_KERNEL_DEFCONFIG += " \
    common/gpio/kconfig/0001-gpio-enable-sysfs-option.cfg \
"

