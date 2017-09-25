#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> 
#include <errno.h>
int main(int argc, char *argv[]){
    printf("Entre mypwd");
    char *p = getenv("USER");
    if(p == NULL){ 
        return EXIT_FAILURE;
    }
    printf("%s@:",p);
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL){
        printf("%s:", cwd);
    }else{
        perror("getcwd() error");
    }
    return 0;
    
}