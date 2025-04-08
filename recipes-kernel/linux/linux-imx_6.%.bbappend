FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}:"

require recipes-kernel/linux/linux-imx/${MACHINE}/${MACHINE}.inc
#LOCALVERSION = "-lts-next-imx-6.12.3-1.0.0-advantech"
