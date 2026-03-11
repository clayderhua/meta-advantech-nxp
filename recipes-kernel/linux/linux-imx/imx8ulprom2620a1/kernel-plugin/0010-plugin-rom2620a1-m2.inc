SRC_URI += " \
    file://kernel-device-tree/conflicts/imx8ulp-rom2620-a1-diffevk-dsi.dtsi \
    file://kernel-device-tree/conflicts/imx8ulp-rom2620-a1-diffevk-enet.dtsi \
    file://kernel-device-tree/conflicts/imx8ulp-rom2620-a1-diffevk-usdhc2.dtsi \
    file://kernel-device-tree/conflicts/imx8ulp-rom2620-a1-diffevk-bt-sound.dtsi \
    file://kernel-device-tree/imx8ulp-rom2620-a1-pta-ptb-ptc.dtsi \
    file://kernel-device-tree/imx8ulp-rom2620-a1-m2-uart4.dtsi \
    file://kernel-device-tree/imx8ulp-rom2620-a1-m2-usdhc2.dtsi \
"

m2_enable() {

    # [!!] List of DTSI files that handle EVK differences.
    EVK_DIFF_DTSI="\
        imx8ulp-rom2620-a1-diffevk-dsi.dtsi \
        imx8ulp-rom2620-a1-diffevk-enet.dtsi \
        imx8ulp-rom2620-a1-diffevk-usdhc2.dtsi \
        imx8ulp-rom2620-a1-diffevk-bt-sound.dtsi \
    "

    # [!!] List of DTSI files that implement specific functions.
    FUNC_DTSI="\
        imx8ulp-rom2620-a1-pta-ptb-ptc.dtsi \
        imx8ulp-rom2620-a1-m2-uart4.dtsi \
        imx8ulp-rom2620-a1-m2-usdhc2.dtsi \
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
