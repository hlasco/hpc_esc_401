#!/bin/bash

for d in sum_omp*.out; do
#if (/ellapsed time: ([0-9]*\.[0-9]+) seconds/) {
c=$(cat $d);
c=${c%seconds*}
c=${c#*time: }

d=${d#*omp\_}
d=${d%\.*}
echo $d $c
done
