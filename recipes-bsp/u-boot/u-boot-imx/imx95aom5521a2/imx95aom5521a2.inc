# Install files
SRC_URI += " \
	file://imx95-aom5521-a2.dts;subdir=git/arch/arm/dts \
	file://imx95-aom5521-a2-local.dtsi;subdir=git/arch/arm/dts \
	file://imx95-aom5521-a2-u-boot.dtsi;subdir=git/arch/arm/dts \
	file://0001-imx95_evk-add-iomux-swrst.patch \
"

do_configure:prepend() {
	# imx95_19x19_evk_defconfig
	## Change the `CONFIG_DEFAULT_DEVICE_TREE`
	sed -i "/^CONFIG_DEFAULT_DEVICE_TREE=/c\CONFIG_DEFAULT_DEVICE_TREE=\"imx95-aom5521-a2\"" ${S}/configs/imx95_19x19_evk_defconfig

	## Change the `CONFIG_DEFAULT_FDT_FILE`
	sed -i "/^CONFIG_DEFAULT_FDT_FILE=/c\CONFIG_DEFAULT_FDT_FILE=\"imx95-aom5521-a2.dtb\"" ${S}/configs/imx95_19x19_evk_defconfig

	## Modify CONFIG to imx95aom5521a2 setting
	sed -i "/^CONFIG_SF_DEFAULT_SPEED=/c\CONFIG_SF_DEFAULT_SPEED=40000000" ${S}/configs/imx95_19x19_evk_defconfig
	sed -i "/^CONFIG_USB_TCPC=y/c\# CONFIG_USB_TCPC is not set" ${S}/configs/imx95_19x19_evk_defconfig
	echo "CONFIG_SPI_FLASH_WINBOND=y" >> ${S}/configs/imx95_19x19_evk_defconfig

	# Makefile
	sed -i '/imx95-19x19-verdin.dtb/i \imx95-aom5521-a2.dtb \\' ${S}/arch/arm/dts/Makefile

	# imx95_evk.h
	## Change all the PHYS_SDRAM_2_SIZE to 6GB
	sed -i '/PHYS_SDRAM_2_SIZE/s/.*/#define PHYS_SDRAM_2_SIZE    0x180000000UL/' ${S}/include/configs/imx95_evk.h

}
