require ../../common/watchdog/i2c-wdt_enable_watchdog_advantech.inc

SRC_URI += " \
    file://kernel-device-tree/imx95-aom5521-a2-lpi2c2-wdt-msp430.dtsi \
"

i2c_wdt_enable() {

    # [!!] List of DTSI files that implement specific functions.
    FUNC_DTSI=" \
        imx95-aom5521-a2-lpi2c2-wdt-msp430.dtsi \
    "

    # Step to add specific function
    for DTSI in $FUNC_DTSI; do
        # copy dtsi file
        install -D "${KERNEL_DTS_ROOT_PATH}/${DTSI}" "${S}/arch/arm64/boot/dts/freescale/${DTSI}"
        # append target device tree (check it is written or not)
        if [ ! -f "${KERNEL_FILE_COLLECT_ADD}" ] || ! grep -qF "$DTSI" "${KERNEL_FILE_COLLECT_ADD}"; then
            echo "#include \"$DTSI\"" >> "${KERNEL_FILE_COLLECT_ADD}"
        fi
    done
}
