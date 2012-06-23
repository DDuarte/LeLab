#ifndef SINGLETON_H
#define SINGLETON_H

#include <cassert>
#include <iostream>

template <class T>
class Singleton
{
    static T* _singleton;

public:
    Singleton()
    {
        assert(!_singleton);

        int offset = (int)(T*)1 - (int)(Singleton<T>*)(T*)1;
        _singleton = (T*)((int)this + offset);
    }

    ~Singleton()
    {
        assert(_singleton);
        _singleton = NULL;
    }

    static T& Get()
    {
        assert(_singleton);
        return *_singleton;
    }

    static T* GetPtr()
    {
        assert(_singleton);
        return _singleton;
    }
};

template <class T>
T* Singleton<T>::_singleton = NULL;

#endif // SINGLETON_H
