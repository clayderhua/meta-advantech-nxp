# Function related
require kernel-plugin/0001-plugin-aom5521a2-usb2.inc
require kernel-plugin/0002-plugin-aom5521a2-gpio.inc
require kernel-plugin/0003-plugin-aom5521a2-usbotg.inc
require kernel-plugin/0004-plugin-aom5521a2-i2c.inc
require kernel-plugin/0005-plugin-aom5521a2-uart.inc
require kernel-plugin/0006-plugin-aom5521a2-enet.inc
require kernel-plugin/0007-plugin-aom5521a2-enet-tg.inc
require kernel-plugin/0008-plugin-aom5521a2-hdmi.inc
require kernel-plugin/0009-plugin-aom5521a2-spi.inc
require kernel-plugin/0010-plugin-aom5521a2-spi-nor-flash.inc
require kernel-plugin/0011-plugin-aom5521a2-can.inc
require kernel-plugin/0012-plugin-aom5521a2-pcie0.inc
require kernel-plugin/0013-plugin-aom5521a2-pcie1.inc
require kernel-plugin/0014-plugin-aom5521a2-i2c-rtc.inc
require kernel-plugin/0015-plugin-aom5521a2-i2c-wdt.inc
require kernel-plugin/0016-plugin-aom5521a2-i2c-codec.inc
require kernel-plugin/0017-plugin-aom5521a2-i2c-eeprom.inc
require kernel-plugin/0018-plugin-aom5521a2-i2c-tpm.inc
require kernel-plugin/0019-plugin-aom5521a2-i2c-gpioexp.inc

# Driver related

SRC_URI += " \
    file://kernel-device-tree/base.dts \
    file://kernel-device-tree/conflicts \
    file://kernel-json \
"

KERNEL_JSON_ROOT_PATH = "${UNPACKDIR}/kernel-json"
KERNEL_DTS_ROOT_PATH = "${UNPACKDIR}/kernel-device-tree"
KERNEL_DEFAULT_JSON = "${KERNEL_JSON_ROOT_PATH}/kernel-default.json"
KERNEL_DTS_MOVE_TO = "${S}/arch/arm64/boot/dts/freescale"

KERNEL_FILE_COLLECT_ADD = "COLLECT_ADD_DTSI.TEMP"

FUNCLIST = " \
    usb2 \
    gpio \
    usbotg \
    i2c \
    uart \
    enet \
    enet_tg \
    hdmi \
    spi \
    spi_nor_flash \
    can \
    pcie0 \
    pcie1 \
    i2c_rtc \
    i2c_wdt \
    i2c_codec \
    i2c_eeprom \
    i2c_tpm \
    i2c_gpioexp \
"

import_modules() {
    for func in ${FUNCLIST}; do

        enable_var="enable_${func}"

    if [ "$(eval echo \$$enable_var)" = "1" ]; then

        case $func in
            usb2)
            usb2_enable
            ;;
            gpio)
            gpio_enable
            ;;
            usbotg)
            usbotg_enable
            ;;
            i2c)
            i2c_enable
            ;;
            uart)
            uart_enable
            ;;
            enet)
            enet_enable
            ;;
            enet_tg)
            enet_tg_enable
            ;;
            hdmi)
            hdmi_enable
            ;;
            spi)
            spi_enable
            ;;
            spi_nor_flash)
            spi_nor_flash_enable
            ;;
            can)
            can_enable
            ;;
            pcie0)
            pcie0_enable
            ;;
            pcie1)
            pcie1_enable
            ;;
            i2c_rtc)
            i2c_rtc_enable
            ;;
            i2c_wdt)
            i2c_wdt_enable
            ;;
            i2c_codec)
            i2c_codec_enable
            ;;
            i2c_eeprom)
            i2c_eeprom_enable
            ;;
            i2c_tpm)
            i2c_tpm_enable
            ;;
            i2c_gpioexp)
            i2c_gpioexp_enable
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

        ######################
        # Create device-tree #
        ######################

        cp ${dts_base} ${dts_move_to}/$current.dts
        echo "dtb-\$(CONFIG_ARCH_MXC) += $current.dtb" >> ${dts_move_to}/Makefile

        ###############################
        # Different contents with EVB #
        ###############################

        echo "/*" >> ${dts_move_to}/$current.dts
        echo " * Step1. Include the difference set dtsi to remove some contents from EVK." >> ${dts_move_to}/$current.dts
        echo " */" >> ${dts_move_to}/$current.dts

        for file in $(ls ${KERNEL_DTS_ROOT_PATH}/conflicts); do
            if [ -f "${KERNEL_DTS_ROOT_PATH}/conflicts/$file" ]; then
                install -D "${KERNEL_DTS_ROOT_PATH}/conflicts/$file" "${dts_move_to}/$file"
                echo "#include \"$file\"" >> ${dts_move_to}/$current.dts
            fi
        done
        echo "" >> ${dts_move_to}/$current.dts

        ###################
        # Features import #
        ###################

        set_modules_enable_or_not "$func_list" "$json_file" "$current"
        import_modules

        echo "/*" >> ${dts_move_to}/$current.dts
        echo " * Step2. The features of the device tree are added below" >> ${dts_move_to}/$current.dts
        echo " */" >> ${dts_move_to}/$current.dts

        if [ -f "${KERNEL_FILE_COLLECT_ADD}" ]; then
            cat ${KERNEL_FILE_COLLECT_ADD} >> ${dts_move_to}/$current.dts
        fi

        [ -f "${KERNEL_FILE_COLLECT_ADD}" ] && rm ${KERNEL_FILE_COLLECT_ADD}

    done
}
