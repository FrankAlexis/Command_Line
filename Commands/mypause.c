#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main(){
  //Interrumpe la terminar hasta que una señal es capturada
  pause();
  exit(EXIT_SUCCESS);
}