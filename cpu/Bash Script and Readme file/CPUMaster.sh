#!/bin/bash

gcc -o MyCPUBench MyCPUBench.c -lpthread

thread_count=1
operation=QP
outfile=cpu_QP_1thread.out.dat
expname=MyCPUBench

sbatch CPUSlave.sh $thread_count $operation $expname $outfile 

thread_count=2
outfile=cpu_QP_2thread.out.dat

sbatch CPUSlave.sh $thread_count $operation $expname $outfile

thread_count=4
outfile=cpu_QP_4thread.out.dat

sbatch CPUSlave.sh $thread_count $operation $expname $outfile

#---------------------------------------------------------

thread_count=1
operation=HP
outfile=cpu_HP_1thread.out.dat
expname=MyCPUBench

sbatch CPUSlave.sh $thread_count $operation $expname $outfile 

thread_count=2
outfile=cpu_HP_2thread.out.dat

sbatch CPUSlave.sh $thread_count $operation $expname $outfile

thread_count=4
outfile=cpu_HP_4thread.out.dat

sbatch CPUSlave.sh $thread_count $operation $expname $outfile

#---------------------------------------------------------

thread_count=1
operation=SP
outfile=cpu_SP_1thread.out.dat
expname=MyCPUBench

sbatch CPUSlave.sh $thread_count $operation $expname $outfile 

thread_count=2
outfile=cpu_SP_2thread.out.dat

sbatch CPUSlave.sh $thread_count $operation $expname $outfile

thread_count=4
outfile=cpu_SP_4thread.out.dat

sbatch CPUSlave.sh $thread_count $operation $expname $outfile

#---------------------------------------------------------

thread_count=1
operation=DP
outfile=cpu_DP_1thread.out.dat
expname=MyCPUBench

sbatch CPUSlave.sh $thread_count $operation $expname $outfile 

thread_count=2
outfile=cpu_DP_2thread.out.dat

sbatch CPUSlave.sh $thread_count $operation $expname $outfile

thread_count=4
outfile=cpu_DP_4thread.out.dat

sbatch CPUSlave.sh $thread_count $operation $expname $outfile













