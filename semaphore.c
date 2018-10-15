#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdio.h>

/*  Crea el semaforo

    seed: El valor para la semilla del semaforo.

    Devuelve el valor el indentificador del semaforo.
*/
int semGet(int seed){
  key_t key = ftok("./",seed); //Crea la key para el semaforo.
  int semID;
  if ((semID = semget(key, 1, IPC_CREAT | 0664))== -1) {
    printf("Error, no se pudo crear el semaforo\n");
  }
  return semID;
}


 /* Cambia el valor del semaforo

    semID: El id del semaforo.
    semID: El nuevo valor.
 */
 void semSet(int semID, int val){
   if (semctl(semID, 0, SETVAL, val) == -1) {
     printf("Error, no se pudo cambiar el valor del semaforo\n");
   }
 }

/*  Crea el semaforo y le establece un valor por defecto.

    seed: El valor para la semilla del semaforo.
    value: Establecer el valor por defecto del semaforo.

    Devuelve el valor el indentificador del semaforo.
*/
 int semCreate(int seed, int value){
   int semID = semGet(seed);
   //printf("seed : %d semID: %d\n",seed, semID );
   semSet(semID, value);
   return semID;
 }

 /* Aumenta el contador del semaforo

    semID: El id del semaforo.
 */
 int semSignal(int semID){
   // Indica el numero del semaforo y el incremento que tendra.
   struct sembuf op[] = {0, 1, 0};
   if (semop(semID, op, 1) == -1) {
     printf("Error, no se pudo aumentar el semaforo\n");
   }
 }

 /* Disminuye el contador del semaforo

    semID: El id del semaforo.
 */
 int semWait(int semID){
   // Indica el numero del semaforo y el incremento que tendra.
   struct sembuf op [] = {0, -1, 0};
   if (semop(semID, op, 1) == -1) {
     printf("Error, no se pudo disminuir el semaforo\n");
   }
 }
