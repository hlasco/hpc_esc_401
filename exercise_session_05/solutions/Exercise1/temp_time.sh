#!/bin/bash

RE="Temperature\: ([0-9]+\.[0-9]+) deg at time\: ([0-9]+\.[0-9]+) sec"
TEMP=0
n=0
:>out.txt
while read A; do
	if [[ "$A" =~ $RE ]] ; then
		echo "${BASH_REMATCH[1]}   ${BASH_REMATCH[2]}" >> out.txt
		TEMP=$(echo "scale=5;${TEMP} + ${BASH_REMATCH[1]}" | bc)
		n=$((n+1))
                echo "temp: ${TEMP} n: ${n}" 

 	fi
done
AVERAGE=$(echo "scale=5;$TEMP/$n" | bc)
echo "Average time: ${AVERAGE}"
