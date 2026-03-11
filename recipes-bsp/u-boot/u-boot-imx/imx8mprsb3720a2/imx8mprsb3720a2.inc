require ../board/imx8mprsb3720a2/change_debug_port_uart3.inc
require ../board/imx8mprsb3720a2/support_ethernet_MAC_address.inc
require ../drivers/spi/spi_controller_not_support_advanced_features.inc

SRC_URI += " \
    file://imx8mp-evk-u-boot.dtsi;subdir=git/arch/arm/dts/ \
    file://imx8mp-evk.dts;subdir=git/dts/upstream/src/arm64/freescale/ \
"

# For Uboot defualt parameter #
do_configure:prepend() {
    sed -i "/^CONFIG_DEFAULT_FDT_FILE=/c\CONFIG_DEFAULT_FDT_FILE=\"imx8mp-rsb3720-a2.dtb\"" ${S}/configs/imx8mp_evk_defconfig
    sed -i 's/ttymxc1/ttymxc2/g' ${S}/board/freescale/imx8mp_evk/imx8mp_evk.env
}
