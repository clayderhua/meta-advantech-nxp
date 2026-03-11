SRC_URI += " \
	file://lpddr4x_timing_afee420a1.c;subdir=git/board/freescale/imx93_evk/ \
"

do_configure:prepend() {
	sed -i "/^CONFIG_DEFAULT_FDT_FILE=/c\CONFIG_DEFAULT_FDT_FILE=\"imx93-afee420-a1.dtb\"" ${S}/configs/imx93_11x11_evk_defconfig	
	sed -i 's/lpddr4x_timing.o/lpddr4x_timing_afee420a1.o/g' ${S}/board/freescale/imx93_evk/Makefile
}
