#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

#define N 5

sem_t chopsticks[N];

void* philosopher(void* num) {
    int id = *(int*)num;

    printf("\nPhilosopher %d is thinking.\n", id);
    sleep(1);

    printf("\nPhilosopher %d is hungry and trying to pick up chopsticks.\n", id);

    sem_wait(&chopsticks[id]);
    printf("\nPhilosopher %d picked up left chopstick %d.\n", id, id);

    sem_wait(&chopsticks[(id + 1) % N]);
    printf("\nPhilosopher %d picked up right chopstick %d.\n", id, (id + 1) % N);

    printf("\nPhilosopher %d is eating.\n", id);
    sleep(2);

    sem_post(&chopsticks[(id + 1) % N]);
    printf("\nPhilosopher %d put down right chopstick %d.\n", id, (id + 1) % N);

    sem_post(&chopsticks[id]);
    printf("\nPhilosopher %d put down left chopstick %d.\n", id, id);

    printf("\nPhilosopher %d has finished eating and leaves the table.\n", id);

    return 0;
}

int main() {
    pthread_t philosophers[N];
    int philosopher_ids[N];

    for (int i = 0; i < N; i++) {
        sem_init(&chopsticks[i], 0, 1);
        philosopher_ids[i] = i;
    }

    for (int i = 0; i < N; i++) {
        pthread_create(&philosophers[i], NULL, philosopher, &philosopher_ids[i]);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(philosophers[i], NULL);
    }

    for (int i = 0; i < N; i++) {
        sem_destroy(&chopsticks[i]);
    }

    return 0;
}
