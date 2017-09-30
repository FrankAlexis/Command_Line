#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
  if( argc !=2){
      perror("Arguments error");
      exit(EXIT_FAILURE);
  }
  printf("%s\n",argv[1]);
  return 0;
}
