#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "parser.h"

#define TAM 100
static const char mypath[] =  "/home/estudiantes/frank.castrillon/Desktop/Command_Line/Commands/";

void my_handler(int sig);
void getMycd(char **, int);
void getMypwd(char **, int);
void getPrompt();
void getMydir(char **, int);
void getMyecho(char **, int);
void getMycp(char **, int);
void getMytime(char **, int);
void getMyclear(char **, int);
void getMykill(char **, int);
void getMypause(char **, int);

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
    if(strcmp(items[0],"mycd") == 0 ){
      getMycd(items,num);
    }else if(strcmp(items[0],"myexit") == 0){
      exit(EXIT_SUCCESS);
    }else{
      int status;
      pid_t pid_p = fork();
      switch(pid_p){
        case 0:
          if( strcmp(items[0],"mypwd") == 0){
            getMypwd(items,num);
          }else if(strcmp(items[0],"mydir") == 0){
            getMydir(items,num);
          }else if(strcmp(items[0],"mycp") == 0){
            getMycp(items,num);
          }else if (strcmp(items[0],"mytime") == 0){
            getMytime(items,num);
          }else if (strcmp(items[0],"myecho") == 0){
            getMyecho(items,num);
          }else if(strcmp(items[0],"myclear") == 0){
            getMyclear(items,num);
          }else if(strcmp(items[0],"mykill") == 0){
            getMykill(items,num);
          }else if(strcmp(items[0],"mypause") == 0){
            getMypause(items,num);
          }else{
            perror("Command not found\n");
          }
          break;
        default:
          if(background==0){
            wait(&status);
            printf("salí del estatus" );
          }
          break;
      }
    }
  }
  liberaItems (items);
  return 0;
}
void my_handler(int sig) {
  printf("End the CLI with 'myexit' command sig:%d",sig);
  sleep(3);
}

void getMyclear(char **items, int num){
  char message[100];
  if(num!=1){
    perror("The command no needs arguments");
    exit(EXIT_FAILURE);
  }
  strcat(message,mypath);
  strcat(message,"myclear");
  execl(message,message, NULL);
}
void getMyecho(char **items, int num){
  char message[100];
  if(num<2){
    perror("The command needs 1 argument. myecho <message>");
    exit(EXIT_FAILURE);
  }
    for (int i=1; i<num; i++){
      strcat(message,items[i]);
      strcat(message," ");
  }
  execl("/home/estudiantes/frank.castrillon/Desktop/Command_Line/Commands/myecho",
          "/home/estudiantes/frank.castrillon/Desktop/Command_Line/Commands/myecho", message,NULL);
}

void getMytime(char **items, int num){
  if(num!=1){
    perror("The command no needs arguments");
    exit(EXIT_FAILURE);
  }
  execl("/home/estudiantes/frank.castrillon/Desktop/Command_Line/Commands/mytime",
            "/home/estudiantes/frank.castrillon/Desktop/Command_Line/Commands/mytime", NULL);
}

void getMycd(char **items, int num){
  if(num!=2){
    perror("The command needs 1 argument. mycd <path>");
    exit(EXIT_FAILURE);
  }
  char* path = items[1];
  int value = chdir(path);
  if(value == -1){
    perror("chdir()");
  }
}

void getMypwd(char **items, int num){
  if(num!=1){
    perror("The command no needs arguments");
    exit(EXIT_FAILURE);
  }
  execl("/home/estudiantes/frank.castrillon/Desktop/Command_Line/Commands/mypwd",
        "/home/estudiantes/frank.castrillon/Desktop/Command_Line/Commands/mypwd", NULL);
}

void getPrompt(){
  printf("\n");
  char *p = getenv("USER");
  if(p == NULL){
      exit(EXIT_FAILURE);
  }
  printf("%s@:",p);
  char cwd[1024];
  if (getcwd(cwd, sizeof(cwd)) != NULL){
      printf("%s>", cwd);
  }else{
      perror("getcwd() error");
  }
}

void getMydir(char **items, int num){
  if(num!=2){
    perror("The command needs only 1 argument. mydir <path>");
    exit(EXIT_FAILURE);
  }
  char* path = items[1];
  execl("/home/estudiantes/frank.castrillon/Desktop/Command_Line/Commands/mydir",
            "/home/estudiantes/frank.castrillon/Desktop/Command_Line/Commands/mydir",path, NULL);
}

void getMycp(char **items, int num){
  if(num!=3){
    perror("The command needs only 2 arguments. mycp <source> <target>");
    exit(EXIT_FAILURE);
  }
  char* sourcePath = items[1];
  char* targetPath = items[2];
  printf("%s %s\n",sourcePath,targetPath );
  execl("/home/estudiantes/frank.castrillon/Desktop/Command_Line/Commands/mycp",
            "/home/estudiantes/frank.castrillon/Desktop/Command_Line/Commands/mycp",sourcePath,targetPath, NULL);

}

void getMykill(char **items, int num){
  if(num!=3){
    perror("The command needs only 2 arguments. mykill <signal> <pid>");
    exit(EXIT_FAILURE);
  }
  char* sig = items[1];
  char *pid = items[2];

  execl("/home/estudiantes/frank.castrillon/Desktop/Command_Line/Commands/mykill",
            "/home/estudiantes/frank.castrillon/Desktop/Command_Line/Commands/mykill",sig,pid, NULL);
}

void getMypause(char **items, int num){
  if(num!=1){
    perror("The command no needs arguments.");
    exit(EXIT_FAILURE);
  }
  execl("/home/estudiantes/frank.castrillon/Desktop/Command_Line/Commands/mypause",
            "/home/estudiantes/frank.castrillon/Desktop/Command_Line/Commands/mypause",NULL);
}
