#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>

FILE *fp;

static void * start_routine(void *arg){
	fprintf(fp, "%d", getpid());
}

int main(void){
	int mypid, loopCounter = 0;
	pthread_attr_t attr;

	pthread_attr_init(&attr);
	fp = fopen("PROCTAB.txt", "w");
	
	if(fp == NULL){
		fprintf(stderr, "Can't open. Bail out!\n");
		exit(1);
	}
	else
	{
		while(loopCounter < 2){
			pthread_create(loopCounter, &attr, &start_routine, loopCounter);

			loopCounter++;
		}

		fprintf(fp, "Success!\n");
	}
	return 0;
}
