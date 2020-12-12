#include "types.h"
#include "stat.h"
#include "user.h"
#include "x86.h"
#define PGSIZE 4096



int thread_create(void (*start_routine)(void*), void *arg);
int lock_acquire(lock_t *);
int lock_release(lock_t *);
void frisbee(void* arg);


int main(int argc, char *argv[])
{
	
	int x = 5;
	thread_create(&frisbee, &x);
	printf(0, "Exiting\n");
	exit();
}



void frisbee(void* arg){
	printf(0,"test print\n");
	return;
}

int thread_create(void (*start_routine)(void*), void *arg){
	lock_t LK = 0;
	lock_acquire(&LK);
	void *stack = malloc(PGSIZE*2);
	lock_release(&LK);
	printf(0, "STACK ALLOCATED\n");
    clone(stack, PGSIZE*2);
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

