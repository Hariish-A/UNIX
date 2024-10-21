#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#include<string.h>

sem_t mutex;
int southcount = 0, northcount = 0;

void* tunnel(void* arg) {
    char* direction = (char*)arg;  // Explicitly cast to char*

    if (strcmp(direction, "North") == 0) {
        while (southcount > 0)
            sem_wait(&mutex);
        northcount++;
    } else {
        while (northcount > 0)
            sem_wait(&mutex);
        southcount++;
    }

    printf("\n %s : Entered \n", direction);

    // Critical Section (optional sleep)
    // sleep(3);

    printf("\n %s : Exiting \n", direction);

    if (strcmp(direction, "North") == 0) {
        northcount--;
    } else {
        southcount--;
    }

    sem_post(&mutex);
    return 0;
}

int main() {
    sem_init(&mutex, 0, 1);  // Initialize the semaphore

    pthread_t t1, t2, t3, t4, t5, t6, t7, t8;
    char *msg1 = "North", *msg2 = "South";

    // Create threads
    pthread_create(&t1, NULL, tunnel, (void*)msg1);
    pthread_create(&t2, NULL, tunnel, (void*)msg1);
    pthread_create(&t3, NULL, tunnel, (void*)msg2);
    pthread_create(&t4, NULL, tunnel, (void*)msg2);
    pthread_create(&t5, NULL, tunnel, (void*)msg2);
    pthread_create(&t6, NULL, tunnel, (void*)msg1);
    pthread_create(&t7, NULL, tunnel, (void*)msg1);
    pthread_create(&t8, NULL, tunnel, (void*)msg2);

    // Join threads
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);
    pthread_join(t5, NULL);
    pthread_join(t6, NULL);
    pthread_join(t7, NULL);
    pthread_join(t8, NULL);

    sem_destroy(&mutex);  // Destroy the semaphore

    return 0;
}
