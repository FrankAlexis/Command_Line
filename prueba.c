#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
void my_handler(int sig);
int main(){
    printf("hello");
    struct sigaction my_action;
    my_action.sa_handler = SIG_IGN;
    my_action.sa_flags = SA_RESTART;
    sigaction(SIGINT, & my_action, NULL);
    while(1){
        
    }
    return 0;
}
void my_handler(int sig) {
    printf("End the CLI with 'myexit' command ");
}