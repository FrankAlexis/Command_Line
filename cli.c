#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "parser.h"

#define TAM 100
static const char mypath[] =  "/home/frank/Desktop/operative system/Lab_3.1/Command_Line/Commands/";

void my_handler(int sig);
void getMycd(char*);
void getMypwd();
void getPrompt();
void getMydir(char *);
void getMyecho(char **, int);
void getMycp(char*, char*);
void getMytime();
void getMyclear();
void getMykill(char *, char*);

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
      getMycd(items[1]);
    }else if(strcmp(items[0],"myexit") == 0){
      exit(EXIT_SUCCESS);
    }else{
      int status;
      pid_t pid_p = fork();
      switch(pid_p){
        case 0:
          if( strcmp(items[0],"mypwd") == 0){
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
            getMykill(items[1], items[2]);
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

/**
 * Limpia la pantalla de la terminar
 * */
void getMyclear(){
  char message[100];
  strcat(message,mypath);
  strcat(message,"myclear");
  execl(message,message, NULL);
}
void getMyecho(char **items, int num){
  char message[100];
  char msn[100];
  if (num>0){
    for (int i=1; i<num; i++){
      strcat(message,items[i]);
      strcat(message," ");
    }
  }
  strcat(msn,mypath);
  strcat(msn,"myecho");
  execl(msn,msn, message,NULL);
}

/**
 * Obtiene la hora actual del sistema 
 * */
void getMytime(){
  char message[100];
  strcat(message,mypath);
  strcat(message,"mytime");
  execl(message,message, NULL);
}

/**
 * Cambia de directorio de trabajo
 * @param path dirección del directorio
 * */
void getMycd(char* path){
  //Llamado al sistema chdir
  int value = chdir(path);
  //En caso de error envia el mensaje correspondiente
  if(value == -1){
    perror("chdir()");
  }
}
/**
 * Obtiene la dirección del actual directorio
 * */
void getMypwd(){
  char message[100];
  strcat(message,mypath);
  strcat(message,"mypwd");
  execl(message,message, NULL);
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
 * Imprime los archivos de un directorio de trabajo
 * @param path dirección del directorio
 * */
void getMydir(char* path){
  char message[100];
  strcat(message,mypath);
  strcat(message,"mydir");
  execl(message,message,path, NULL);
}

void getMycp(char* sourcePath, char* targetPath){
  char message[100];
  strcat(message,mypath);
  strcat(message,"mycp");
  execl(message, message,sourcePath,targetPath, NULL);

}

/**
 * Enviar una determinada señan a un proceso
 * @param pid identificador del proceso
 * @param sig tipo de señal
 * */
void getMykill(char *pid, char* sig){
  char message[100];
  strcat(message,mypath);
  strcat(message,"mykill");
  execl(message,message,sig,pid, NULL);
}
