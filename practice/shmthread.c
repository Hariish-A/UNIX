#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>
#define SHMSIZE 27

int main(void)
{
    int shmid;
    key_t key = 2041;
    char *s;
    char *shm;

    if (fork( ) == 0)
    {
        sleep(5);
        if ((shmid = shmget(key, SHMSIZE, 0666)) < 0)
        {
            exit(1);
        }

        if ((shm = shmat(shmid, NULL, 0)) == (char *) -1)
        {
            exit(1);
        }

        printf ("\nChild Reading ....\n\n");

        for (s = shm; *s != NULL; s++)
            putchar(*s);

        putchar('\n');
    }

    else
    {
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

        printf ("Parent Writing ....\n\n") ;
        for (char c = 'a'; c <= 'z'; c++)
	{
            *s++ = c;
	    putchar(c);
        }
	*s = NULL;

        putchar('\n');
        wait(NULL);

        shmdt(shm);

	if(shmctl(shmid, IPC_RMID, NULL) < 0)
	{
		perror("shmctl");
		exit(-1);
	}
    }
    exit(0);
}


