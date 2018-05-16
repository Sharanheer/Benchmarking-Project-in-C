#!/bin/bash


thread=$1
buffer=$2
operation=$3
exp=$4
outfile=$5
input_file=$6

echo output > $outfile
./$exp $thread $buffer $operation $input_file >> $outfile

rm -rf $input_file
