#!/bin/sh

CONF=avrdude.conf
HEX=firmware.hex
if [ ! -e $CONF  -o ! -e $HEX ]
then
  CONF=~/.platformio/packages/tool-avrdude/$CONF
  HEX=.pio/build/mega2560/$HEX
fi
if [ ! -e $CONF  -o ! -e $HEX ]
then
  echo $CONF and $HEX not exists!
  exit 1
fi
echo found [$CONF] and [$HEX]
avrdude -V -p atmega2560 -C $CONF -c wiring -b 115200 -D -P /dev/cu.wchusbserial1440 -U flash:w:$HEX:i
