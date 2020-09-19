/**
 * @author YashKumarVerma / 19BCE2669
 * @for: Lab Digital Assignment 3
 * @description: Implementation of producer consumer problem using semaphores
 */

/** defining constants for application **/
#define BUFFER_SIZE 10

/** Including Required headers **/
#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

/** 
 * @class Config
 * @description To store code configurations and local state
 **/
class Config {
public:
    static int MaxItems;
    static int BufferSize;
    static sem_t empty;
    static sem_t full;
    static int in;
    static int out;
    static int buffer[BUFFER_SIZE];
    static pthread_mutex_t mutex;
};

/** Initializing All App state **/
int Config::MaxItems = 10;
int Config::BufferSize = BUFFER_SIZE;
sem_t Config::empty;
sem_t Config::full;
int Config::in = 0;
int Config::out = 0;
int Config::buffer[BUFFER_SIZE];
pthread_mutex_t Config::mutex;

/** 
 * @class Semaphore
 * @description Class to contain definitions for Producer and Consumer
 **/
class Semaphore {
public:
    /* comsumer process */
    static void* Consumer(void* cno) {
        for (int i = 0; i < Config::MaxItems; i++) {
            sem_wait(&Config::full);
            pthread_mutex_lock(&Config::mutex);
            int item = Config::buffer[Config::out];
            printf("Consumer %d: Remove Item %d from %d\n", *((int*)cno), item, Config::out);
            Config::out = (Config::out + 1) % Config::BufferSize;
            pthread_mutex_unlock(&Config::mutex);
            sem_post(&Config::empty);
        }
    }

    /* producer process */
    static void* Producer(void* pno) {
        int item;
        for (int i = 0; i < Config::MaxItems; i++) {
            item = rand(); // Produce an random item
            sem_wait(&Config::empty);
            pthread_mutex_lock(&Config::mutex);
            Config::buffer[Config::in] = item;
            printf("Producer %d: Insert Item %d at %d\n", *((int*)pno), Config::buffer[Config::in], Config::in);
            Config::in = (Config::in + 1) % Config::BufferSize;
            pthread_mutex_unlock(&Config::mutex);
            sem_post(&Config::full);
        }
    }
};

/* main caller function */
int main(){

    pthread_t pro[5], con[5];
    pthread_mutex_init(&Config::mutex, NULL);
    sem_init(&Config::empty, 0, Config::BufferSize);
    sem_init(&Config::full, 0, 0);

    /* Just used for numbering the producer and consumer */
    int a[5] = { 1, 2, 3, 4, 5 };
    for (int i = 0; i < 5; i++) {
        pthread_create(&pro[i], NULL, Semaphore::Producer, (void*)&a[i]);
    }
    for (int i = 0; i < 5; i++) {
        pthread_create(&con[i], NULL, Semaphore::Consumer, (void*)&a[i]);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(pro[i], NULL);
    }
    for (int i = 0; i < 5; i++) {
        pthread_join(con[i], NULL);
    }

    pthread_mutex_destroy(&Config::mutex);
    sem_destroy(&Config::empty);
    sem_destroy(&Config::full);

    return 0;
}