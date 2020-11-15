#include "types.h"
#include "stat.h"
#include "user.h"
int main(int argc, char *argv[])
{
	printf(1,"Ticket Count: %d\n",ticket(20)); 
	int i,k;
	const int loop=43000;
	for(i=0;i<loop;i++)
	{
		asm("nop");
		for(k=0;k<loop;k++)
		{
			asm("nop");
		}
	}
	printf(1,"2:  %d out of %d \n",ticksProc(0), ticksProc(1));
	exit();
}
