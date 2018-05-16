#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>

#define GIGA_BYTE 1024*1024*1024
#define HUN_MILLION_OPERATION 100000000
long mem_per_thread, block_size;
char *input_array,*output_arr;

void *SeqRW(void *args){

	long beg_add = (long) args;
	long start_add;
	long last_add = beg_add + mem_per_thread;
	
	//printf("Value of beg_add %ld \n", beg_add);
	//printf("Value of last_add %ld \n", last_add);
	//printf("Value of mem_per_thread %ld \n", mem_per_thread);
	
	long diff;
	for(int j = 0; j < 100; j++){
		start_add = beg_add;
		diff = last_add-start_add;
		for(; diff>=block_size && start_add<last_add ; start_add+=block_size, diff=last_add-start_add){
			memcpy(&output_arr[start_add],&input_array[start_add],block_size);
		}
	}
	return NULL;
}

void *RanRW(void *args){

	long beg_add = (long) args;
	long start_add, index;
	long last_add = beg_add + mem_per_thread;
	long range = mem_per_thread-block_size;

	//printf("Value of beg_add %ld \n", beg_add);
	//printf("Value of last_add %ld \n", last_add);
	//printf("Value of mem_per_thread %ld \n", mem_per_thread);

	srand(time(NULL));
	for(int j = 0; j < 100; j++){
		start_add = beg_add;
		for(; start_add < last_add; start_add+=block_size){
			index = beg_add + rand()%range;
			memcpy(&output_arr[index],&input_array[index],block_size);
		}
		//printf("Index: %ld \n",index);
	}
	
	return NULL;
}

void *Lat_SeqRW(void *args){

	long start_add = (long) args;
	long last_add = start_add + mem_per_thread;
	
	//printf("Value of beg_add %ld \n", start_add);
	//printf("Value of last_add %ld \n", last_add);
	//printf("Value of mem_per_thread %ld \n", mem_per_thread);

	
	int count_v=0;
	for(; start_add < last_add; start_add++){
		memcpy(&output_arr[start_add],&input_array[start_add],1);
	}
	
	return NULL;
}

void *Lat_RanRW(void *args){

	long beg_add = (long) args;
	long start_add, index;
	long last_add = beg_add + mem_per_thread;
	//long range = mem_per_thread-block_size;

	//printf("Value of beg_add %ld \n", beg_add);
	//printf("Value of last_add %ld \n", last_add);
	//printf("Value of mem_per_thread %ld \n", mem_per_thread);

	srand(time(NULL));
	
	start_add = beg_add;
	for(; start_add < last_add; start_add++){
		index = beg_add + rand()%mem_per_thread;
		memcpy(&output_arr[index],&input_array[index],1);
	}
		//printf("Index: %ld \n",index);

	return NULL;
}

int main(int argc, char *argv[]){
	
	//input no_of_threads & block_size
	struct timeval start_time, stop_time;
	double t_start, t_stop, t_diff, avg_t, result, result_lat;
	int rc;
	long tid, thread_count, start_add = 0;
	void *(*addr)(void *);
	char *op[2];
	thread_count = (long)atoi(argv[1]);
	block_size = (long)atoi(argv[2]);
	pthread_t threads[thread_count];
	
	op[0] = argv[3];
	
	if(block_size == 1){
		if(strcmp(op[0],"RWS")==0){
			addr = Lat_SeqRW;
		}
		else if(strcmp(op[0],"RWR")==0){
			addr = Lat_RanRW;
		}
		else{
			printf("Please enter a valid operation argument (RWS/RWR)");
			return 0;
		}
	}
	else if(block_size == 1024 || block_size == 1048576 || block_size == 10485760){
		if(strcmp(op[0],"RWS")==0){
			addr = SeqRW;
		}
		else if(strcmp(op[0],"RWR")==0){
			addr = RanRW;
		}
		else{
			printf("Please enter a valid operation argument (RWS/RWR)");
			return 0;
		}
	}
	else{
		printf("Enter valid block size  [1KB,1MB,10MB,1Byte]");
	}
	//printf("Size of char %lu \n", sizeof(char));
	
	input_array = (char *)malloc(sizeof(char)*GIGA_BYTE);
	output_arr = (char*)malloc(sizeof(char)*GIGA_BYTE);
	
	
	if((input_array != NULL) && (output_arr != NULL)){
		//Initializing input arr with random char.
		/*for(long i = 0; i < GIGA_BYTE; i++){
			input_array[i] = (char)((rand()%10)+65);
		}*/
		memset(input_array, 'A', GIGA_BYTE);
		//printf("Successfully created the requested array size with char input\n");
		
		
		
		if(block_size == 1024 || block_size == 1048576 || block_size == 10485760){
		
			//Performing memcopy to calculate memory throughput
			mem_per_thread = GIGA_BYTE/thread_count;
			
			for(int r=0 ; r<3; r++){
				start_add = 0;

				//Measure start time
				gettimeofday(&start_time,NULL);
		
				for(tid=0; tid < thread_count; tid++){
					rc = pthread_create(&threads[tid],NULL,addr,(void *) start_add);
					if (rc){
						printf("Couldn't create thread : %ld \n" , tid);
					}
					start_add += mem_per_thread;
				}
	
				for(tid=0; tid < thread_count; tid++){
					rc = pthread_join(threads[tid], NULL);
					if (rc){
						printf("Couldn't join thread number : %ld \n" , tid);
					}
				}
			
				gettimeofday(&stop_time,NULL);
		
				t_start = start_time.tv_sec + (start_time.tv_usec/1000000.0);
				t_stop = stop_time.tv_sec + (stop_time.tv_usec/1000000.0);
				//printf("time taken %lf \n",t_stop - t_start);
				t_diff += t_stop - t_start;
			}
			avg_t = t_diff/3;
			result = 100/avg_t;
			//printf("time taken for 100GB is %lf \n", avg_t);
			//printf("Resultant throughput is %lf \n",result);
			printf("------------------------------------------------------------------------------------\n");
			printf("Workload Concurrency BlockSize MyRAMBenchValue TheoreticalValue MyRAMBenchEfficiency\n");
			printf(" %s	     %ld	        %ld	    %lf\n",op[0],thread_count,block_size,result);
			printf("------------------------------------------------------------------------------------\n");
		}
		else if(block_size == 1){
		////////////////////////////Latency Experiment////////////////////////////////
	
		
	
			mem_per_thread = HUN_MILLION_OPERATION/thread_count;
	
			for(int r=0 ; r<3; r++){
			
				start_add = 0;

				gettimeofday(&start_time,NULL);

				for(tid=0; tid < thread_count; tid++){
					rc = pthread_create(&threads[tid],NULL,addr,(void *) start_add);
					if (rc){
						printf("Couldn't create thread : %ld \n" , tid);
					}
					start_add += mem_per_thread;
				}
	
				for(tid=0; tid < thread_count; tid++){
					rc = pthread_join(threads[tid], NULL);
					if (rc){
						printf("Couldn't join thread number : %ld \n" , tid);
					}
				}
			
				gettimeofday(&stop_time,NULL);	
		
				t_start = (start_time.tv_sec*1000000.0) + start_time.tv_usec;
				t_stop = (stop_time.tv_sec*1000000.0) + stop_time.tv_usec;
				//printf("time taken %lf \n",t_stop - t_start);
				t_diff += t_stop - t_start;
			}
			avg_t = t_diff/3;
			result_lat = avg_t/HUN_MILLION_OPERATION;
			//printf("time taken in usec for transfering 100 million byte is %lf \n", avg_t);
			//printf("Resultant latency in microsecs : %lf \n",result_lat);
			printf("------------------------------------------------------------------------------------\n");
			printf("Workload Concurrency BlockSize MyRAMBenchValue TheoreticalValue MyRAMBenchEfficiency\n");
			printf(" %s	     %ld	        %ld	    %lf\n",op[0],thread_count,block_size,result_lat);
			printf("------------------------------------------------------------------------------------\n");
		}	
		free(input_array);
		free(output_arr);
	}
	else{
		printf("Couldn't allocate the requested array size\n");
	}	
	
	return 0;
}
