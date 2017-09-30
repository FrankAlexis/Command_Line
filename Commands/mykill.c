#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    if( argc != 3){
        perror("Arguments error");
        exit(EXIT_FAILURE);
    }
    int signal = atoi(argv[1]);
    pid_t pid = atoi(argv[2]);
    //Envia una señal al proceso pid
    int value = kill(pid, signal);
    if(value == 0){
        printf("Signal sended");
    }else{
        perror("Error sending signal");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}