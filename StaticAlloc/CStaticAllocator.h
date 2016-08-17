#ifndef CSTATICALLOCATOR_H
#define	CSTATICALLOCATOR_H

#include "IAllocator.h"
#include "Global.h"
#include <pthread.h>

/*
 * Allocates Memory from static heap section. 
 * Because its static there is no deallocate.
 * Take it and use it until system shuts down.
 */

class CStaticAllocator : public IAllocator {    //Singleton
public:
    static IAllocator& getAllocator();
    virtual void* allocate(size_t memsize) {
        return ::getStaticMemory(memsize);
    }
    virtual void deallocate(void* memptr) {};
private:
    friend class CDummy;
    static CStaticAllocator* sAllocatorPtr;
    static pthread_mutex_t sMutex;
    CStaticAllocator() {};
    CStaticAllocator(const CStaticAllocator& orig) {};
    //CStaticAllocator& operator=(const CStaticAllocator& orig) {};
    ~CStaticAllocator() {};
};

#endif	/* CSTATICALLOCATOR_H */

