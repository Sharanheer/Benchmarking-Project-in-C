#define _GNU_SOURCE
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <fcntl.h>

#include <unistd.h>
#define ONE_GB 1024*1024*1024

FILE *fp;
int file_descriptor;
char *buff;
long block_size;
int64_t mem_per_thread;
char *input_array;
int size;
long rd = 10;  //delete it later
//Block size needs to be mentioned in 1,10,100 MB

void *SeqR(void *args){

	long beg_add = (long) args;
	long start_add, r_size;
	long last_add = beg_add + mem_per_thread;
	
	//printf("Value of beg_add %ld \n", beg_add);
	//printf("Value of last_add %ld \n", last_add);
	//printf("Value of mem_per_thread %ld \n", mem_per_thread);

	start_add = beg_add;
	file_descriptor = fileno(fp);
	long block_size1 = block_size*1024*1024;
	
	for(; start_add<last_add; start_add+=block_size1){
		r_size = pread(file_descriptor, buff, block_size1, start_add);
		//printf("start_add: %ld\n",start_add);
	}
	if(r_size>0){
		//printf("successfully read the file\n");
	}
	return NULL;
}

void *SeqW(void *args){

	long beg_add = (long) args;
	long start_add, w_size = 0;
	long last_add = beg_add + mem_per_thread;
	
	//printf("Value of beg_add %ld \n", beg_add);
	//printf("Value of last_add %ld \n", last_add);
	//printf("Value of mem_per_thread %ld \n", mem_per_thread);

	start_add = beg_add;
	file_descriptor = fileno(fp);
	long block_size1 = block_size*1024*1024;
	
	for(; start_add<last_add; start_add+=block_size1){
		w_size += pwrite(file_descriptor, buff, block_size1, start_add);
		if(w_size == -1){
			printf("SOme error writing data \n");
		}
	}
	//printf("bytes wrote on the file %ld\n",w_size);
	if(w_size>0){
		//printf("successfully wrote the file\n");
	}
	return NULL;
}

void *RanR(void *args){

	long beg_add = (long) args;
	long start_add, index, r_size;
	long last_add = beg_add + mem_per_thread;
	long block_size1 = block_size*1024*1024;
	long range = mem_per_thread - block_size1;

	//printf("Value of beg_add %ld \n", beg_add);
	//printf("Value of last_add %ld \n", last_add);
	//printf("Value of mem_per_thread %ld \n", mem_per_thread);
	
	file_descriptor = fileno(fp);
	srand(time(NULL));
	start_add = beg_add;
	for(; start_add<last_add; start_add+=block_size1){
		index = beg_add + rand()%range;
		r_size = pread(file_descriptor, buff, block_size1, index);
		//printf("start_add: %ld\n",start_add);
	}
	if(r_size>0){
		//printf("successfully read the file");
	}
	return NULL;
}


void *RanW(void *args){

	long beg_add = (long) args;
	long start_add, w_size = 0, index;
	long last_add = beg_add + mem_per_thread;
	long block_size1 = block_size*1024*1024;
	long range = mem_per_thread - block_size1;
	
	//printf("Value of beg_add %ld \n", beg_add);
	//printf("Value of last_add %ld \n", last_add);
	//printf("Value of mem_per_thread %ld \n", mem_per_thread);
	
	start_add = beg_add;
	file_descriptor = fileno(fp);
	srand(time(NULL));

	for(; start_add<last_add; start_add+=block_size1){
		index = beg_add + rand()%range;
		w_size += pwrite(file_descriptor, buff, block_size1, index);
	}
	//printf("bytes wrote on the file %ld\n",w_size);
	if(w_size>0){
		//printf("successfully wrote the file");
	}
	return NULL;
}

void *RanRL(void *args){

	long beg_add = (long) args;
	long start_add, index, r_size;
	long last_add = beg_add + mem_per_thread;
	
	long range = mem_per_thread-block_size;

	//printf("Value of beg_add %ld \n", beg_add);
	//printf("Value of last_add %ld \n", last_add);
	//printf("Value of mem_per_thread %ld \n", mem_per_thread);
	
	file_descriptor = fileno(fp);
	srand(time(NULL));
	start_add = beg_add;
	for(; start_add<last_add; start_add+=block_size){
		index = beg_add + rand()%range;
		r_size = pread(file_descriptor, buff, block_size, index);
		//printf("start_add: %ld\n",start_add);
		//printf("bytes read from the file %ld\n",r_size);
	}
	if(r_size>0){
		//printf("successfully read the file");
	}
	return NULL;
}


void *RanWL(void *args){

	long beg_add = (long) args;
	long start_add, w_size, index;
	long last_add = beg_add + mem_per_thread;
	long range = mem_per_thread - block_size;
	
	//printf("Value of beg_add %ld \n", beg_add);
	//printf("Value of last_add %ld \n", last_add);
	//printf("Value of mem_per_thread %ld \n", mem_per_thread);
	
	start_add = beg_add;
	file_descriptor = fileno(fp);
	srand(time(NULL));

	for(; start_add<last_add; start_add+=block_size){
		index = beg_add + rand()%range;
		w_size = pwrite(file_descriptor, buff, block_size, index);
		//printf("bytes wrote on the file %ld\n",w_size);
	}
	if(w_size>0){
		//printf("successfully wrote the file");
	}
	return NULL;
}


int main(int argc, char *argv[]){
	

	struct timeval start_time, stop_time;
	double t_start, t_stop, t_diff, result;
	int rc;
	long tid, thread_count, start_add = 0;
	char *op[2];
	void *(*addr)(void *);
	thread_count = (long)atoi(argv[1]);
	block_size = (long)atoi(argv[2]);  //Need to be entered as 1MB, 10MB, 100MB
	pthread_t threads[thread_count];
	op[0] = argv[3];
	char *fname[50];
	fname[0] = argv[4];
	//printf("name of the input file : %s\n",fname[0]);
	
	if(block_size == 1 || block_size == 10 || block_size == 100){
		if(strcmp(op[0],"RS")==0){
			addr = &SeqR;
		}
		else if(strcmp(op[0],"WS")==0){
			addr = &SeqW;
		}
		else if(strcmp(op[0],"RR")==0){
			addr = &RanR;
		}
		else if(strcmp(op[0],"WR")==0){
			addr = &RanW;
		}
		else{
			printf("Please enter a valid operation argument (RS/WS/RR/WR) for block_size of 1,10,100MB\n");
			return 0;
		}
	}
	else if(block_size == 1024){
		if(strcmp(op[0],"RR")==0){
		addr = &RanRL;
		}
		else if(strcmp(op[0],"WR")==0){
			addr = &RanWL;
		}
		else{
			printf("Please enter a valid operation argument (RR/WR) for block_size of 1024Bytes\n");
			return 0;
		}
	}
	else{
		printf("Please enter a valid block size\n");
		return 0;
	}
	if(block_size == 1 || block_size == 10 || block_size == 100){
		buff=(char *)malloc(sizeof(char)*block_size*1024*1024);
		input_array = (char *)malloc(sizeof(char)*ONE_GB);
	
		//For optimization can use memset later...
		/*for(long i = 0; i < ONE_GB; i++){
			input_array[i] = (char)((rand()%10)+65);
		}*/
		memset(input_array, 'A', ONE_GB);
		size = strlen(input_array);
		input_array[size+1] = '\0';    //Adding a null character
		fp = fopen(fname[0],"w+");
		//file_descriptor = open("file1.txt", O_RDWR | O_CREAT | O_DIRECT | O_LARGEFILE | O_SYNC, 0666);
		//printf("value of the file descriptor is : %d\n",file_descriptor);
		//printf("File is now open \n");
		file_descriptor = fileno(fp);  //INITIALIZING FILE DESCRIPTOR...	
		//printf("Size of the input array of 1GB is:  %d\n",size);
		int64_t off = 0;
		int64_t w_size = 0;
		if(strcmp(op[0],"RR")==0 || strcmp(op[0],"RS")==0){
			for(int i=0; i<rd;i++){
				w_size += pwrite(file_descriptor, input_array, size, off);
				off += ONE_GB;
				//printf("value of the counter is %d\n",i);
				//printf("value of pwrite is \n");
				//printf("%" PRId64 "\n", w_size);
			}
			//printf("Bytes written to the file using pwrite :\n");
			//printf("%" PRId64 "\n", w_size);
			//printf("File loaded with 10GB of random char \n");
		}	
		if(strcmp(op[0],"WR")==0 || strcmp(op[0],"WS")==0){
			memcpy(&buff[0], &input_array[0], block_size*1024*1024);
		}
	  
		fseek(fp, 0, SEEK_SET);
		
		int64_t large = INT64_C(rd*1024*1024*1024); 
		//printf("Value of large : \n");
		//printf("%" PRId64 "\n", large);
	
		mem_per_thread = large/thread_count;
	
		gettimeofday(&start_time, NULL);
	
		//Creating threads...
		for(tid=0; tid < thread_count; tid++){
			rc = pthread_create(&threads[tid],NULL,addr,(void *) start_add);
			if (rc){
				printf("Couldn't create thread : %ld \n" , tid);
			}
			start_add += mem_per_thread;
		}
		//Joining all the threads...
		for(tid=0; tid < thread_count; tid++){
			rc = pthread_join(threads[tid], NULL);
			if (rc){
				printf("Couldn't join thread number : %ld \n" , tid);
			}
		}
	
		gettimeofday(&stop_time, NULL);
	
		//printf("content read from the file \n");
	
		t_start = start_time.tv_sec + (start_time.tv_usec/1000000.0);
		t_stop = stop_time.tv_sec + (stop_time.tv_usec/1000000.0);
		//printf("time taken %lf \n",t_stop - t_start);
		t_diff = t_stop - t_start;
		result = (rd*1024)/t_diff;
		//printf("time taken for 10GB is %lf \n", t_diff);
		//printf("Resultant throughput for MB/SEC is : %lf \n",result);
		
		printf("-------------------------------------------------------------------------------------\n");
		printf("Workload Concurrency BlockSize MyDiskBenchThroughput TheoreticalThroughput Efficiency\n");
		printf(" %s	     %ld	        %ldMB	    %lf\n",op[0],thread_count,block_size,result);
		printf("-------------------------------------------------------------------------------------\n");
	}
	else if(block_size == 1024){
	
		buff=(char *)malloc(sizeof(char)*block_size);
		input_array = (char *)malloc(sizeof(char)*ONE_GB);
	
		/*for(long i = 0; i < ONE_GB; i++){
			input_array[i] = (char)((rand()%10)+65);
		}*/
		
		memset(input_array, 'A', ONE_GB);
		fp = fopen(fname[0],"w+");
	
		//printf("File is now open \n");
		//INITIALIZING FILE DESCRIPTOR...
		file_descriptor = fileno(fp);
		size = strlen(input_array);
		//printf("Size of the input array of 1GB %d\n",size);
		input_array[size+1] = '\0';    //Adding a null character
	
		if(strcmp(op[0],"RR")==0){
			long w_size = pwrite(file_descriptor, input_array, size, 0);
			//printf("Bytes written to the file using pwrite : %ld\n",w_size);
			//printf("Wrote 1GB of random char \n");
		}
		if(strcmp(op[0],"WR")==0){
			memcpy(&buff[0], &input_array[0], block_size);
			//buff[strlen(buff)+1] = '\0';
		}
	
		fseek(fp, 0, SEEK_SET);
	
		mem_per_thread = ONE_GB/thread_count;
	
		gettimeofday(&start_time, NULL);
	
		//Creating threads...
		for(tid=0; tid < thread_count; tid++){
			rc = pthread_create(&threads[tid],NULL,addr,(void *) start_add);
			if (rc){
				printf("Couldn't create thread : %ld \n" , tid);
			}
			start_add += mem_per_thread;
		}
		//Joining all the threads...
		for(tid=0; tid < thread_count; tid++){
			rc = pthread_join(threads[tid], NULL);
			if (rc){
				printf("Couldn't join thread number : %ld \n" , tid);
			}
		}
	
		gettimeofday(&stop_time, NULL);
	
	/////////////////////////////////Calculation Area////////////////////////////////////////
	
		t_start = start_time.tv_sec + (start_time.tv_usec/1000000.0);
		t_stop = stop_time.tv_sec + (stop_time.tv_usec/1000000.0);
		//printf("time taken %lf \n",t_stop - t_start);
		t_diff = t_stop - t_start;
		result = 1048576/t_diff;  //Need to clarify if 1000000 or 1048576
		//printf("time taken for 1GB in secs %lf \n", t_diff);
		//printf("Resultant IOPS for 1KB is : %lf \n",result);
	
		double time_per_access = (t_diff/1048576)*1000;  //time in millisec for single access(1KB)
		//printf("Resultant time_per_access/latency for 1KB is : %lf \n",time_per_access);
		
		printf("-------------------------------------------------------------------------------------\n");
		printf("Workload Concurrency BlockSize MyDiskBenchIOPS TheoreticalThroughput Efficiency\n");
		printf(" %s	     %ld	        %ldB	    %lf\n",op[0],thread_count,block_size,result);
		printf("-------------------------------------------------------------------------------------\n");
		
		printf("Workload Concurrency BlockSize MyDiskBenchLatency TheoreticalThroughput Efficiency\n");
		printf(" %s	     %ld	        %ldB	    %lf\n",op[0],thread_count,block_size,time_per_access);
		printf("-------------------------------------------------------------------------------------\n");
	}


	fclose(fp);
	free(buff);
	free(input_array);
	return 0;
}
