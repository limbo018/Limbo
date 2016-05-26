/* 
 * WHAT THIS EXAMPLE DOES
 * 
 * We create a pool of 4 threads and then add 40 tasks to the pool(20 task1 
 * functions and 20 task2 functions). task1 and task2 simply print which thread is running them.
 * 
 * As soon as we add the tasks to the pool, the threads will run them. It can happen that 
 * you see a single thread running all the tasks (highly unlikely). It is up the OS to
 * decide which thread will run what. So it is not an error of the thread pool but rather
 * a decision of the OS.
 * 
 * */

#include <stdio.h>
#include <pthread.h>
#include "thpool.h"

/*check if the compiler is of C++*/
#ifdef __cplusplus 
extern "C" {
#endif


void* task1(void* args){
    int i;
    for (i = 0; i < 10000000; ++i);
	printf("Thread #%lu working on task1\n", (unsigned long)pthread_self());
    return NULL;
}


void* task2(void* args){
    int i;
    for (i = 0; i < 1000000; ++i);
	printf("Thread #%lu working on task2\n", (unsigned long)pthread_self());
    return NULL;
}

void* task3(void* args){
    int i;
    for (i = 0; i < 100000; ++i);
	printf("Thread #%lu working on task3\n", (unsigned long)pthread_self());
    return NULL;
}


void* task4(void* args){
    int i;
    for (i = 0; i < 100; ++i);
	printf("Thread #%lu working on task4\n", (unsigned long)pthread_self());
    return NULL;
}


int main(){
	
	puts("Making threadpool with 4 threads");
	threadpool thpool = thpool_init(4);

	puts("Adding 40 tasks to threadpool");
	int i;
	for (i=0; i<10; i++){
		thpool_add_work(thpool, task1, NULL);
		thpool_add_work(thpool, task2, NULL);
        /*thpool_wait(thpool); */
		thpool_add_work(thpool, task3, NULL);
		thpool_add_work(thpool, task4, NULL);
        thpool_wait(thpool); 
	};

	puts("Killing threadpool");
	thpool_destroy(thpool);
	
	return 0;
}

/*check if the compiler is of C++*/
#ifdef __cplusplus 
}
#endif

