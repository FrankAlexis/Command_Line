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
  /*Controlar la señal emitida por CRT+C por medio de un handler*/
  struct sigaction my_action;
  my_action.sa_handler = my_handler;
  my_action.sa_flags = SA_RESTART;
  sigaction(SIGINT, &my_action, NULL);
  /*Los comandos myexit y mycd son comandos internos por eso se ejecutan como funciones del CLI.
  Para los demás comandos se crea un proceso hijo y se llama al ejecutable correspondiente*/
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
          /*Significa que el comando no se debe ejecutar en segundo plano*/
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

/**
  Método que llama al ejecutable myclear. Si el usuario ingresa argumentos al comando
  se retorna un error.
**/

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

/**
  Método que llama al ejecutable myecho. Si el usuario ingresa más de 1 argumento al comando
  se retorna un error.
**/
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

/**
  Método que llama al ejecutable mytime. Si el usuario ingresa argumentos al comando
  se retorna un error.
**/
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

/**
  Método que llama al ejecutable mtcd. Si el usuario ingresa más de 1 argumento al comando
  se retorna un error. Del array items se extrae la ruta a la cual se desea cambiar.
**/
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


/**
  Método que llama al ejecutable mypwd. Si el usuario ingresa argumentos al comando
  se retorna un error.
**/
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

/**
  Método que llama al ejecutable mydir. Si el usuario ingresa más de 1 argumento al comando
  se retorna un error.Del array items se extrae el directorio que se quiere listar.
**/
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

/**
  Método que llama al ejecutable mycp. Si el usuario ingresa más o menos de 2 argumentos 
  al comando se retorna un error. Del array items se extrae la ruta del archivo que se quiere
  copiar y la nueva ruta donde se quiere poner la copia.
**/
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
 * Método que llama al ejecutable mykill.Enviar una determinada señal a un proceso
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

/**
  Método que llama al ejecutable mypause. Si el usuario ingresa argumentos al comando
  se retorna un error.
**/
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
