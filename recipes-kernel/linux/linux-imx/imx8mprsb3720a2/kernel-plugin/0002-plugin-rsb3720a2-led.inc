SRC_URI += " \
        file://kernel-device-tree/conflicts/imx8mp-rsb3720-a2-diffevk-led.dtsi \
	file://kernel-device-tree/imx8mp-rsb3720-a2-led.dtsi \
"

led_enable() {

    # [!!] List of DTSI files that handle EVK differences.
    EVK_DIFF_DTSI="\
	imx8mp-rsb3720-a2-diffevk-led.dtsi \    
    "

    # [!!] List of DTSI files that implement specific functions.
    FUNC_DTSI="\
        imx8mp-rsb3720-a2-led.dtsi \
    "

    append_string_to_file() {
        local S=$1
        local F=$2
        if [ ! -f "${F}" ] || ! grep -qF "$S" "${F}"; then
            echo "#include \"$S\"" >> "${F}"
        fi
    }

    # Step to handle EVK different
    for DTSI in $EVK_DIFF_DTSI; do
        # copy dtsi file
        install -D "${KERNEL_DTS_ROOT_PATH}/conflicts/${DTSI}" "${S}/arch/arm64/boot/dts/freescale/${DTSI}"
        # append target device tree
        append_string_to_file "${DTSI}" "${KERNEL_FILE_COLLECT_DIFF}"
    done

    # Step to add specific function
    for DTSI in $FUNC_DTSI; do
        # copy dtsi file
        install -D "${KERNEL_DTS_ROOT_PATH}/${DTSI}" "${S}/arch/arm64/boot/dts/freescale/${DTSI}"
        # append target device tree
        append_string_to_file "${DTSI}" "${KERNEL_FILE_COLLECT_ADD}"
    done
}

