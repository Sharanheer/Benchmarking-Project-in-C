#!/bin/bash

gcc -o MyRAMBench MyRAMBench.c -lpthread

thread_count=4
operation=RWS
buffer=1024
outfile=memory-"$operation"-"$buffer"-"$thread_count"thread.out.dat
expname=MyRAMBench

sbatch RAMSlave.sh $thread_count $buffer $operation $expname $outfile

thread_count=2
outfile=memory-"$operation"-"$buffer"-"$thread_count"thread.out.dat

sbatch RAMSlave.sh $thread_count $buffer $operation $expname $outfile

thread_count=1
outfile=memory-"$operation"-"$buffer"-"$thread_count"thread.out.dat

sbatch RAMSlave.sh $thread_count $buffer $operation $expname $outfile

thread_count=4
buffer=1048576
outfile=memory-"$operation"-"$buffer"-"$thread_count"thread.out.dat

sbatch RAMSlave.sh $thread_count $buffer $operation $expname $outfile

thread_count=2
outfile=memory-"$operation"-"$buffer"-"$thread_count"thread.out.dat

sbatch RAMSlave.sh $thread_count $buffer $operation $expname $outfile

thread_count=1
outfile=memory-"$operation"-"$buffer"-"$thread_count"thread.out.dat

sbatch RAMSlave.sh $thread_count $buffer $operation $expname $outfile

thread_count=4
buffer=10485760
outfile=memory-"$operation"-"$buffer"-"$thread_count"thread.out.dat

sbatch RAMSlave.sh $thread_count $buffer $operation $expname $outfile

thread_count=2
outfile=memory-"$operation"-"$buffer"-"$thread_count"thread.out.dat

sbatch RAMSlave.sh $thread_count $buffer $operation $expname $outfile

thread_count=1
outfile=memory-"$operation"-"$buffer"-"$thread_count"thread.out.dat

sbatch RAMSlave.sh $thread_count $buffer $operation $expname $outfile

thread_count=4
buffer=1
outfile=memory-"$operation"-"$buffer"-"$thread_count"thread.out.dat

sbatch RAMSlave.sh $thread_count $buffer $operation $expname $outfile

thread_count=2
outfile=memory-"$operation"-"$buffer"-"$thread_count"thread.out.dat

sbatch RAMSlave.sh $thread_count $buffer $operation $expname $outfile

thread_count=1
outfile=memory-"$operation"-"$buffer"-"$thread_count"thread.out.dat

sbatch RAMSlave.sh $thread_count $buffer $operation $expname $outfile














