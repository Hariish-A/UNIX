#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#define SHMSIZE 27

int main()
{
	int shmid;
	char *s, *shm;
	key_t key = 5678;

	if (shmid = shmget(key, SHMSIZE, IPC_CREAT | 0666) < 0)
	{
		perror("shmget");
		exit(1);
	}

	if ((shm = shmat(shmid, NULL, 0)) == (char *) -1)
	{
		perror("shmat");
		exit(1);
	}

	s = shm;

	for (char c = 'a'; c <= 'z'; c++)
		*s++ = c;
	*s = NULL;

	while (*shm != '*')
		sleep(1);

	printf("\n\nServer Process Complete.\n\n");
	exit(0);
}
