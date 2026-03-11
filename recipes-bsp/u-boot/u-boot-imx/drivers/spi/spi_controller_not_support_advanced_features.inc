SRC_URI += " \
    file://drivers/spi/0001-spi_controller_not_support_advanced_features.patch \
"

do_configure:prepend() {
	echo 'CONFIG_SPI_FLASH_WINBOND=y' >> ${S}/configs/imx8mp_evk_defconfig
}
