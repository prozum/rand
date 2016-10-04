#!/bin/bash

echo -n "Input filename of file to upload, don't include the filetype: "
read filename

dev="/dev/ttyACM4"
board="atmega328p"

#-Os
avr-gcc -g -DF_CPU=16000000UL -mmcu=$board -c "$filename".c avr8-stub.c;
avr-gcc -mmcu=$board "$filename".o avr8-stub.o -o "$filename";

avr-objcopy -O ihex -R .eeprom "$filename" "$filename".hex;
avrdude -F -V -c arduino -p $board -P $dev -b 115200 -U flash:w:"$filename".hex;
