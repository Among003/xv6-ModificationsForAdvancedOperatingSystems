#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"


int main(int argc, char *argv[])
{
  if(argc !=2){
  printf(1, "ERROR: enter 1 option.  (1) for proccess count, (2) for total number of syscalls, (3) for total number of mem pages used by current process"); 
  exit();
  }

  int x = atoi(argv[1]);
  printf(1,"%d\n",x);

  printf(1 , "%d" , info(x));
  exit();
}


