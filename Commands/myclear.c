#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
int main(int argc, char *argv[]){
    const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
    write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
    return 0;
}
