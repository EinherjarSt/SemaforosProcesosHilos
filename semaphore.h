#ifndef SEMAPHORE
#define SEMAPHORE

int semCreate(int seed, int value);
int semSignal(int semID);
int semWait(int semID);
#endif
