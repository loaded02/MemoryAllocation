/* 
 * Interface
 */

#ifndef IALLOCATOR_H
#define	IALLOCATOR_H

#include <cstdlib>

class IAllocator {
public:
    virtual void* allocate(size_t memsize) = 0; //pure virtual
    virtual void deallocate(void* memptr) = 0;
protected:
    IAllocator() {};
    virtual ~IAllocator() {};
};

#endif	/* IALLOCATOR_H */

