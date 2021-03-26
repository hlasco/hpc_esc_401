#!/bin/bash

FILE=$1
OUTPUT="triple_out.txt"

# Check if the file was specifies
if [[ -z $FILE ]]; then
    # If not, ask for the user to provide for a file
    echo "Specify an input file:"
    read FILE
    # Check if it exists
    if [[ ! -f $FILE ]]; then
        # If not, notify and exit
        echo "$FILE does not exists"
        exit 0
    fi
fi

# Clear the output file
truncate -s 0 $OUTPUT
# Loop over the lines of the input file
while read line; do
    # Append the line to the output file
    echo $line >> $OUTPUT
    # Append an empty line
	echo " " >> $OUTPUT
    echo " " >> $OUTPUT
done < $FILE
