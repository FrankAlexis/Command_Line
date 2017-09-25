#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"

#define TAM 100

void getMycd(char*);
void getMypwd();

int main (){

  char ** items;
  int num, background;
  char expresion[TAM];

  while(1){
    fgets (expresion, TAM, stdin);
    num = separaItems (expresion, &items, &background);
    printf ("Numero de parametros: %d\n", num);
    if (num>0){
      for (int i=0; i<num; i++){
        printf ("%d \"%s\"\n", i+1, items[i]);
        printf ("Background: %d\n", background);
      }
    }
    if(strcmp(items[0],"mycd") == 0 ){
      getMycd(items[1]);
    }else if( strcmp(items[0],"mypwd") == 0){
      getMypwd(); 
    }
  }
  liberaItems (items);
  return 0;
}

void getMycd(char* path){
  int value = chdir(path);
  if(value == -1){
    perror("chdir()");
  }
}
void getMypwd(){
  int status;
  pid_t pid_p = fork();
  switch(pid_p){
    case 0:
      execl("/home/frank/Desktop/operative system/Lab_3.1/T/Commands/mypwd",
            "/home/frank/Desktop/operative system/Lab_3.1/T/Commands/mypwd", NULL);
      break;
    default:
      wait(&status);
  }
}
