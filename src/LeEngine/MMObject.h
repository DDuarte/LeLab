#ifndef MMOBJECT_H
#define MMOBJECT_H

#include <list>
#include "Defines.h"

#define AUTO_SIZE uint32 Size() { return sizeof(*this); }

//! Should only be used for objects allocated in the heap (new)

//! Basic garbage collectable object (ref counting)
class MMObject
{
private:
    //! List of used memory objects
    static std::list<MMObject*> _liveObjects;
    //! List of objects that will be removed
    static std::list<MMObject*> _deadObjects;
    //! Reference count
    int32 _refCount;
    //! Iterator to the position of object in list of live objects
    std::list<MMObject*>::const_iterator _itr;

protected:
    //! Constructor
    MMObject();
    //! Virtual destructor
    virtual ~MMObject() {}

public:
    //! Increase reference count
    void AddRef() { ++_refCount; }
    //! Decrease reference count. Moves object to _deadObjects if ref count is 0.
    void Release();

    //! Frees memory. Clears list of dead objects.
    static void CollectGarbage();
    //! Frees list of live and dead objects. Can report warning if it was not empty.
    static void CollectRemainingObjects(bool withWarnings = false);
};

#endif // MMOBJECT_H
