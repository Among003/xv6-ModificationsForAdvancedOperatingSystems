#include "types.h"
#include "stat.h"
#include "user.h"
#include "x86.h"
#define PGSIZE 4096

lock_t TOKEN = 0;
lock_t PASSCHECK = 0;


uint PASSNUMBER = 0;
uint PASSES = 0;

int thread_create(void (*start_routine)(void*, void*), void *arg, void* arg2);
int lock_acquire(lock_t *);
int lock_release(lock_t *);
void frisbee(void* arg, void* arg2);


int main(int argc, char *argv[])
{
	if (argc < 3){
		printf(0,"Input number of threads and number of passes\n");
		
	}
	uint numberOfThreads = atoi(argv[1]);
	PASSES = atoi(argv[2]);
	uint threadIDs[numberOfThreads];
	
	for (unsigned int i= 0; i < numberOfThreads; i++){
		threadIDs[i] = i;
	}
	
	for (unsigned int i = 0; i < numberOfThreads; i++){
		thread_create(&frisbee, &threadIDs[i], &numberOfThreads);
	}
	printf(0, "Exiting\n");
	//wait();
	for (unsigned int i = 0; i < 4000000000000; i++){;}
	exit();
}


//arg 1 is thread id, arg 2 is numberOfThreads
void frisbee(void* arg, void* arg2){
	
	//printf(2, "Values being passed in: %d and %d\n", *(int*) arg, *(int*) arg2);
	
	
	lock_acquire(&PASSCHECK);
	
	while(PASSNUMBER < PASSES){
		
		if(PASSNUMBER % (*(int *) arg2) == (*(int*) arg)){
			PASSNUMBER += 1;
			lock_acquire(&TOKEN);
			printf(1,"Pass number no: %d, Thread %d is passing the token to %d\n", PASSNUMBER, *(int*) arg, (PASSNUMBER) % (*(int *) arg2));
			lock_release(&TOKEN);
		}
		lock_release(&PASSCHECK);
		sleep(20);
		lock_acquire(&PASSCHECK);
	}
		
	
	
	//lock_acquire(&TOKEN);
	//printf(1, "TOKEN acquired by thread %d \n", *(int*) arg); 
	//lock_release(&TOKEN);
	
	/*
	if(passNumber <= *(int*)arg2){
		printf(1,"%d \n", *(int*)arg);
		passNumber += 1;
	}*/
	
	
	for (unsigned int i = 0; i < 400000; i++){;}
	exit();
}

int thread_create(void (*start_routine)(void*, void*), void *arg, void *arg2){
	lock_t LK = 0;
	lock_acquire(&LK);
	void *stack = malloc(PGSIZE*2);
	lock_release(&LK);
	
	if((uint)stack % PGSIZE)
		stack = stack + (PGSIZE - (uint)stack % PGSIZE);

	//printf(0, "STACK ALLOCATED\n");
    clone(stack, start_routine, arg, arg2);
	return 0;
}

int lock_acquire(lock_t * lkAquiring){ 
	while(xchg(lkAquiring,1) != 0){
		;
	}
	return 0;
}

int lock_release(lock_t * lkReleasing){ 
	xchg(lkReleasing, 0);
	return 0;
}

