#!/bin/sh

ver=`git tag | tail -n 1`
#echo $ver

tmp=/tmp/marlin

rm -rf $tmp
mkdir $tmp
cp .pio/build/mega2560/firmware.hex $tmp
cp ~/.platformio/packages/tool-avrdude/avrdude.conf $tmp
cp update.txt $tmp

d=`date "+%y%m%d"`

cd $tmp
zip marlin.$ver.MT.$d.zip * > /dev/null

ls -l marlin.$ver.MT.$d.zip

