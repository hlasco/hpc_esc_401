#!/usr/bin/perl
use strict;
#my @files=<sum_omp*.out>;

#foreach my $file (@files){
while(<sum_omp*.out>) {
if (/ellapsed time: ([0-9]*\.[0-9]+) seconds/) {
printf("%f\n",$1);
}
}
#}
