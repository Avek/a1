/*
* a1.c
* CS570 5/30/2013 Summer
* by masc0965(Douglas Bielinski)
* and masc0964(Kirankumar Dhakshana)
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <semaphore.h>

sem_t LOCK;//semaphore

//start routine is passed to each thread, each thread will (once every second)
//check the LOCK semaphore if they can access the critical region
//if they can they open PROCTAB.txt with a so they can append to the file
//they print to stdout that they are running
//they append their ID to the file PROCTAB.txt
//they close the file and release LOCK, if it is their 10th print they exit.
static void * start_routine(void *arg){
	FILE *fp;
	
	for(int i = 0; i<10; i++){
		sleep(1);//once every second
		sem_wait(&LOCK);
		fp = fopen("PROCTAB.txt", "a");
		if(fp==NULL)
			fprintf(stderr, "Failed opening file!");
		printf("Thread %d is running\n", pthread_self());
		fprintf(fp, "%d\r\n", pthread_self());
		fclose(fp);
		sem_post(&LOCK);
	}
	pthread_exit(NULL);
}

int main(void){
	FILE *fp;
	int threadCounter, check = 0;
	pthread_t thread_id[10];

	check = sem_init(&LOCK, 0, 1);//initialize the semaphore with val 1
	if(check!=0)
		fprintf(fp, "sem init broke!\n");

	//Create a file, PROCTAB.txt
	fp = fopen("PROCTAB.txt", "w");//open or create PROCTAB.txt
				//we use "w" here because if it exists
				//we'd like to write over it.
	if(fp == NULL){
		fprintf(stderr, "Can't open. Bail out!\n");
		exit(1);
	}
	//Write it's pid(followed by a Carriage Return and a Newline)
	fprintf(fp, "%d\r\n", getpid());
	check = fclose(fp);
	
	if(check != 0)
		fprintf(stderr, "Error closing file\n");

	//this loop creates 10 threads, with ID's 2 through 11
	//the main process is ID 1. pthread_create passes the threads their
	//start routines.
	while(threadCounter < 10){
		check = pthread_create(&thread_id[threadCounter], NULL, &start_routine, NULL);
		if(check != 0)
			fprintf(stderr, "This thread broke!\n");
		threadCounter++;
	}//end while

	//we are done with LOCK, destroy the semaphore
	check = sem_destroy(&LOCK);
	if(check != 0)
		fprintf(stderr, "sem destroy failed!");

	free(thread_id); //release the memory allocated for thread_id
	pthread_exit(NULL);//when all the threads are done
			//this will be like exit(0)
}
