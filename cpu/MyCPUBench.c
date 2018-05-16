#include <stdio.h>
#include <sys/time.h>
#include <stdint.h>
#include <inttypes.h>
#include <pthread.h>
#include <string.h>
#define GIGA_BYTE 1024*1024*1024


struct argument{
	int64_t count_th;
	char *op[2];
};

void *quarter_precision(void *args){
	//char *ops[2];
	char a = 'A';
	char b = 'B';
	char c;
	struct argument *a1 = (struct argument*)args;
	int64_t counter1 = (*a1).count_th;
	//ops[0] = (*a1).op[0];
	int64_t i = INT64_C(1);
	//printf("Inside quarter");
	//printf("The value of counter1 is");
	//printf("%" PRId64 "\n", counter1);
	for(i; i <= counter1/100; i++){
		c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;
		c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;
		c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;
		c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;
		c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;
		c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;
		c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;
		c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;
		c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;
		c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;
	}
	return NULL;
}
void *half_precision(void *args){

	short a = 70, b = 720, c;
	//char *ops[2];
	struct argument *a1 = (struct argument*)args;
	int64_t counter1 = (*a1).count_th;
	//ops[0] = (*a1).op[0];
	int64_t i = INT64_C(1);
	//printf("Inside Half");
	//printf("The value of counter1 is");
	//printf("%" PRId64 "\n", counter1);
	for(i; i <= counter1/100; i++){
		c = a-b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;
		c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;
		c = a*b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a*b;c = a+b;c = a+b;
		c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;
		c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;
		c = a+b;c = a+b;c = a+b;c = a*b;c = a*b;c = a*b;c = a+b;c = a+b;c = a+b;c = a+b;
		c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a*b;
		c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;
		c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a*b;c = a+b;c = a+b;
		c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;c = a+b;
	}
	return NULL;
}
void *single_precision(void *args){

	int a = 1147483648, b = 1147483648,c;
	//char *ops[2];
	struct argument *a1 = (struct argument*)args;
	int64_t counter1 = (*a1).count_th;
	//ops[0] = (*a1).op[0];
	int64_t i = INT64_C(1);
	//printf("Inside Single");
	//printf("The value of counter1 is");
	//printf("%" PRId64 "\n", counter1);
	for(i; i <= counter1/100; i++){
		c=b+a;c=b+a;c=b+a;c=b+a;c=b+a;c=b+a;c=b+a;c=b+a;c=b+a;c=b+a;
		c=b*a;c=b*a;c=b*a;c=b*a;c=b*a;c=b*a;c=b*a;c=b*a;c=b*a;c=b*a;
		c=b+a;c=b+a;c=b+a;c=b+a;c=b+a;c=b+a;c=b+a;c=b+a;c=b+a;c=b+a;
		c=b*a;c=b*a;c=b*a;c=b*a;c=b*a;c=b*a;c=b*a;c=b*a;c=b*a;c=b*a;
		c=b+a;c=b+a;c=b+a;c=b+a;c=b+a;c=b+a;c=b+a;c=b+a;c=b+a;c=b+a;
		c=b*a;c=b*a;c=b*a;c=b*a;c=b*a;c=b*a;c=b*a;c=b*a;c=b*a;c=b*a;
		c=b+a;c=b+a;c=b+a;c=b+a;c=b+a;c=b+a;c=b+a;c=b+a;c=b+a;c=b+a;
		c=b*a;c=b*a;c=b*a;c=b*a;c=b*a;c=b*a;c=b*a;c=b*a;c=b*a;c=b*a;
		c=b+a;c=b+a;c=b+a;c=b+a;c=b+a;c=b+a;c=b+a;c=b+a;c=b+a;c=b+a;
		c=b*a;c=b*a;c=b*a;c=b*a;c=b*a;c=b*a;c=b*a;c=b*a;c=b*a;c=b*a;
	}
	return NULL;
}
void *double_precision(void *args){
	double c = 10.67,d = 720.46,a;
	//char *ops[2];
	struct argument *a1 = (struct argument*)args;
	int64_t counter1 = (*a1).count_th;
	//ops[0] = (*a1).op[0];
	int64_t i = INT64_C(1);
	//printf("Inside Double");
	//printf("The value of counter1 is");
	//printf("%" PRId64 "\n", counter1);
	for(i; i <= counter1/100; i++){
		a = c+d;a = c+d;a = c+d;a = c+d;a = c+d;a = c+d;a = c+d;a = c+d;a = c+d;a = c+d;
		a = c-d;a = c-d;a = c-d;a = c-d;a = c-d;a = c-d;a = c-d;a = c-d;a = c-d;a = c-d;
		a = c*d;a = c*d;a = c*d;a = c*d;a = c*d;a = c*d;a = c*d;a = c*d;a = c*d;a = c*d;
		a = c+d;a = c+d;a = c+d;a = c+d;a = c+d;a = c+d;a = c+d;a = c+d;a = c+d;a = c+d;
		a = c-d;a = c-d;a = c-d;a = c-d;a = c-d;a = c-d;a = c-d;a = c-d;a = c-d;a = c-d;
		a = c*d;a = c*d;a = c*d;a = c*d;a = c*d;a = c*d;a = c*d;a = c*d;a = c*d;a = c*d;
		a = c+d;a = c+d;a = c+d;a = c+d;a = c+d;a = c+d;a = c+d;a = c+d;a = c+d;a = c+d;
		a = c-d;a = c-d;a = c-d;a = c-d;a = c-d;a = c-d;a = c-d;a = c-d;a = c-d;a = c-d;
		a = c*d;a = c*d;a = c*d;a = c*d;a = c*d;a = c*d;a = c*d;a = c*d;a = c*d;a = c*d;
		a = c+d;a = c+d;a = c+d;a = c+d;a = c+d;a = c+d;a = c+d;a = c+d;a = c+d;a = c+d;
	}
	return NULL;
}
				
int main(int argc, char *argv[]){

	struct timeval t_start , t_stop;
	struct argument a1;
	
	int tid;
	int rc, rd=100;
	int no_of_threads = atoi(argv[1]);
	pthread_t threads[no_of_threads];

	//int64_t counter = INT64_C(  );
	long long int counter = (long long)rd*GIGA_BYTE;
	int64_t count_t = counter/no_of_threads;
	
	a1.count_th = count_t;
	//printf("All good..");
	a1.op[0] = argv[2];
	//printf("%s",a1.op[0]);
	//printf("The number of threads is %d \n", no_of_threads);
	//printf("Value of count_t is \n");
	//printf("%" PRId64 "\n", count_t);
	void *(*addr)(void *);
	if(strcmp((a1.op[0]),"QP")==0){
		addr = quarter_precision;
	}
	else if(strcmp((a1.op[0]),"HP")==0){
		addr = half_precision;
	}
	else if(strcmp((a1.op[0]),"SP")==0){
		addr = single_precision;
	}
	else if(strcmp((a1.op[0]),"DP")==0){
		addr = double_precision;
	}
	else{
		printf("Enter a valid operation");
		return 0;
	}
	
	//printf("Creating threads... \n");
	
	double timer_diff = 0;

	for(int r = 0; r < 3; r++){
	gettimeofday(&t_start, NULL);

	for(tid=0; tid < no_of_threads; tid++){
    	rc = pthread_create(&threads[tid],NULL,addr,(void *) &a1);
		if (rc){
			printf("Coudn't create thread : %d \n" , tid);
		}
	}
	
	for(tid=0; tid < no_of_threads; tid++){
		rc = pthread_join(threads[tid], NULL);
		if (rc){
			printf("Coudn't join thread number : %d \n" , tid);
		}
	}

	gettimeofday(&t_stop, NULL);
	
	
	double start_timer = t_start.tv_sec+(t_start.tv_usec/1000000.0);
	double stop_timer = t_stop.tv_sec+(t_stop.tv_usec/1000000.0);
	//printf("The value of the start timer is %lf \n", start_timer);
	//printf("The value of the stop timer is %lf \n", stop_timer);
	//printf("Time taken to perform 1 Trillion operations is %lf \n", (stop_timer-start_timer));
	timer_diff += stop_timer - start_timer;
	}
	double avg_diff = timer_diff/3;
	//printf("Avg time diff is : %lf  \n",avg_diff);
	double result = rd/avg_diff;
	//printf("The result of the GOPS is : %lf \n", result);
	printf("-------------------------------------------------------------------\n");
	printf("Workload   Concurrency  MyCPUBenchValue TheoreticalValue Efficiency\n");
	printf(" %s		%i	   %lf\n",a1.op[0],no_of_threads,result);
	printf("-------------------------------------------------------------------\n");
	
	return 0;
}

