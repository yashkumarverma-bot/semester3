/**
 * @author YashKumarVerma / 19BCE2669
 * @for: Lab Digital Assignment 3
 * @description: Implementation of readers-writers problem using semaphores
 */

#include<iostream>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

using namespace std;

sem_t mutex;
sem_t wrt;
int data = 0;
int readCount = 0;

/** 
 * @class Semaphore
 * @description: to define reader and writer behavior
 */
class Semaphore{
    public:


    static void *Reader(void *arg){
        int f = ((intptr_t)arg);

        sem_wait(&mutex);
        readCount += 1;
        if(readCount == 1){
            sem_wait(&wrt);
        }

        sem_post(&mutex);
        std::cout << "Data read by the reader : " << f << " is " << data << std::endl;
        sleep(1);
        
        sem_wait(&mutex);
        readCount -= 1;
        if(readCount == 0){
            sem_post(&wrt);
        }
        sem_post(&mutex);
    }

    static void *Writer(void *arg){
        int f = ((intptr_t)arg);
	    sem_wait(&wrt);
        data++;
        std::cout << "Data written by the writer : " << f << " is " << data << std::endl; 
        sleep(1);
        sem_post(&wrt);
    }
};

/** Main caller function */
int main(){
    
	int i, b;
	pthread_t readerThreadId[8], writerThreadId[8];
	sem_init(&mutex, 0, 1);
	sem_init(&wrt, 0, 1);
	for (i=0;i<=5;i++){
		pthread_create(&writerThreadId[i], NULL, Semaphore::Writer, (void *)(intptr_t)i);
		pthread_create(&readerThreadId[i], NULL, Semaphore::Reader, (void *)(intptr_t)i);
	}
	for (i=0;i<=5;i++){
		pthread_join(writerThreadId[i], NULL);
		pthread_join(readerThreadId[i], NULL);
	}
	return 0;
}