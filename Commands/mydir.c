#define _GNU_SOURCE
#include <dirent.h>     /*Define las constantes DT_*/
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/syscall.h>

/**
 * Estructura que almacena la configuración de un directorio o archivo
 * **/
struct directory{
    long           d_ino;
    off_t          d_off;
    unsigned short d_reclen;/*Tamaño del directorio*/
    char           d_name[];
};

/**
 * Tamaño del buffer
 * */
#define BUF_SIZE 1024

char* getDirectoryType(char);

int main(int argc, char *argv[]){
    int fd, nread;
    char buf[BUF_SIZE];
    struct directory*d;
    int bpos;
    char d_type;
    /*for(int i=0; i< argc; i++){
        printf("%d:%s\n",i,argv[i]);
    }*/
    if( argc != 2){
        perror("Arguments error");
        exit(EXIT_FAILURE);
    }
    //Abre el diectorio enviado como argv[1] dependiendo del tipo
    //O_RDONLY abre el directorio en solo lectura
    //O_DIRECTORY abre el archivo si es un directorio
    fd = open(argv[1] , O_RDONLY | O_DIRECTORY );
    if (fd == -1){
        /*Imprime un mensaje estandar de error describiendo el ultimo error
          encontrado durante  una llamada al sistema o una función de liberia.
        */
        perror("open");
        exit(EXIT_FAILURE);
    }
    /* El ciclo no tiene condición, ya que se lee el directorio por bloques de 1024, por eso cuando 
        nread=0 significa que no hay nada más por leer*/
    for ( ; ; ) {
        nread = syscall(SYS_getdents, fd, buf, BUF_SIZE);
        if (nread == -1){
            perror("getdent");
            exit(EXIT_FAILURE);
        }
        if (nread == 0){
            break;
        }
        printf("file_type  name\n");
        /*Se mueve por cada una de las estructuras directory para imprimir el nombre y el tipo de directorio. */
        for (bpos = 0; bpos < nread;) {
            d = (struct directory*) (buf + bpos);
            d_type = *(buf + bpos + d->d_reclen - 1);
            printf("|%-10s| ",getDirectoryType(d_type));
            printf("%s\n", d->d_name);
            bpos += d->d_reclen;
        }
    }
    return 0;
}
/**
 * Imprime el tipo de directorio
 * @param d_type tipo de directorio
 * */
char* getDirectoryType(char d_type){
    switch(d_type){
        case DT_REG:
            return "regular";
        case DT_DIR:
            return "directory";
        case DT_FIFO:
            return "FIFO";
        case DT_SOCK:
            return "socket";
        case DT_LNK:
            return "sysmlink";
        case DT_BLK:
            return "block dev";
        case DT_CHR:
            return "char dev";
    }
}
