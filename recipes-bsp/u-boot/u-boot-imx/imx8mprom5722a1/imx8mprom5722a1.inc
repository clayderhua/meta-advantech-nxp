do_configure:prepend() {
	sed -i "/^CONFIG_DEFAULT_FDT_FILE=/c\CONFIG_DEFAULT_FDT_FILE=\"imx8mp-rom5722-a1.dtb\"" ${S}/configs/imx8mp_evk_defconfig
}
