FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}:"

require recipes-kernel/linux/linux-imx/${MACHINE}/${MACHINE}.inc
#LOCALVERSION = "-lts-next-imx-6.12.49-advantech"

DEPENDS += "jq jq-native"
