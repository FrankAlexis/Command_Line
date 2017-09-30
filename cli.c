#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "parser.h"

#define TAM 100

void my_handler(int sig);
void getMycd(char*);
void getMypwd();
void getPrompt();
void getMydir(char *);
void getMyecho(char **, int);
void getMycp(char*, char*);
void getMytime();
void getMyclear();
void getMykill(char *);

int main (){
  char ** items;
  int num, background;
  char expresion[TAM];
  struct sigaction my_action;
  my_action.sa_handler = my_handler;
  my_action.sa_flags = SA_RESTART;
  sigaction(SIGINT, &my_action, NULL);
  while(1){
    getPrompt();
    fgets (expresion, TAM, stdin);
    num = separaItems (expresion, &items, &background);
    printf ("Numero de parametros: %d\n", num);

    /*
    if (num>0){
      for (int i=0; i<num; i++){
        printf ("%d \"%s\"\n", i+1, items[i]);
        printf ("Background: %d\n", background);
      }
    }
    */

    if(strcmp(items[0],"mycd") == 0 ){
      getMycd(items[1]);
    }else if( strcmp(items[0],"mypwd") == 0){
      getMypwd();
    }else if(strcmp(items[0],"mydir") == 0){
      getMydir(items[1]);
    }else if(strcmp(items[0],"myexit") == 0){
      exit(EXIT_SUCCESS);
    }else if(strcmp(items[0],"mycp") == 0){
      getMycp(items[1], items[2]);
    }else if (strcmp(items[0],"mytime") == 0){
      getMytime();
    }else if (strcmp(items[0],"myecho") == 0){
      getMyecho(items,num);
    }else if(strcmp(items[0],"myclear") == 0){
      getMyclear();
    }else if(strcmp(items[0],"mykill") == 0){
      getMykill(items[1]);
    }else{
      perror("Command not found\n");
    }
  }
  liberaItems (items);
  return 0;
}
void my_handler(int sig) {
  printf("End the CLI with 'myexit' command ");
}

void getMyclear(){
  int status;
  pid_t pid_p = fork();
  switch(pid_p){
    case 0:
      execl("/home/estudiantes/frank.castrillon/Desktop/Command_Line/Commands/myclear",
            "/home/estudiantes/frank.castrillon/Desktop/Command_Line/Commands/myclear", NULL);
      break;
    default:
      wait(&status);
  }
}
void getMyecho(char **items, int num){
  int status;
  char message[100];
  pid_t pid_p = fork();
  switch(pid_p){
    case 0:
    if (num>0){
      for (int i=1; i<num; i++){
        strcat(message,items[i]);
        strcat(message," ");
      }
    }
      execl("/home/estudiantes/frank.castrillon/Desktop/Command_Line/Commands/myecho",
            "/home/estudiantes/frank.castrillon/Desktop/Command_Line/Commands/myecho", message,NULL);
      break;
    default:
      wait(&status);
  }
}

void getMytime(){
  int status;
  pid_t pid_p = fork();
  switch(pid_p){
    case 0:
      execl("/home/estudiantes/frank.castrillon/Desktop/Command_Line/Commands/mytime",
            "/home/estudiantes/frank.castrillon/Desktop/Command_Line/Commands/mytime", NULL);
      break;
    default:
      wait(&status);
  }
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
      execl("/home/estudiantes/frank.castrillon/Desktop/Command_Line/Commands/mypwd",
            "/home/estudiantes/frank.castrillon/Desktop/Command_Line/Commands/mypwd", NULL);
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
      execl("/home/estudiantes/frank.castrillon/Desktop/Command_Line/Commands/prompt",
            "/home/estudiantes/frank.castrillon/Desktop/Command_Line/Commands/prompt", NULL);
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
      execl("/home/estudiantes/frank.castrillon/Desktop/Command_Line/Commands/mydir",
            "/home/estudiantes/frank.castrillon/Desktop/Command_Line/Commands/mydir",path, NULL);
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
      execl("/home/estudiantes/frank.castrillon/Desktop/Command_Line/Commands/mycp",
            "/home/estudiantes/frank.castrillon/Desktop/Command_Line/Commands/mycp",sourcePath,targetPath, NULL);
      break;
    default:
      wait(&status);
  }
}

void getMykill(char *pid){
  int status;
  pid_t pid_p = fork();
  switch(pid_p){
    case 0:
      execl("/home/estudiantes/frank.castrillon/Desktop/Command_Line/Commands/mykill",
            "/home/estudiantes/frank.castrillon/Desktop/Command_Line/Commands/mykill",pid, NULL);
      break;
    default:
      wait(&status);
  }
}
