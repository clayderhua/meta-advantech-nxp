do_configure:prepend() {
	sed -i "/^CONFIG_DEFAULT_FDT_FILE=/c\CONFIG_DEFAULT_FDT_FILE=\"imx93-rom2820-a1.dtb\"" ${S}/configs/imx93_11x11_evk_defconfig
}

