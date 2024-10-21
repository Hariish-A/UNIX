#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHMSIZE 27

int main()
{
	int shmid;
	key_t key = 5678;
	char *shm, *s;

	if ((shmid = shmget(key, SHMSIZE, IPC_CREAT | 0666)) < 0)
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
	*s++ = '1';
	*s = NULL;
	printf("Process1: I have put the message %s\n", shm);

	while (*shm != '2' && *shm + 6 != 'o')
		sleep(1);
	printf("Process1: Process2 has put the message %s\n", shm);

	while (*shm != '3' && *shm + 7 != 'y')
		sleep(1);
	printf("Process1: Process3 has put the message %s\n", shm);
	printf("Process1: I am quitting \n");
	return 0;
}
