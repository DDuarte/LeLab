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

        _singleton = static_cast<T*>(this);
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
