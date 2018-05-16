#!/bin/bash

gcc -o MyDiskBench MyDiskBench.c -lpthread

thread_count=4
operation=RR
buffer=100
input_file=diskinput1.txt
outfile=disk-"$operation"-"$buffer"MB-"$thread_count"thread.out.dat
expname=MyDiskBench

sbatch DiskSlave.sh $thread_count $buffer $operation $expname $outfile $input_file

thread_count=2
input_file=diskinput2.txt
outfile=disk-"$operation"-"$buffer"MB-"$thread_count"thread.out.dat

sbatch DiskSlave.sh $thread_count $buffer $operation $expname $outfile $input_file

thread_count=1
input_file=diskinput3.txt
outfile=disk-"$operation"-"$buffer"MB-"$thread_count"thread.out.dat

sbatch DiskSlave.sh $thread_count $buffer $operation $expname $outfile $input_file

thread_count=4
buffer=10
input_file=diskinput4.txt
outfile=disk-"$operation"-"$buffer"MB-"$thread_count"thread.out.dat
expname=MyDiskBench

sbatch DiskSlave.sh $thread_count $buffer $operation $expname $outfile $input_file

thread_count=2
input_file=diskinput5.txt
outfile=disk-"$operation"-"$buffer"MB-"$thread_count"thread.out.dat

sbatch DiskSlave.sh $thread_count $buffer $operation $expname $outfile $input_file

thread_count=1
input_file=diskinput6.txt
outfile=disk-"$operation"-"$buffer"MB-"$thread_count"thread.out.dat

sbatch DiskSlave.sh $thread_count $buffer $operation $expname $outfile $input_file

buffer=1
thread_count=4
input_file=diskinput7.txt
outfile=disk-"$operation"-"$buffer"MB-"$thread_count"thread.out.dat
expname=MyDiskBench

sbatch DiskSlave.sh $thread_count $buffer $operation $expname $outfile $input_file

thread_count=2
input_file=diskinput8.txt
outfile=disk-"$operation"-"$buffer"MB-"$thread_count"thread.out.dat

sbatch DiskSlave.sh $thread_count $buffer $operation $expname $outfile $input_file

thread_count=1
input_file=diskinput9.txt
outfile=disk-"$operation"-"$buffer"MB-"$thread_count"thread.out.dat

sbatch DiskSlave.sh $thread_count $buffer $operation $expname $outfile $input_file

