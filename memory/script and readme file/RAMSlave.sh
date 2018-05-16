#!/bin/bash


thread=$1
buffer=$2
operation=$3
exp=$4
outfile=$5

echo output > $outfile
./$exp $thread $buffer $operation >> $outfile
