#ifndef SHARED_MEMORY
#define SHARED_MEMORY

int getSharedMemory(int seed, int size);
int deleteMemoryShare(int memID);
int disassociateProcess(char *address);
char* associateProcess(int memID);
#endif
