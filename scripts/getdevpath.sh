#!/bin/bash
# getdevpath
#
# Apr 09 Polhemus -- first line changed from !/bin/sh to !/bin/bash to work on the dash shell (Ubuntu)
#
# Copyright(c) 2002 Cypress Semiconductor
#
# this script reads /proc/bus/usb/devices and builds the
# proper usb file system path to the device corresponding
# to the caller's vis and pid arguments. The pathname is
# written to stdout.
#
# usage: getdevpath -vVID -pPID
# where VID is Vendor ID in hex
# and PID is Product ID in hex
# set variables
MYVID=
MYPID=
TLINE=
BUS=
DEV=
EURIKA=
function usage() {
cat <<EOF
Usage: $0 -vVID -pPID
-v Vendor ID in hex
-p Product ID in hex
-? this help message
EOF
exit 0
}
# parse command-line arguments
while getopts ":v:p:" opt; do
case $opt in
v) MYVID=$OPTARG ;;
p) MYPID=$OPTARG ;;
\?) usage ;;
esac
done
# pad VID and PID with left-end zeros
COUNT=`echo $MYVID | wc -c`
while [ $COUNT -lt 5 ]
do
MYVID=`echo 0$MYVID`
let COUNT=COUNT+1
done
COUNT=`echo $MYPID | wc -c`
while [ $COUNT -lt 5 ]
do
MYPID=`echo 0$MYPID`
let COUNT=COUNT+1
done
# VID and PID both equal to "0000" is invalid
if [ "$MYPID" == "0000" ]
then
if [ "$MYVID" == "0000" ]
then
usage;
fi
fi
# set result in temp file for later checking
echo "false" > eurika
# read usb devices list, taking the lines with useful info
cat /proc/bus/usb/devices | grep "T:\|P:" |
while
read LINE
do
if [ `expr substr "$LINE" 1 1` == "T" ]
then
TLINE=$LINE
else
VID=`expr substr "$LINE" 12 4`
PID=`expr substr "$LINE" 24 4`
if [ $VID == $MYVID ]
then
if [ $PID == $MYPID ]
then
echo $TLINE > tline
BUS=`awk '{print $2}' < tline | cut -c5-`
COUNT=`echo $BUS | wc -c`
while [ $COUNT -lt 4 ]
do
BUS=`echo 0$BUS`
let COUNT=COUNT+1
done
DEV=`awk '{print $8}' < tline`
COUNT=`echo $DEV | wc -c`
while [ $COUNT -lt 4 ]
do
DEV=`echo 0$DEV`
let COUNT=COUNT+1
done
rm tline
echo "true" > eurika
echo /proc/bus/usb/$BUS/$DEV
fi
fi
fi
done
if [ `cat eurika` == "false" ]
then
echo "device not found"
fi
rm eurika

