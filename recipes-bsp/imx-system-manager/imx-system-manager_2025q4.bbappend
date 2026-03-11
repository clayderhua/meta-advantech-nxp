FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

SRC_URI += " \
           file://0001-AOM-5521-Remove-pcal6408-related-code.patch \
           file://0002-AOM-5521-Move-CAN_FD1-to-A55.patch \
           file://0003-AOM-5521-Remove-LPUART3-and-move-GPIO_IO14-GPIO_IO15-to-A55.patch \
           "
# System manager requires only patch 0001 to function correctly.
# Patches 0002 and 0003 can be applied as needed.

