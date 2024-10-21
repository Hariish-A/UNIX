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

        *shm++ = '3';
        *shm++ = ' ';
        *shm++ = 'm';
        *shm++ = 'e';
        *shm++ = 'm';
        *shm++ = 'o';
        *shm++ = 'r';
	*shm++ = 'y';
        *shm = NULL;
        exit(0);
}

