#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "semmac.h"
#include <stdlib.h>
#include <stdio.h>

// Inicializa el semaforo esta forma(Semaforos nombrados) sirve para mac y linux
// En linux se puede usar semaforos anonimos con sem_init
void init(sem_t **sem, char* pathname, int valor_inicial) {
   if ((*sem = sem_open(pathname, O_CREAT, 0664, valor_inicial)) == SEM_FAILED) {
      printf("Error inicializando semaforo\n");
      exit(EXIT_FAILURE);
   }
}

//función encargada de bloquear un semáforo
//si ya estaba bloqueado, se queda a la espera de ser liberado para bloquearlo
void p(sem_t *sem) {
   if (sem_wait(sem)) {
      printf("Error fatal haciendo sem_wait()\n");
      exit(EXIT_FAILURE);
   }
}

//función encargada de liberar un semáforo
//en caso que el semáforo ya esté liberado,
void v(sem_t *sem) {
   if (sem_post(sem)) {
      printf("Error fatal haciendo sem_post()\n");
      exit(EXIT_FAILURE);
   }
}

void l(char *name){
   if (sem_unlink(name) == -1){
      printf("Error fatal haciendo sem_unlink()\n");
      exit(EXIT_FAILURE);
   }
}

void imprimirValSem(sem_t *sem, char *name){
  int d = 0;
  sem_getvalue(sem, &d);
  printf("El valor del semaforo %s es %d\n", name, d);
}
