require kernel-plugin/0001-plugin-rom2620a1-uart.inc
require kernel-plugin/0002-plugin-rom2620a1-acodec-sgtl5000.inc
require kernel-plugin/0003-plugin-rom2620a1-i2c.inc
require kernel-plugin/0004-plugin-rom2620a1-enet.inc
require kernel-plugin/0005-plugin-rom2620a1-sdcard.inc
require kernel-plugin/0006-plugin-rom2620a1-usb.inc
require kernel-plugin/0007-plugin-rom2620a1-display-auog070vw01.inc
require kernel-plugin/0008-plugin-rom2620a1-pwm.inc
require kernel-plugin/0009-plugin-rom2620a1-gpio.inc
require kernel-plugin/0010-plugin-rom2620a1-m2.inc
require kernel-plugin/0011-plugin-rom2620a1-i2c-eeprom.inc
require kernel-plugin/0012-plugin-rom2620a1-cam-ov5640.inc
require ../common/others/imx8ulp/imx8ulp_pta_ptb_ptc_support.inc
require ../common/others/imx8ulp/imx8ulp_pwm_tpm7_support.inc

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
    uart \
    acodec \
    i2c \
    ethernet \
    sdcard \
    usb \
    gpio \
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
                uart)
                    uart_enable
                    ;;
                acodec)
                    acodec_enable
                    ;;
                i2c)
                    i2c_enable
                    ;;
                ethernet)
                    ethernet_enable
                    ;;
                sdcard)
                    sdcard_enable
                    ;;
                usb)
                    usb_enable
                    ;;
                gpio)
                    gpio_enable
                    ;;
                pwm)
                    pwm_enable
                    ;;
                m2)
                    m2_enable
                    ;;
                cam_ov5640)
                    cam_ov5640_enable
                    ;;
                i2c_eeprom)
                    i2c_eeprom_enable
                    ;;
                lvds_auog070vw01)
                    lvds_auog070vw01_enable
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
        cat ${KERNEL_FILE_COLLECT_DIFF} >> ${dts_move_to}/$current.dts
        echo "//Then include the DTSI files related to the newly added functions" >> ${dts_move_to}/$current.dts
        cat ${KERNEL_FILE_COLLECT_ADD} >> ${dts_move_to}/$current.dts

        rm ${KERNEL_FILE_COLLECT_DIFF}
        rm ${KERNEL_FILE_COLLECT_ADD}

    done
}

