#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "parser.h"

#define TAM 100
static const char mypath[] =  "/home/frank/Desktop/operative system/Lab_3.1/Command_Line/Commands/";

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
  struct sigaction my_action_ignore;
  struct sigaction my_action_kill;
  my_action_ignore.sa_handler = SIG_IGN;
  my_action_ignore.sa_flags = SA_RESTART;
  sigaction(SIGINT, &my_action_ignore, NULL);
  my_action_kill.sa_handler = my_handler;
  my_action_kill.sa_flags = SA_RESTART;
  sigaction(SIGTERM, &my_action_kill, NULL);
  while(1){
    getPrompt();
    fgets (expresion, TAM, stdin);
    num = separaItems (expresion, &items, &background);
    //printf ("Numero de parametros: %d\n", num);
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
            //getMypause(items,num);
            pause();
          }else{
            perror("Command not found\n");
          }
          break;
        default:
          if(background==0){
            wait(&status);
          }
          break;
      }
    }
  }
  liberaItems (items);
  return 0;
}
/**
 * Método que captura la señal CTRL+c
 * @param sig número de la seña enviada
 **/
void my_handler(int sig) {
  printf("End the CLI with 'myexit' command sig:%d",sig);
  sleep(2);
}

void getMyclear(char **items, int num){
  char binPath[100];
  if(num!=1){
    perror("The command no needs arguments");
    exit(EXIT_FAILURE);
  }
  strcat(binPath,mypath);
  strcat(binPath,"myclear");
  execl(binPath,binPath, NULL);
}
void getMyecho(char **items, int num){
  char message[100];
  strcpy(message,"");
  if(num<2){
    perror("The command needs 1 argument. myecho <message>");
    exit(EXIT_FAILURE);
  }
  for (int i=1; i<num; i++){
      strcat(message,items[i]);
      strcat(message," ");
  }
  char binPath[100];
  strcat(binPath,mypath);
  strcat(binPath,"myecho");
  execl(binPath,binPath,message,NULL);

}

void getMytime(char **items, int num){
  if(num!=1){
    perror("The command no needs arguments");
    exit(EXIT_FAILURE);
  }
  char binPath[100];
  strcat(binPath,mypath);
  strcat(binPath,"mytime");
  execl(binPath,binPath,NULL);
}

void getMycd(char **items, int num){
  if(num!=2){
    perror("The command needs 1 argument. mycd <path>");
    exit(EXIT_FAILURE);
  }
  char* path = items[1];
  int value = chdir(path);
  //En caso de error envia el mensaje correspondiente
  if(value == -1){
    perror("chdir()");
  }
}

void getMypwd(char **items, int num){
  if(num!=1){
    perror("The command no needs arguments");
    exit(EXIT_FAILURE);
  }
  char binPath[100];
  strcat(binPath,mypath);
  strcat(binPath,"mypwd");
  execl(binPath,binPath, NULL);
}

/**
 * Imprime el usuario y el directorio de trabajo actual
 * */
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
  char binPath[100];
  strcat(binPath,mypath);
  strcat(binPath,"mydir");
  execl(binPath,binPath,path, NULL);
}

void getMycp(char **items, int num){
  if(num!=3){
    perror("The command needs only 2 arguments. mycp <source> <target>");
    exit(EXIT_FAILURE);
  }
  char* sourcePath = items[1];
  char* targetPath = items[2];
  char binPath[100];
  strcat(binPath,mypath);
  strcat(binPath,"mycp");
  execl(binPath, binPath,sourcePath,targetPath, NULL);

}

/**
 * Enviar una determinada señan a un proceso
 * @param pid identificador del proceso
 * @param sig tipo de señal
 * */
void getMykill(char **items, int num){
  if(num!=3){
    perror("The command needs only 2 arguments. mykill <signal> <pid>");
    exit(EXIT_FAILURE);
  }
  char* sig = items[1];
  char *pid = items[2];
  char binPath[100];
  strcat(binPath,mypath);
  strcat(binPath,"mykill");
  execl(binPath,binPath,sig,pid, NULL);
}


void getMypause(char **items, int num){
  if(num!=1){
    perror("The command no needs arguments.");
    exit(EXIT_FAILURE);
  }
  char binPath[100];
  strcat(binPath,mypath);
  strcat(binPath,"mypause");
  execl(binPath,binPath,NULL);
}
