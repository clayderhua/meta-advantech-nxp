#require drivers/watchdog_advantech.inc

SRC_URI += " \
    file://rtc-support.cfg \
    file://rsb3720.dts \
"

do_configure:prepend() {
    cp ${UNPACKDIR}/rsb3720.dts ${S}/arch/arm64/boot/dts/freescale/
    echo 'dtb-$(CONFIG_ARCH_MXC) += rsb3720.dtb' >> ${S}/arch/arm64/boot/dts/freescale/Makefile
}


DELTA_KERNEL_DEFCONFIG += "rtc-support.cfg"
