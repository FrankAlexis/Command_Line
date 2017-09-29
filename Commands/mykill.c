#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    if( argc != 2){
        perror("Arguments error");
        exit(EXIT_FAILURE);
    }
    pid_t pid = atoi(argv[1]);
    //SIGKILL=9
    int value = kill(pid, SIGKILL);
    if(value == 0){
        printf("Signal sended");
    }else{
        perror("Error sending signal");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}