require kernel-plugin/0001-plugin-rom5722a1-i2c.inc
require kernel-plugin/0002-plugin-rom5722a1-rtc.inc
require kernel-plugin/0003-plugin-rom5722a1-gpioexpander.inc

SRC_URI += " \
    file://kernel-device-tree/base.dts \
    file://kernel-json \
"

KERNEL_JSON_ROOT_PATH = "${UNPACKDIR}/kernel-json"
KERNEL_DTS_ROOT_PATH = "${UNPACKDIR}/kernel-device-tree"
KERNEL_DEFAULT_JSON = "${KERNEL_JSON_ROOT_PATH}/kernel-default.json"
KERNEL_DTS_MOVE_TO = "${S}/arch/arm64/boot/dts/freescale"

KERNEL_FILE_COLLECT_DIFF = "COLLECT_DIFF_DTSI.TEMP"
KERNEL_FILE_COLLECT_ADD = "COLLECT_ADD_DTSI.TEMP"

FUNCLIST="\
    debugport_uart3 \
    led \
    i2c \
    rtc \
    gpioexpander \
    tpm \
    watchdog \
    pwm \
    m2 \
    cam_ov5640 \
    i2c_eeprom \
    lvds_auog070vw01 \
"

import_modules() {
    for func in ${FUNCLIST}; do
        enable_var="enable_${func}"
        if [ "$(eval echo \$$enable_var)" = "1" ]; then
            case $func in
		debugport_uart3)
                    ;;
                led)
                    ;;
                i2c)
	    i2c_enable
                    ;;
                rtc)
	    rtc_enable
                    ;;
                gpioexpander)
	    gpioexpander_enable
                    ;;
                tpm)
                    ;;
                watchdog)
                    ;;
                pwm)
                    ;;
                m2)
                    ;;
                cam_ov5640)
                    ;;
                i2c_eeprom)
                    ;;
                lvds_auog070vw01)
                    ;;
                *)
                    echo "Unknown function: $func"
                    ;;
            esac
        fi
    done
}

###########################################################
## The following content requires almost no modification ##
###########################################################

inherit json-parse-type-nxp

do_configure:prepend() {

    local json_file="${KERNEL_DEFAULT_JSON}"
    local func_list="${FUNCLIST}"
    local dts_base="${KERNEL_DTS_ROOT_PATH}/base.dts"
    local dts_move_to="${KERNEL_DTS_MOVE_TO}"

    confs=$(get_namelist_of_conf_root "${json_file}")

    for current in $confs; do

        cp ${dts_base} ${dts_move_to}/$current.dts
        echo "dtb-\$(CONFIG_ARCH_MXC) += $current.dtb" >> ${dts_move_to}/Makefile

        set_modules_enable_or_not "$func_list" "$json_file" "$current"
        import_modules

        echo "//First include the DTSI that are different from the evk board" >> ${dts_move_to}/$current.dts
        if [ -f "${KERNEL_FILE_COLLECT_DIFF}" ]; then
            cat ${KERNEL_FILE_COLLECT_DIFF} >> ${dts_move_to}/$current.dts
        fi
        echo "//Then include the DTSI files related to the newly added functions" >> ${dts_move_to}/$current.dts
        if [ -f "${KERNEL_FILE_COLLECT_ADD}" ]; then
            cat ${KERNEL_FILE_COLLECT_ADD} >> ${dts_move_to}/$current.dts
        fi

        [ -f "${KERNEL_FILE_COLLECT_DIFF}" ] && rm ${KERNEL_FILE_COLLECT_DIFF}
        [ -f "${KERNEL_FILE_COLLECT_ADD}" ] && rm ${KERNEL_FILE_COLLECT_ADD}

    done
}
