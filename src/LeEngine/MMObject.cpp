#include "MMObject.h"
#include "Log.h"
#include <list>
#include <boost/utility.hpp>
#include <boost/lexical_cast.hpp>

MMObject* MMObject::_liveObjects = NULL;
MMObject* MMObject::_deadObjects = NULL;
std::list<MMObject*> MMObject::_heapObjects;

MMObject::MMObject()
{
    _nextObject = NULL;
    _prevObject = NULL;
    _refCount = 0;
    std::list<MMObject*>::iterator it = std::find(_heapObjects.begin(), _heapObjects.end(), this);
    if (it == _heapObjects.end())
        _isStackAllocated = true;
    else
    {
        _isStackAllocated = false;
        _heapObjects.erase(it);
    }

    if(!_isStackAllocated)
    {
        _nextObject = _deadObjects;
        if(_deadObjects)
            _deadObjects->_prevObject = this;
        _deadObjects = this;
    }
}


void MMObject::AddRef()
{
    ++_refCount;

    if(!_isStackAllocated && _refCount == 1)
    {
        if (_prevObject)
            _prevObject->_nextObject =_nextObject;
        if (_nextObject)
            _nextObject->_prevObject = _prevObject;
        if (_deadObjects == this)
            _deadObjects = _nextObject;
        _prevObject = 0;
        _nextObject = _liveObjects;
        if(_liveObjects)
            _liveObjects->_prevObject = this;
        _liveObjects = this;
    }
}


void MMObject::Release()
{
    --_refCount;

    if(!_isStackAllocated && _refCount <= 0)
    {
        if (_prevObject)_prevObject->_nextObject = _nextObject;
        if (_nextObject)_nextObject->_prevObject = _prevObject;
        if (_liveObjects == this)
            _liveObjects = _nextObject;
        _prevObject = 0;
        _nextObject = _deadObjects;
        if (_deadObjects)
            _deadObjects->_prevObject = this;
        _deadObjects = this;
    }
}

void MMObject::CollectGarbage()
{
    // FIXME: This is deleting stuff twice, crashing
    //while (_deadObjects)
    //{
    //    MMObject* nObj = _deadObjects->_nextObject;
    //    delete _deadObjects;
    //    _deadObjects = nObj;
    //}
}

void MMObject::CollectRemainingObjects(bool withWarnings /*= false*/)
{
    // FIXME: This is deleting stuff twice, crashing
    //CollectGarbage();
    //while (_liveObjects)
    //{
    //    MMObject* obj = _liveObjects->_nextObject;
    //    if (withWarnings)
    //    {
    //        //copy the object to a temporary buffer so that our '10 bytes' message doesn't
    //        //cause an access violation
    //        char szBuf[11];
    //        memset(szBuf, 0, 11);
    //        memcpy(szBuf, _liveObjects, std::min(_liveObjects->Size(), (uint32)10));
    //        LeLog.WriteP(LOG_APP, "Unreleased MMObject at %#sX, length %u bytes, first bytes \"%.10s\"",
    //            _liveObjects, _liveObjects->Size(), szBuf);
    //    }
    //
    //    delete _liveObjects;
    //    _liveObjects = obj;
    //}
}

void* MMObject::operator new(size_t size)
{
    void* newObj = malloc(size);
    _heapObjects.push_back((MMObject*)newObj);
    return newObj;
}

void MMObject::operator delete(void* obj)
{
    if(!((MMObject*)obj)->_isStackAllocated)
        free(obj);
}
