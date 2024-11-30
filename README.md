# Commodore 900 helper scripts

This repository contains scripts that I have created to bring my Commodore 900 to life. The contents are as follows:

`scripts`

This directory contains two Perl scripts that are required to format the hard disk and to build system installation floppies from images.

The scripts access the machine language monitor in the BIOS using the serial line and issue appropriate commands to the disk controller.
To use the scripts, you need to remove the graphics card from the computer, so that the BIOS uses the serial port for input and output.

`rom`

This directory contains a modified system BIOS that does not try to access the hard drive before starting the machine language monitor.

This is necessary to format the hard disk, because otherwise the disk controller will hang trying to access the unformatted disk and will become unusable afterwards. It will then not be possible format the HDD, as the controller is hung.
