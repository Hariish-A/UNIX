#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define CHAIRS 3 // Number of chairs in the barber room
#define BENCH 3 // Number of seats in the waiting room

sem_t barber_ready; // Barber is ready to cut hair
sem_t customer_ready; // Customer is ready for haircut
sem_t mutex; // To protect shared resources

int waiting_chairs = 0; // Number of customers sitting in chairs
int bench = 0; // Number of customers waiting on the bench

// Barber function
void* barber(void* arg) {
    while (1) {
        sem_wait(&customer_ready); // Wait for a customer to arrive
        sem_wait(&mutex); // Access critical section
        waiting_chairs--; // One customer gets the haircut
        printf("Barber is cutting hair. Customers waiting: %d (Chairs) %d (Bench)\n",
               waiting_chairs, bench);
        sem_post(&barber_ready); // Signal barber is ready to cut hair
        sem_post(&mutex); // Release critical section
        sleep(2); // Simulate hair cutting
    }
}

// Customer function
void* customer(void* num) {
    int id = (int)num;
	sem_wait(&mutex); // Access critical section
    if (waiting_chairs < CHAIRS) {
        // Customer finds a chair
        waiting_chairs++;
        printf("Customer %d sitting in the barber chair. Waiting: %d\n", id, waiting_chairs);
        sem_post(&customer_ready); // Notify barber
        sem_post(&mutex); // Release critical section
        sem_wait(&barber_ready); // Wait for barber to be ready
        printf("Customer %d got a haircut.\n", id);
    } else if (bench < BENCH) {
        // If no chair, customer sits on the bench
        bench++;
        printf("Customer %d sitting on the bench. Waiting on bench: %d\n", id, bench);
        sem_post(&mutex); // Release critical section
    } else {
        // If no bench or chairs, customer leaves
        printf("Customer %d left. No space available.\n", id);
        sem_post(&mutex); // Release critical section
    }
    return NULL;
}

int main() {
    pthread_t barber_thread;
    pthread_t customer_threads[10]; // 10 customers for simulation
    int customer_ids[10];

    sem_init(&barber_ready, 0, 0); // Barber initially sleeping
    sem_init(&customer_ready, 0, 0); // No customers initially
    sem_init(&mutex, 0, 1); // Mutex for shared resources

    // Create the barber thread
    pthread_create(&barber_thread, NULL, barber, NULL);

    // Create customer threads
    for (int i = 0; i < 10; i++) {
        customer_ids[i] = i + 1;
        pthread_create(&customer_threads[i], NULL, customer, (void*)&customer_ids[i]);
        sleep(1); // Customers arriving at different times
    }

    // Wait for customer threads to finish
    for (int i = 0; i < 10; i++) {
        pthread_join(customer_threads[i], NULL);
    }

    // Cleanup
    sem_destroy(&barber_ready);
    sem_destroy(&customer_ready);
    sem_destroy(&mutex);

    return 0;
}
