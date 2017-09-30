#define _GNU_SOURCE
#include <dirent.h>     /*Define las constantes DT_*/
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/syscall.h>

struct directory{
    long           d_ino;
    off_t          d_off;
    unsigned short d_reclen;
    char           d_name[];
};

#define BUF_SIZE 1024

char* getDirectoryType(char);

int main(int argc, char *argv[]){
    int fd, nread;
    char buf[BUF_SIZE];
    struct directory*d;
    int bpos;
    char d_type;
    for(int i=0; i< argc; i++){
        printf("%d:%s\n",i,argv[i]);
    }
    if( argc != 2){
        perror("Arguments error");
        exit(EXIT_FAILURE);
    }
    fd = open(argv[1] , O_RDONLY | O_DIRECTORY );
    if (fd == -1){
        /*Imprime un mensaje estandar de error describiendo el ultimo error
          encontrado durante  una llamada al sistema o una función de liberia.
        */
        perror("open");
        exit(EXIT_FAILURE);
    }
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
