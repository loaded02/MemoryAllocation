#include "CStaticAllocator.h"

CStaticAllocator* CStaticAllocator::sAllocatorPtr = NULLPTR;    //wg static

pthread_mutex_t CStaticAllocator::sMutex;  //wg.static

IAllocator& CStaticAllocator::getAllocator() {
    if(NULLPTR == sAllocatorPtr) {
        pthread_mutex_lock(&sMutex);
        if(NULLPTR == sAllocatorPtr) {
            sAllocatorPtr = NEW_STATIC_DEFAULT(CStaticAllocator);
        }
        pthread_mutex_unlock(&sMutex);
    }
    return *sAllocatorPtr;      //ref to sAllocator Object
}

