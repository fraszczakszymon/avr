#!/bin/sh

FILE=${1##*/}
FILENAME=${FILE%.*}
DIR=$(dirname ${1})

echo "\033[33mKompilowanie oraz tworzenie pliku .hex..."
tput sgr0
avr-gcc -mmcu=atmega8 -Os -DF_CPU=8000000UL -Wall "./"$DIR"/"$FILE -o "./"$DIR"/"$FILENAME".o"
avr-objcopy -O ihex "./"$DIR"/"$FILENAME".o" "./"$DIR"/"$FILENAME".hex"

if [ -f "./"$DIR"/"$FILENAME".o" ]; then
  rm "./"$DIR"/"$FILENAME".o"
fi

if [ -f "./"$DIR"/"$FILENAME".hex" ]; then
  echo "\033[32mPlik .hex został utworzony pomyślnie"
  tput sgr0
  read -p "Chcesz zaprogramowac uC ATMega8 skompilowanym programem? (t/n) " RESP
  if [ "$RESP" = "t" ]; then
    avrdude -p atmega8 -c usbasp -U flash:w:$DIR"/main.hex"
  fi
else
  echo "\033[31mWystapil blad podczas tworzenia pliku .hex"
  tput sgr0
fi
