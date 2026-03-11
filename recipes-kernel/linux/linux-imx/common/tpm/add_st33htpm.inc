SRC_URI += " \
    file://common/tpm/patch/0001-add_st33htpm.patch \
    file://common/tpm/kconfig/0001-add_st33htpm.cfg \
"

DELTA_KERNEL_DEFCONFIG += " \
    common/tpm/kconfig/0001-add_st33htpm.cfg \
"

