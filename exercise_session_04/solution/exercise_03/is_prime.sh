#!/bin/bash
NUMBER=$1

if [[ -z $NUMBER ]]; then
    echo "enter a number: "
    read NUMBER
fi

if [[ ! $NUMBER =~ ^[0-9]*$ ]]; then
    echo "give a number!"
    exit 1
fi

for ((i = 2 ; i < $NUMBER ; i++)); do
  if [ $(expr $NUMBER % $i) -eq 0 ]; then
    echo "FALSE, $NUMBER is divisable by $i"
    exit 0
  fi
done

echo TRUE
