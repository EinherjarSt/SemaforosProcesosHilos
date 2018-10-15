#ifndef SEM_MAC
#define SEM_MAC
	void init(sem_t **sem, char* pathname, int valor_inicial);
	void p(sem_t *sem);
	void v(sem_t *sem);
	void l(char *name);
	void imprimirValSem(sem_t *sem, char *name);
#endif
