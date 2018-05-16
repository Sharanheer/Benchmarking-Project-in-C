CPU Benchmark:

1) Download the file MyCPUBench.c (Source code) onto the Linux machine.
2) Download two bash script files CPUMaster.sh and CPUSlave.sh onto the Linux machine.
3) Run the CPUMaster.sh bash script as below.
     
	    ./CPUMaster.sh
		
4) The CPUMaster.sh will compile the code, run different test cases and will call CPUSlave.sh to submit jobs on different   compute nodes.
5) The results of all the tests will be written in different files using the format "cpu_$operation_$threadcount.out.dat".
6) The output will contain information in below format:
		
------------------------------------------------------------------- 
Workload   Concurrency  MyCPUBenchValue TheoreticalValue Efficiency 
 DP            1           2.217331 
------------------------------------------------------------------- 
	   
Memory Benchmark:

1) Download the file MyRAMBench.c (Source code) onto the Linux machine.
2) Download two bash script files RAMMaster.sh and RAMSlave.sh onto the Linux machine.
3) Run the RAMMaster.sh bash script as below.
     
	    ./RAMMaster.sh
		
4) The RAMMaster.sh will compile the code, run different test cases and will call RAMSlave.sh to submit jobs on different compute nodes.
5) The results of all the tests will be written in different files using the format 

		"memory_$operation_$block_size_$threadcount.out.dat".

6) The output will contain information in below format:
		
------------------------------------------------------------------------------------ 
Workload Concurrency BlockSize MyRAMBenchValue TheoreticalValue MyRAMBenchEfficiency 
 RWS         4       10485760    6.258864 
------------------------------------------------------------------------------------
  
Disk Benchmark:

1) Download the file MyDiskBench.c (Source code) onto the Linux machine.
2) Download two bash script files DiskMaster.sh and DiskSlave.sh onto the Linux machine.
3) Run the RAMMaster.sh bash script as below.
     
	    ./DiskMaster.sh
		
4) The DiskMaster.sh will compile the code, run different test cases and will call DiskSlave.sh to submit jobs on different compute nodes.
5) The results of all the tests will be written in different files using the format 

		"disk_$operation_$block_size_$threadcount.out.dat".

6) The output will contain information in below format:
		
----------------------------------------------------------------------------
Workload Concurrency BlockSize MyDiskBenchValue TheoreticalOutput Efficiency 
 RS         1          1MB         137.18 
----------------------------------------------------------------------------
	  
Network Benchmark:

1) Login to two compute nodes and download the MyNETBench.c (in server code) on one compute node and MyNETBench.c (Client code) on another computer node.
2) Using ifcongif obtain the ipaddress for the server node and use that address to connect to the server from the client.
3) Compile the codes on the respective nodes to generate the binary files using below
   
       gcc -Wall -o MyNETBench MyNETBench.c -lpthread
	   
4) Run the below commands in parallel for each test case
    (e.g) For 1 thread 1kb tcp connection run the server and client as 
	    ./MyNETBench 1 1kb T S on server node
	    ./MyNETBench 1 1kb T C on client node
		
	    format: ./MyNETBench thread-count block_size protocol mode

	    where thread_count [1,2,4,8]
		  block_size [1KB, 32KB, 1byte]
		  protocol [T/C] for TCP and UDP respectively
		  mode [S/C] for Server and Client respectively
		
5) Run for all the test cases below (test cases provided)
6) The output will be displayed on the client node after the execution is completed. For the purpose of this experiment I took output for each test case into an output file on the client node using below command.

	     ./MyNETBench thread-count block_size protocol C > network-TCP-1KB-1thread.out.dat
 
	  