SRC_URI += " \
    file://common/tpm/patch/0001-tpm-add-st33htpm-to-driver-supported-list.patch \
    file://common/tpm/kconfig/0001-i2c-tpm_enable_st33htpm.cfg \
"

DELTA_KERNEL_DEFCONFIG += " \
    common/tpm/kconfig/0001-i2c-tpm_enable_st33htpm.cfg \
"
