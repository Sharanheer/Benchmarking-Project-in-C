#!/bin/bash

thread=$1
operation=$2
exp=$3
outfile=$4

echo output > $4
./$exp $thread $operation >> $4
