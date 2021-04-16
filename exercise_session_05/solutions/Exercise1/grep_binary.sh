#!/bin/bash -l

BINARY_FILE="./../../binary.txt"

GREP_OPTIONS='-i --color'

echo "1): end with 00"
egrep $GREP_OPTIONS ".{14}00" ${BINARY_FILE}
# egrep "[01]{${STRING_LENGTH}}00" ${BINARY_FILE} # alternatively, this can be used
if [[ $? -ne 0 ]]; then echo "no such sequence found"; fi

echo "2): start and end with 1"
egrep ${GREP_OPTIONS} "1.{14}1" ${BINARY_FILE}
if [[ $? -ne 0 ]]; then echo "no such sequence found"; fi

echo "3): contain pattern 110"
egrep ${GREP_OPTIONS} "110" ${BINARY_FILE}
if [[ $? -ne 0 ]]; then echo "no such sequence found"; fi

echo "4): contain at least three times a 1"
egrep ${GREP_OPTIONS} "1+.*1+.*1+" ${BINARY_FILE}
if [[ $? -ne 0 ]]; then echo "no such sequence found"; fi

echo "5): contain at least three consecutive 1s"
egrep ${GREP_OPTIONS} "111+" ${BINARY_FILE}
if [[ $? -ne 0 ]]; then echo "no such sequence found"; fi
