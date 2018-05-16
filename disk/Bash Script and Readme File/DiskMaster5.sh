#!/bin/bash

gcc -o MyDiskBench MyDiskBench.c -lpthread

thread_count=1
operation=RR
buffer=1024
input_file=diskinput1.txt
outfile=disk-"$operation"-"$buffer"B-"$thread_count"thread.out.dat
expname=MyDiskBench

sbatch DiskSlave.sh $thread_count $buffer $operation $expname $outfile $input_file

thread_count=2
input_file=diskinput2.txt
outfile=disk-"$operation"-"$buffer"B-"$thread_count"thread.out.dat

sbatch DiskSlave.sh $thread_count $buffer $operation $expname $outfile $input_file

thread_count=4
input_file=diskinput3.txt
outfile=disk-"$operation"-"$buffer"B-"$thread_count"thread.out.dat

sbatch DiskSlave.sh $thread_count $buffer $operation $expname $outfile $input_file

thread_count=8
input_file=diskinput4.txt
outfile=disk-"$operation"-"$buffer"B-"$thread_count"thread.out.dat

sbatch DiskSlave.sh $thread_count $buffer $operation $expname $outfile $input_file

thread_count=16
input_file=diskinput5.txt
outfile=disk-"$operation"-"$buffer"B-"$thread_count"thread.out.dat

sbatch DiskSlave.sh $thread_count $buffer $operation $expname $outfile $input_file

thread_count=32
input_file=diskinput6.txt
outfile=disk-"$operation"-"$buffer"B-"$thread_count"thread.out.dat

sbatch DiskSlave.sh $thread_count $buffer $operation $expname $outfile $input_file

thread_count=64
input_file=diskinput7.txt
outfile=disk-"$operation"-"$buffer"B-"$thread_count"thread.out.dat

sbatch DiskSlave.sh $thread_count $buffer $operation $expname $outfile $input_file

thread_count=128
input_file=diskinput8.txt
outfile=disk-"$operation"-"$buffer"B-"$thread_count"thread.out.dat

sbatch DiskSlave.sh $thread_count $buffer $operation $expname $outfile $input_file


