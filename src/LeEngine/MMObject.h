#ifndef MMOBJECT_H
#define MMOBJECT_H

#include <list>
#include "Defines.h"

//! Should only be used for objects allocated in the heap (new)

//! Basic garbage collectable object (ref counting)
class MMObject
{
private:
    static MMObject* _liveObjects; //!> List of used memory objects
    static MMObject* _deadObjects; //!> List of objects that will be removed
    MMObject* _nextObject; //!> Pointer to next object in the list
    MMObject* _prevObject; //!> Pointer to previous object in the list
    int32 _refCount; //!> Reference count
    bool _isStackAllocated; //!> True if space was reserved
    static std::list<MMObject*> _heapObjects; //!> List of objects

protected:
    //! Constructor
    MMObject();
    //! Virtual destructor
    virtual ~MMObject() {}

public:
    //! Increase reference count
    void AddRef();
    //! Decrease reference count. Moves object to _deadObjects if ref count is 0.
    void Release();

    //! Frees memory. Clears list of dead objects.
    static void CollectGarbage();
    //! Frees list of live and dead objects. Can report warning if it was not empty.
    static void CollectRemainingObjects(bool withWarnings = false);

    virtual uint32 Size() = 0;

    void* operator new(size_t size);
    void operator delete(void* obj);
};

#define AUTO_SIZE uint32 Size() { return sizeof(*this); }

#endif // MMOBJECT_H
