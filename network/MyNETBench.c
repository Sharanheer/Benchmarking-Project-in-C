#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/time.h>
#define GIGA_BYTE 1024*1024*1024
#define MEGA_BYTE 1024*1024

//int sock_id;
int sock_id, new_soc;
double data_per_thread;
long block_size;

void *tcp_send(void *args){

	int sock_ids;
	struct sockaddr_in client_socs;
	
	if((sock_ids = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("Error in socket creation \n");
		return NULL;
	}
	memset(&client_socs, '0', sizeof(client_socs));
	client_socs.sin_family = AF_INET;
	client_socs.sin_port = htons(8080);
	
	//Converting ip add to byte code
	
	if(inet_pton(AF_INET, "192.168.9.65", &client_socs.sin_addr)<= 0)
	{
		printf("Error in conversion from decimal to byte code\n");
		return NULL;
	}
	
	if(connect(sock_ids, (struct sockaddr *)&client_socs, sizeof(client_socs)) < 0)
	{
		printf("Connection establishment failed\n");
		return NULL;
	}


	long long int max = (long long)(data_per_thread*GIGA_BYTE);
	//printf("Value of max is : %lld\n", max);
	long block = block_size*1024;
	//printf("Value of block is : %lld\n", block);
	char *buffer =(char *)malloc(block_size*1024*sizeof(char));
	memset(buffer,'A',block);
	long long int data;
	
	printf("sending...\n");
	for(long long int i=0ll; i < max; i+=data){
		
		data = (long long)send(sock_ids, buffer, strlen(buffer), 0);
		//printf("Value of data is : %lld\n", data);
		//printf("Value of i is : %lld\n", i);
	}
	return NULL;
}

void *tcp_receive(void *input){
																
	int t_soc = (long)input;
	long long int bytes = 0ll, valread;
	char *buffer =(char *)malloc(block_size*1024*sizeof(char));
	long long int max = (long long)(data_per_thread*GIGA_BYTE);
	//printf("Value of max is : %lld\n", max);
	//long i;
	//long long block = (long long)block_size*1024;
	//printf("Value of block is : %lld\n", block);
	printf("Receiving Data...\n");
	for(long long int i = 0ll ; i < max; i+=valread){

		valread = (long long)read(t_soc, buffer, block_size*1024);
		//printf("Value of i is : %lld\n", i);
    	//printf("Bytes received  %lld\n",valread);
    	
    	bytes+=valread;
    	//printf("Bytes Transferred %lld\n",bytes);
    	//memset(buffer, 0, block_size*1024);
		if(valread == 0)
			return NULL;

    	
	}
	printf("Bytes received  %lld\n",valread);
	printf("Bytes Transferred %lld\n",bytes);
	return NULL;
}

void *udp_send(void *args){

	int port_num = (int)args;
	int sock_id;
	struct sockaddr_in client_soc, server_soc;
	socklen_t slen = sizeof(server_soc);
	
	if((sock_id = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		printf("Error in socket creation \n");
		return NULL;
	}
	
    
    memset(&server_soc, 0, sizeof(server_soc));
    server_soc.sin_family = AF_INET;
    //server_soc.sin_addr.s_addr = htonl(0x7f000001);
    server_soc.sin_port = htons(port_num);

	if(inet_pton(AF_INET, "192.168.9.65", &server_soc.sin_addr)<= 0)
	{
		printf("Error in conversion from decimal to byte code\n");
		return NULL;
	}
	
	long long int max = (long long)(data_per_thread*GIGA_BYTE);
	//printf("Value of max is : %lld\n", max);
	long block = block_size*1024;
	//printf("Value of block is : %lld\n", block);
	char *buffer =(char *)malloc(block_size*1024*sizeof(char));
	memset(buffer,'A',block);
	long long int data, valread;
	
	printf("sending...\n");
	for(long long int i=0ll; i < max; i+=data){
		
		data = (long long)sendto(sock_id, buffer, strlen(buffer), 0, (struct sockaddr *)&server_soc, slen);
		if(data<0){
			printf("Problem sending data to the server\n");
		}
		
	}
	sleep(0.5);
	sendto(sock_id, 0, 0, 0, (struct sockaddr *)&server_soc, slen);
	return NULL;
}

void *udp_receive(void *args){
		
	int port_num=(int)args;													
	int sock_id;
	struct sockaddr_in s_socket,c_socket;
	int s_size = sizeof(s_socket);
	int c_size = sizeof(c_socket);

	if((sock_id = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		printf("Error in socket creation \n");
		return NULL;
	}
	
	int opt = 1;
	
	if(setsockopt(sock_id, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
	{
		printf("Error in sockopt");
		return NULL;
	}
	
	memset( &s_socket, 0, sizeof(s_socket) );
	s_socket.sin_family = AF_INET;
	s_socket.sin_port = htons(port_num);
	//s_socket.sin_addr.s_addr = htonl(0x7f000001);
	
	if(inet_pton(AF_INET, "192.168.9.65", &s_socket.sin_addr)<= 0)
	{
		printf("Error in conversion from decimal to byte code\n");
		return NULL;
	}

	if(bind(sock_id, (struct sockaddr *)&s_socket, sizeof(s_socket))<0)
    	{
    	perror("bind failed");
        exit(EXIT_FAILURE);
   	}

	
	long long int bytes = 0ll, valread, data;
	char *buffer =(char *)malloc(block_size*1024*sizeof(char));
	long long int max = (long long)(data_per_thread*GIGA_BYTE);
	
	long block = block_size*1024;
	printf("Receiving Data...\n");
	for(long long int i = 0ll ; i < max; i+=valread){
		valread = (long long)recvfrom(sock_id, buffer, block, 0, (struct sockaddr *)&c_socket, &c_size);
		
    	
    	bytes+=valread;
    	
		if(valread == 0){
			printf("Value of valread is zero, loop should terminate\n");
			return NULL;
		}
		if(valread < 0){
			printf("Value of valread is less than zero, loop should terminate\n");
			return NULL;
		}
		
		memset(buffer, 0, block_size*1024);
    	
	}
	printf("Bytes received  %lld\n",valread);
	printf("Bytes Transferred %lld\n",bytes);
	return NULL;
}

void *tcp_sendL(void *args){

	int sock_id;
	struct sockaddr_in client_soc;
	
	if((sock_id = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("Error in socket creation \n");
		return NULL;
	}
	memset(&client_soc, '0', sizeof(client_soc));
	client_soc.sin_family = AF_INET;
	client_soc.sin_port = htons(8080);
	
	//Converting ip add to byte code
	if(inet_pton(AF_INET, "192.168.9.65", &client_soc.sin_addr)<= 0)
	{
		printf("Error in conversion from decimal to byte code\n");
		return NULL;
	}
	
	if(connect(sock_id, (struct sockaddr *)&client_soc, sizeof(client_soc)) < 0)
	{
		printf("Connection establishment failed\n");
		return NULL;
	}

	long max = data_per_thread*MEGA_BYTE;
	//printf("Value of max is : %ld\n", max);
	char *buffer =(char *)malloc(sizeof(char));
	memset(buffer,'A',1);
	long data, valread;
	
	printf("sending...\n");
	for(long i=0; i < max; i+=data){
		
		data = send(sock_id, buffer, strlen(buffer), 0);
		memset(buffer, 0, 1);
		if(data == 0){
			printf("Client couldn't send data to the server\n");
			return NULL;
		}	
		valread = read(sock_id, buffer, 1);
	}
	return NULL;
}

void *tcp_receiveL(void *input){
																
	int t_soc = (long)input;
	long bytes = 0, valread, data;
	char *buffer =(char *)malloc(sizeof(char));
	long max = data_per_thread*MEGA_BYTE;
	//printf("Value of max is : %ld\n", max);
	//printf("Receiving Data...\n");
	for(long i = 0 ; i < max; i+=valread){
		valread = read(t_soc, buffer, 1);
    	bytes+=valread;
		if(valread == 0){
			printf("Server couldn't receive any data from the client \n");
			return NULL;
		}
		data = send(t_soc, buffer, strlen(buffer), 0);
    	
    	memset(buffer, 0, 1);
	}
	return NULL;
}

void *udp_sendL(void *args){
	int port_num = (int) args;
	int sock_id;
	struct sockaddr_in client_soc, server_soc;
	socklen_t slen = sizeof(server_soc);
	
	if((sock_id = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		printf("Error in socket creation \n");
		return NULL;
	}
    
    memset(&server_soc, 0, sizeof(server_soc));
    server_soc.sin_family = AF_INET;
   // server_soc.sin_addr.s_addr = htonl(0x7f000001);
    server_soc.sin_port = htons(port_num);
	
	if(inet_pton(AF_INET, "192.168.9.65", &server_soc.sin_addr)<= 0)
	{
		printf("Error in conversion from decimal to byte code\n");
		return NULL;
	}

	long max = data_per_thread*MEGA_BYTE;
	//printf("Value of max is : %ld\n", max);
	
	char *buffer =(char *)malloc(sizeof(char));
	memset(buffer,'A',1);
	long data,valread;
	
	printf("sending...\n");
	for(long i=0; i < max; i+=data){
		
		data = sendto(sock_id, buffer, strlen(buffer), 0, (struct sockaddr *)&server_soc, slen);
		if(data<=0){
			printf("Problem sending data to the server\n");
			return NULL;
		}
		//printf("Value of data send is : %ld\n", data);
		memset(buffer,0,1);
		valread = recvfrom(sock_id, buffer, 1, 0, NULL, 0);
		if(valread<=0){
			printf("Problem reading data from server...\n");
			return NULL;
		}
		
		//printf("Value of valread is : %ld\n", valread);
	}
	return NULL;
}

void *udp_receiveL(void *input){
																
	int sock_id;
	int port_num = (int) input;
	struct sockaddr_in s_socket,c_socket;
	int s_size = sizeof(s_socket);
	int c_size = sizeof(c_socket);

	if((sock_id = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		printf("Error in socket creation \n");
		return NULL;
	}
	
	int opt = 1;
	if(setsockopt(sock_id, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
	{
		printf("Error in sockopt");
		return NULL;
	}
	
	memset( &s_socket, 0, sizeof(s_socket) );
	s_socket.sin_family = AF_INET;
	s_socket.sin_port = htons(port_num);
	//s_socket.sin_addr.s_addr = htonl(0x7f000001);
	
	if(inet_pton(AF_INET, "192.168.9.65", &s_socket.sin_addr)<= 0)
	{
		printf("Error in conversion from decimal to byte code\n");
		return NULL;
	}

	if(bind(sock_id, (struct sockaddr *)&s_socket, sizeof(s_socket))<0)
    	{
    	perror("bind failed");
        exit(EXIT_FAILURE);
   	}

	
	long bytes = 0, valread, data;
	char *buffer =(char *)malloc(sizeof(char));
	long max = data_per_thread*MEGA_BYTE;
	//printf("Value of max is : %ld\n", max);
	
	printf("Receiving Data...\n");
	for(long i = 0 ; i < max; i+=valread){
	
		valread = recvfrom(sock_id, buffer, 1, 0, (struct sockaddr *)&c_socket, &c_size);
		
		//printf("value of buffer after read operation%s\n",buffer);
    	//printf("Bytes received  %ld\n",valread);
    	
    	bytes+=valread;
    	//printf("Bytes Transferred from client to server till now : %ld\n",bytes);
    	
		if(valread <= 0){
			printf("Value of valread is zero, loop should terminate\n");
			return NULL;
		}
		data = sendto(sock_id, buffer, strlen(buffer), 0, (struct sockaddr *)&c_socket, c_size);
		if(data<=0){
			printf("Problem sending data to the client\n");
			return NULL;
		}
		//printf("Bytes sent back to client  %ld\n",data);
		memset(buffer, 0, 1);
		//printf("value of buffer after reset %s\n",buffer);
    	//printf("---------------\n");
	}
	//printf("Bytes received  %ld\n",valread);
	//printf("Bytes Transferred %ld\n",bytes);
	return NULL;
}

//FILL ME IN
int main(int argc, char **argv)
{
	//struct sockaddr_in client_soc;
	struct timeval start_time, stop_time;
	double t_start, t_stop, t_diff, result;
	int rc, rd =5;
	long tid, thread_count;
	char *op[2];
	char *type[2];
	void *(*addr)(void *);
	thread_count = (long)atoi(argv[1]);
	block_size = (long)atoi(argv[2]);  //Need to be entered as 1KB, 32KB, [0 for 1Byte]

	
	pthread_t threads[thread_count];
	op[0] = argv[3];
	type[0] = argv[4]; //Client(c) or Server(s)
	
	if(block_size == 1 || block_size == 32){
		if(strcmp(type[0], "C")==0){
	
			if(strcmp(op[0], "T")==0){
				addr = &tcp_send;
			
				//Calculating data per thread, considering 100 as 100GB of data
				data_per_thread = ((double)rd/thread_count); 
				
				//printf("value of data_per_thread : %lf/n",data_per_thread);		
				
				gettimeofday(&start_time,NULL);
		
				for(tid=0; tid < thread_count; tid++){
					rc = pthread_create(&threads[tid],NULL,addr,NULL);
					if (rc){
						printf("Couldn't create thread : %ld \n" , tid);
					}
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
				printf("time taken %lf \n",t_stop - t_start);
				t_diff = t_stop - t_start;
	
				result = (1024*rd)/t_diff;
				//printf("time taken for 100GB is %lf \n", t_diff);
				//printf("Resultant throughput is %lf \n",result);
				printf("-------------------------------------------------------------------------------------\n");
				printf("Protocol Concurrency BlockSize MyNETBenchValue TheoreticalValue MyNETBenchEfficiency\n");
				printf(" %s	     %ld	        %ldKB	  %lf\n","TCP",thread_count,block_size,result);
				printf("-------------------------------------------------------------------------------------\n");
				
			}
			else if(strcmp(op[0],"U")==0){
				addr = &udp_send;
			
				data_per_thread = ((double)rd/thread_count); 
				int port = 8080;
	
	
				gettimeofday(&start_time,NULL);
				
				for(tid=0; tid < thread_count; tid++){
					rc = pthread_create(&threads[tid],NULL,addr,(void *)port);
					if (rc){
						printf("Couldn't create thread : %ld \n" , tid);
					}
					port++;
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
				printf("time taken %lf \n",t_stop - t_start);
				t_diff = t_stop - t_start;
	
				result = (1024*rd)/t_diff;
				//printf("time taken for 100GB is %lf \n", t_diff);
				//printf("Resultant throughput is %lf \n",result);
				printf("-------------------------------------------------------------------------------------\n");
				printf("Protocol Concurrency BlockSize MyNETBenchValue TheoreticalValue MyNETBenchEfficiency\n");
				printf(" %s	     %ld	        %ldKB	  %lf\n","UDP",thread_count,block_size,result);
				printf("-------------------------------------------------------------------------------------\n");
			}
			else{
				printf("Enter a valid protocol type [T/U] for TCP or UDP respectively\n");
				return 0;
			}
		}else if(strcmp(type[0], "S")==0){
			if(strcmp(op[0],"T")==0){
				
				struct sockaddr_in s_socket;
				int s_size = sizeof(s_socket);
				addr = &tcp_receive;
				if((sock_id = socket(AF_INET, SOCK_STREAM, 0)) == 0)
				{
					printf("Error in socket creation \n");
					return -1;
				}
	
				int opt = 1;
				if(setsockopt(sock_id, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
				{
					printf("Error in sockopt");
					return -1;
				}
				
				s_socket.sin_family = AF_INET;
				s_socket.sin_port = htons(8080);
				s_socket.sin_addr.s_addr = INADDR_ANY;
	
				if(bind(sock_id, (struct sockaddr *)&s_socket, sizeof(s_socket))<0)
				{
					perror("bind failed");
					exit(EXIT_FAILURE);
			   	}
				if(listen(sock_id, 10) < 0)
				{
					perror("listen");
					exit(EXIT_FAILURE);
				}
				tid = 0;
				data_per_thread = ((double)rd/thread_count); 
				while((tid<thread_count) && (new_soc = accept(sock_id, (struct sockaddr *)&s_socket, (socklen_t*)&s_size)))
				{
					//printf("INside the while loop \n");
					rc = pthread_create(&threads[tid],NULL,addr,(void *)new_soc);
					if (rc){
						printf("Couldn't create thread : %ld \n" , tid);
					}
					tid++;	
				}
				for(tid=0; tid < thread_count; tid++){
					rc = pthread_join(threads[tid], NULL);
					if (rc){
						printf("Couldn't join thread number : %ld \n" , tid);
					}
				}
			}
			else if(strcmp(op[0],"U")==0){
		
				addr = &udp_receive;
				int port = 8080;
				data_per_thread = ((double)rd/thread_count); 
		
				for(tid=0; tid < thread_count; tid++)
				{
					rc = pthread_create(&threads[tid],NULL,addr,(void *)port);
					if (rc){
						printf("Couldn't create thread : %ld \n" , tid);
					}
					port++;
				}
				for(tid=0; tid < thread_count; tid++){
					rc = pthread_join(threads[tid], NULL);
					if (rc){
						printf("Couldn't join thread number : %ld \n" , tid);
					}
				}
			}
			else{
				printf("Enter a valid protocol type [T/U] for TCP or UDP respectively\n");
				return 0;
			}
		}else{
			printf("Please enter a valid type [C/S] for client or server respectively\n");
		}
	}else if(block_size == 0){
		if(strcmp(type[0], "C")==0){
	
			if(strcmp(op[0], "T")==0){
				addr = &tcp_sendL;
				double b_size = 1;
				
				data_per_thread = ((double)b_size/thread_count); 
	
				gettimeofday(&start_time,NULL);
		
				for(tid=0; tid < thread_count; tid++){
					rc = pthread_create(&threads[tid],NULL,addr,NULL);
					if (rc){
						printf("Couldn't create thread : %ld \n" , tid);
					}
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
				t_diff = t_stop - t_start;
				double t_milli = t_diff*1000;
				result = t_milli/(MEGA_BYTE);
				//printf("time taken for 1MB in Mili secs is %lf \n", t_milli);
				//printf("Resultant Latency is %lf \n",result);
				printf("-------------------------------------------------------------------------------------\n");
				printf("Protocol Concurrency BlockSize MyNETBenchValue TheoreticalValue MyNETBenchEfficiency\n");
				printf(" %s	     %ld	        %ldB	  %lf\n","TCP",thread_count,block_size+1,result);
				printf("-------------------------------------------------------------------------------------\n");
				
			}
			else if(strcmp(op[0],"U")==0){
				addr = &udp_sendL;
				double b_size = 1;
				int port = 8080;
				data_per_thread = ((double)b_size/thread_count); 
				//printf("value of data_per_thread is : %lf \n", data_per_thread);

				gettimeofday(&start_time,NULL);
		
				for(tid=0; tid < thread_count; tid++){
					rc = pthread_create(&threads[tid],NULL,addr,(void *) port);
					if (rc){
						printf("Couldn't create thread : %ld \n" , tid);
					}
					port++;
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
				t_diff = t_stop - t_start;
				double t_milli = t_diff*1000;
				result = t_milli/(MEGA_BYTE);
				//printf("time taken for 1MB in milli secs is %lf \n", t_milli);
				//printf("Resultant latency is %lf \n",result);
				
				printf("-------------------------------------------------------------------------------------\n");
				printf("Protocol Concurrency BlockSize MyNETBenchValue TheoreticalValue MyNETBenchEfficiency\n");
				printf(" %s	     %ld	        %ldB	  %lf\n","UDP",thread_count,block_size+1,result);
				printf("-------------------------------------------------------------------------------------\n");
			}
			else{
				printf("Enter a valid protocol type [T/U] for TCP or UDP respectively\n");
				return 0;
			}
		}	
		else if(strcmp(type[0], "S")==0){
			if(strcmp(op[0],"T")==0){
				
				struct sockaddr_in s_socket;
				int s_size = sizeof(s_socket);
				addr = &tcp_receiveL;
				if((sock_id = socket(AF_INET, SOCK_STREAM, 0)) == 0)
				{
					printf("Error in socket creation \n");
					return -1;
				}
	
				int opt = 1;
				if(setsockopt(sock_id, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
				{
					printf("Error in sockopt");
					return -1;
				}
	
				s_socket.sin_family = AF_INET;
				s_socket.sin_port = htons(8080);
				s_socket.sin_addr.s_addr = INADDR_ANY;
	
				if(bind(sock_id, (struct sockaddr *)&s_socket, sizeof(s_socket))<0)
			   	{
					perror("bind failed");
					exit(EXIT_FAILURE);
			   	}
				if (listen(sock_id, 8) < 0)
				{
					perror("listen");
					exit(EXIT_FAILURE);
				}
				tid = 0;
				double b_size = 1;
				data_per_thread = ((double)b_size/thread_count); 
				while((tid<thread_count) && (new_soc = accept(sock_id, (struct sockaddr *)&s_socket, (socklen_t*)&s_size)))
				{
					//printf("INside the while loop \n");
					rc = pthread_create(&threads[tid],NULL,addr,(void *)new_soc);
					if (rc){
						printf("Couldn't create thread : %ld \n" , tid);
					}
					tid++;	
				}
				for(tid=0; tid < thread_count; tid++){
					rc = pthread_join(threads[tid], NULL);
					if (rc){
						printf("Couldn't join thread number : %ld \n" , tid);
					}
				}	
			}
			else if(strcmp(op[0],"U")==0){
		
				addr = &udp_receiveL;
				int port = 8080;
				double b_size = 1;
				data_per_thread = ((double)b_size/thread_count); 
   
				for(tid=0; tid < thread_count; tid++)
				{
					//printf("INside the thread for loop \n");
					rc = pthread_create(&threads[tid],NULL,addr,(void *)port);
					if (rc){
						printf("Couldn't create thread : %ld \n" , tid);
					}	
					port++;
				}
				for(tid=0; tid < thread_count; tid++){
					rc = pthread_join(threads[tid], NULL);
					if (rc){
						printf("Couldn't join thread number : %ld \n" , tid);
					}
				}
			}
			else{
				printf("Enter a valid protocol type [T/U] for TCP or UDP respectively\n");
				return 0;
			}
		}
		else{
			printf("Please enter a valid type [C/S] for client or server respectively\n");
		}	
	}	
	else{
		printf("Enter valid block_size [0,1,32] ~ 0 for latency test(1Byte), 1KB or 32KB throughput respectively\n");
	}	
    return 0;
}
