#include <cstdlib>
#include <string.h>
#include <pthread.h>
#include <iostream>
#include <semaphore.h>
#include <time.h>       //wg. sleep
#include <unistd.h>     //wg. sleep
#include "CStaticAllocator.h"

/* Program illustrates how Memory allocation can be handled in an own class.
 * Allocation from static heap section. Pro: no fragmentation (or better: handle fragmentation on your own!)
 * This is a simple static Memory management demo which only allocates memory and shows addresses of 
 * allocated memory by 3 different threads.*/

using namespace std;

sem_t semaphore;

struct thread_arg_t { pthread_mutex_t mutex; char thread_id[10]; };

void* thread_alloc(void *arg) {
    //copy Thread id and signal main thread to proceed
    thread_arg_t *thread_arg = reinterpret_cast<thread_arg_t*>(arg);
    char id[10];
    strcpy(id,thread_arg->thread_id);
    sem_post(&semaphore);
    
    //allocate memory from static heap
    IAllocator& staticAllocator = CStaticAllocator::getAllocator(); //Alias for CStaticAllocator instance
    int** dynamic_array = new int*[10];
    
    for (int i=0; i<10; i++) {
        int* intPtr = (int*)staticAllocator.allocate(sizeof(int));
        *intPtr = i;
        dynamic_array[i] = intPtr;
        pthread_mutex_lock(&thread_arg->mutex);
        cout << id << ": Adress of allocated variable " << i+1 << " : "<< dynamic_array[i] << endl;
        pthread_mutex_unlock(&thread_arg->mutex);
        sleep(1);
    }  
    return 0;
}
/*
 * 
 */
int main(int argc, char** argv) {
    sem_init(&semaphore,0,0);
    thread_arg_t thread_arg;
    pthread_mutex_init(&thread_arg.mutex,NULL);
    pthread_t thread1, thread2, thread3;

    //start thread1
    strcpy(thread_arg.thread_id, "thread1");
    pthread_create(&thread1,NULL,thread_alloc,reinterpret_cast<void*>(&thread_arg));
    //wait until thread_id is copied by thread
    while (sem_wait(&semaphore)) {};
    
    //start thread2
    strcpy(thread_arg.thread_id, "thread2");
    pthread_create(&thread2,NULL,thread_alloc,reinterpret_cast<void*>(&thread_arg));
    //wait until thread_id is copied by thread
    while (sem_wait(&semaphore)) {};
    
    //start thread3
    strcpy(thread_arg.thread_id, "thread3");
    pthread_create(&thread3,NULL,thread_alloc,reinterpret_cast<void*>(&thread_arg));
    //wait until thread_id is copied by thread
    while (sem_wait(&semaphore)) {};
    
    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
    pthread_join(thread3,NULL);
    return 0;
}

