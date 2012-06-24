#include "MMObject.h"
#include "Log.h"
#include <list>
#include <boost/utility.hpp>
#include <boost/lexical_cast.hpp>

std::list<MMObject*> MMObject::_liveObjects;
std::list<MMObject*> MMObject::_deadObjects;

MMObject::MMObject()
{
    _liveObjects.push_back(this);
    _refCount = 0;
    _itr = boost::prior(_liveObjects.end()); // this was added to back, --end is that position
}

void MMObject::Release()
{
    --_refCount;
    if (_refCount <= 0)
    {
        _liveObjects.erase(_itr);
        _deadObjects.push_back(this);
    }
}

void MMObject::CollectGarbage()
{
    for (std::list<MMObject*>::iterator itr = _deadObjects.begin(); itr != _deadObjects.end(); ++itr)
        delete *itr;

    _deadObjects.clear();
}

void MMObject::CollectRemainingObjects(bool withWarnings /*= false*/)
{
    CollectGarbage();
    for (std::list<MMObject*>::iterator itr= _liveObjects.begin(); itr != _liveObjects.end(); ++itr)
    {
        if (withWarnings)
        {
            LeLog << LOG_APP <<
                "CollectRemainingObjects(): Deleting unreleased object (" <<
                boost::lexical_cast<char*>(*itr) << "," << 
                boost::lexical_cast<char*>(sizeof(*itr)) << " bytes" << NL;
        }
        delete *itr;
    }

    _liveObjects.clear();
}
