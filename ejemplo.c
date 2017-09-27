#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#define TAM 100

void getMycd(char*);
void getMypwd();
void getPrompt();
void getMydir(char *);
void getMycp(char*, char*);

int main (){
  char ** items;
  int num, background;
  char expresion[TAM];
  while(1){
    getPrompt();
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
    }else if(strcmp(items[0],"mydir") == 0){
      getMydir(items[1]);
    }else if(strcmp(items[0],"exit") == 0){
      exit(EXIT_SUCCESS);
    }else if(strcmp(items[0],"mycp") == 0){
      getMycp(items[1], items[2]);
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
      execl("/home/frank/Desktop/operative system/Lab_3.1/Command Line/Commands/mypwd",
            "/home/frank/Desktop/operative system/Lab_3.1/Command Line/Commands/mypwd", NULL);
      break;
    default:
      wait(&status);
  }
}

void getPrompt(){
  int status;
  pid_t pid_p = fork();
  switch(pid_p){
    case 0:
      execl("/home/frank/Desktop/operative system/Lab_3.1/Command Line/Commands/prompt",
            "/home/frank/Desktop/operative system/Lab_3.1/Command Line/Commands/prompt", NULL);
      break;
    default:
      wait(&status);
  }
}

void getMydir(char* path){
  int status;
  pid_t pid_p = fork();
  switch(pid_p){
    case 0:
      execl("/home/frank/Desktop/operative system/Lab_3.1/Command Line/Commands/mydir",
            "/home/frank/Desktop/operative system/Lab_3.1/Command Line/Commands/mydir",path, NULL);
      break;
    default:
      wait(&status);
  }
}

void getMycp(char* sourcePath, char* targetPath){
  int status;
  pid_t pid_p = fork();
  switch(pid_p){
    case 0:
      execl("/home/frank/Desktop/operative system/Lab_3.1/Command Line/Commands/mycp",
            "/home/frank/Desktop/operative system/Lab_3.1/Command Line/Commands/mycp",sourcePath,targetPath, NULL);
      break;
    default:
      wait(&status);
  }
}
