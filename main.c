#include "defs.h"

int main(int argc, char *argv[])
{
  if(argc==1){
    runEscape();
  }
  
  if(argc==2){
    viewEscape(argv[1]);
  }

  return(0);
}

/*
  Function:  randomInt
  Purpose:   computes a random number in the range of [0, max)
       in:   a max value
       return:  a random number in the range of [0,max)
*/
int randomInt(int max)
{
  return(rand() % max);
}
