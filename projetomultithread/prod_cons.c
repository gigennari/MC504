#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>
#include "prod_cons.h" 

#define NUM_THREADS 5
#define NUM_MESAS 4
#define NUM_CHEFFS 1 

// int mesas_ocupadas = 0; //talvez fazer isso ser um semáforo?

sem_t semEmpty;
sem_t semFull;

pthread_mutex_t mutexBuffer;

char* buffer[NUM_MESAS]; // buffer de comida com o mesmo tamanho do numero de mesas, já q n faz sentido ser maior. Talvez fazer o buffer ter o tamanho de NUM_CHEFFS
int count = 0; // numero atual de comidas no buffer

/**
 * Cheff que produz uma comida
 * */ 
void* cheff(void* args) {
    while (1) {
        // Produce
        char* x = "Food";
        sleep(1);

        // Add to the buffer
        sem_wait(&semEmpty);
        pthread_mutex_lock(&mutexBuffer);
        buffer[count] = x;
        count++;
        pthread_mutex_unlock(&mutexBuffer);
        sem_post(&semFull);
    }
}

/** Client que vem da come algo da mesa e imprime o proprio ID. 
 * Talvez fazer esse ID ser uma "senha" que se obtem na fila, como se fosse uma senha pra obter a comida especifica.
 * */
void* client(void* args) {
    while (1) {
        char* y;
        long id = (long)args;

        // Remove from the buffer
        sem_wait(&semFull);
        pthread_mutex_lock(&mutexBuffer);
        y = buffer[count - 1];
        count--;
        pthread_mutex_unlock(&mutexBuffer);
        sem_post(&semEmpty);

        // Consume
        printf("%ld got %s\n", id ,y);
        sleep(1);
    }
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    //quando for fazer a fila, precisa fazer algum sistema pra ver qual mesa(th[id]) tá disponivel pra passar como argumento de pthread_create
    pthread_t th[NUM_THREADS]; 
    pthread_mutex_init(&mutexBuffer, NULL);
    sem_init(&semEmpty, 0, 10);
    sem_init(&semFull, 0, 0);
    long i;
    for (i = 0; i < NUM_THREADS; i++) {
        if (i < 2) {
            if (pthread_create(&th[i], NULL, cheff, (void *)i) != 0) {
                perror("Failed to create thread");
            }
        } else {
            if (pthread_create(&th[i], NULL, client, (void *)i) != 0) {
                perror("Failed to create thread");
            }
        }
    }
    for (i = 0; i < NUM_THREADS; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            perror("Failed to join thread");
        }
    }
    sem_destroy(&semEmpty);
    sem_destroy(&semFull);
    pthread_mutex_destroy(&mutexBuffer);
    return 0;
}