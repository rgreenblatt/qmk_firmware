#!/usr/bin/env bash

if [ "$#" -ne 1 ]; then
  echo "usage: $0 <FILE_PATH>"
fi

L_COUNT=$(wc -l < $1)
L_PER=30
ITERS=$(echo "1 + $L_COUNT / $L_PER" | bc)

for ((i=0; i<$ITERS; i++)); do
  START=$(echo "$i * $L_PER" | bc)
  END=$(echo "($i + 1) * $L_PER - 1" | bc)
  < $1 head -n "$END" | tail -n +"$START" > keyboards/gergo/keymaps/greenblatt/data.h
  make gergo:greenblatt
  sudo make gergo:greenblatt:dfu
done
