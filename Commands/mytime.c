#include <sys/times.h>
#include <sys/types.h>
#include <syscall.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

void start_clock(void);
void end_clock();

static clock_t st_time;
static clock_t en_time;
static struct tms st_cpu;
static struct tms en_cpu;


int main(int argc, char *argv[]){
    if( argc < 2){
        perror("Incomplete argument params"); 
        exit(EXIT_FAILURE);
    }
    printf("arg[1]:%s",argv[1]);
    start_clock();
    system("cal");
    end_clock();
    exit(EXIT_SUCCESS);
    return 0;
}

/**
 * Comienza el cronometro haciendo uso del llamado al sistema times()
 * */
void start_clock(){
    st_time = times(&st_cpu);
}

/**
 * Muestra los tiempos requeridos al ejecutar el correspondiente proceso.
 * Los resultados debe estar en un rango de tipo integer.
 * 
 * */
void end_clock(){
    en_time = times(&en_cpu);
    fputs("",stdout);
    printf("\nReal           %jd\nUser Time      %jd\nSystem Time    %jd\n",
        (intmax_t)(en_time - st_time),
        (intmax_t)(en_cpu.tms_utime - st_cpu.tms_utime),
        (intmax_t)(en_cpu.tms_stime - st_cpu.tms_stime));
}
