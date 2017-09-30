#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]){
    char buff[20];
    //Llamado al sistma time que obtiene la fecha actual del sistema
    time_t now = time(NULL);
    /**
     * Da formato al tiempo
     * localtime es la estructura
     * **/
    strftime(buff, 20, "%Y-%m-%d %H:%M:%S", localtime(&now));
    printf("Time: %s\n",buff);
    exit(EXIT_SUCCESS);
    return 0;
}
