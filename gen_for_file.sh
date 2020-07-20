#!/usr/bin/env bash

if [ "$#" -ne 1 ]; then
  echo "usage: $0 <FILE_PATH>"
fi

echo "$(python3 make_decompressable.py $1 | xxd -i)," > tmp.txt && ./file_to_data.sh tmp.txt
