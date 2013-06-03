/*
* a1.c
* CS570 5/30/2013 Summer
* by Masc0965(Douglas Bielinski)
* and Masc0964(Kirankumar Dhakshana)
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <semaphore.h>

FILE *fp;
sem_t mutx;

static void * start_routine(void *arg){
	sem_wait(&mutx);
	fprintf(fp, "Thread %d is running\n", pthread_self());
	sem_post(&mutx);
}

int main(void){
	int loopCounter, check = 0;
	pthread_attr_t attr;
	pthread_t thread_id[15];

	check = sem_init(&mutx, 0, 10);
	if(check!=0)
		fprintf(fp, "sem init broke!\n");

	check = pthread_attr_init(&attr);
	if(check!=0)
		fprintf(stderr, "pthread attr init broke!\n");
	fp = fopen("PROCTAB.txt", "w");

	fprintf(fp, "Printing Thread IDs\n");

	if(fp == NULL){
		fprintf(stderr, "Can't open. Bail out!\n");
		exit(1);
	}
	else
	{
		while(loopCounter < 10){
			check = pthread_create(&thread_id[loopCounter], NULL, &start_routine, NULL);
			if(check != 0)
				fprintf(stderr, "This thread broke!\n");
			loopCounter++;
		}
	}
	sem_destroy(&mutx);

	return 0;
}
