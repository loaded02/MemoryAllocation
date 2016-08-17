/**
 *Global Definitions and Macros
 */
#ifndef GLOBAL_H
#define	GLOBAL_H

#include <assert.h>
#include <pthread.h>
#include <new>

//define nullpointer and nullchar
#define NULLPTR         0
#define NULLCHAR        0

// Macro used to round up the memory required due to the alignment
#define MAKE_ALIGNMENT_SIZE(size)  ((( (size) + (sizeof(int) - 1) ) \
                                   / sizeof(int))*sizeof(int))

// Macro used to encapsulate placement new 
#define NEW_STATIC_DEFAULT(Typ)  ( new((void*)::getStaticMemory(sizeof(Typ))) Typ() )

//Size of Static allocated Memory
static const unsigned int STATIC_MEM_SIZE = 8000000;
//Mutex for getStaticMemory())
static pthread_mutex_t gMutex;  
//Array for memory allocation
static char sMem[STATIC_MEM_SIZE];
//Pointer to current memory location
static char* sCurrentPtr = sMem;
//Pointer to end of array for limit surveillance
static const char* sMemEndPtr = sMem+STATIC_MEM_SIZE;

//global function for memory allocation
inline char* getStaticMemory(size_t memSize) {
    pthread_mutex_lock(&gMutex);
    //ASSERTION
    assert(sCurrentPtr+MAKE_ALIGNMENT_SIZE(memSize)<=sMemEndPtr);
    char* retPtr = sCurrentPtr;
    sCurrentPtr += MAKE_ALIGNMENT_SIZE(memSize);
    pthread_mutex_unlock(&gMutex);
    return retPtr;
}


#endif  /*GLOBAL_H*/