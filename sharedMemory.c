#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

/*
  Crea una zona de memoria compartida.

  seed: El numero que se usara como semilla.
  size: El tamaño de la zona (Byte)

  Devuelve un identificador a la zona.
*/
int getSharedMemory(int seed,int size){
  key_t key = ftok("./",seed); //Crea la key para la memoria compartida.
  int memID;
  if((memID = shmget(key, size, IPC_CREAT | 0644)) == -1){
    printf("Fallo al crear la memoria compartida.\n");
  }
  return memID;
}

/*
  Borra la zona de memoria compartida. Debe ser ejecutado
  desde el proceso padre.

  memID: Es el identificador de la zona.

  Regresa -1 si hay error al liberar la memoria.
*/
int deleteMemoryShare(int memID){
  return shmctl(memID, IPC_RMID, 0);
}

/*
  Desasocia la zona de memoria del proceso que realiza la llamada a
  esta funcion.

  address: El puntero a la zona de memoria.

  Retorna -1 si hay un error al desasociar la memoria.
*/
int disassociateProcess(char *address){
  return shmdt(address);
}

/*
  Asocia la zona de memoria del proceso que realiza la llamada a
  esta funcion.

  memID: Es el identificador de la zona.

  Devuelve un puntero a la zona de memoria.
*/
char* associateProcess(int memID){
  return shmat(memID, 0, 0);
}
