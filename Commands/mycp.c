#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>/*Libreria para utilizar las constantes que definen los
                        privilegios que se tienen sobre un directorio*/
#include <sys/syscall.h>
#include <sys/types.h>


#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif

int main(int argc, char *argv[])
{
    int inputFd;
    int outputFd;
    int openFlags;
    mode_t filePermissions;
    ssize_t numRead;
    ssize_t numWrite;
    char buf[BUF_SIZE];

    if( argc != 3){
        perror("Arguments error");
        exit(EXIT_FAILURE);
    }

    /* Se abre el archivo de entrada*/
    inputFd = open(argv[1], O_RDONLY);
    if (inputFd == -1){
      perror("opening input file");
      exit(EXIT_FAILURE);
    }
    /*Definición de banderas para abrir el archivo
    O_CREAT = Crear la fila si no existe
    O_WRONLY = Abrir para escritura solamente
    O_TRUNC= Truncar el archivo. Limpiar el archivo*/
    openFlags = O_CREAT | O_WRONLY | O_TRUNC;

    /* Definición de permisos para el archivo
    S_IRUSR = Permiso de lectura al propietario
    S_IWUSR = Permiso de escritura al propietario
    S_IRGRP = Permiso de lectura para grupo
    S_IWGRP = Permiso de escritura para grupo
    S_IROTH = Permiso de lectura para otros
    S_IWOTH = Permiso de escritura para otros
    */

    filePermissions = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH; /*rw-rw-rw*/


    /**Se abra el archivo de salida con los permisos correspondientes*/
    outputFd = open(argv[2], openFlags, filePermissions);

    if (outputFd == -1){
      perror("opening output file");
      exit(EXIT_FAILURE);
    }


    /* Se lee la información del archivo de entrada y se copia en el archivo de
    salida. Si el número de bytes leidos difiere del número de bytes escritos,
    se reporta un error de escritura.*/

    while ((numRead = read(inputFd, buf, BUF_SIZE)) > 0)
    {
        numWrite = write(outputFd, buf, numRead);
        if (numWrite != numRead){
          perror("Could not write the buffer");
          exit(EXIT_FAILURE);
        }
    }

    /*Error de lectura*/
    if (numRead == -1){
      perror("read");
      exit(EXIT_FAILURE);
    }

    if (close(inputFd) == -1){
      perror("Close input");
      exit(EXIT_FAILURE);
    }

    if (close(outputFd) == -1){
      perror("Close output");
      exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
