#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
  if( argc !=2){
      perror("Arguments error");
      exit(EXIT_FAILURE);
  }
  //Imprimir el mensaje que viene por parámetro
  printf("%s\n",argv[1]);
  return 0;
}
