#ifndef FUNCTOR_H
#define FUNCTOR_H

#include "MMObject.h"
#include "MMPointer.h"

class Functor : public MMObject
{
public:
    virtual void operator() = 0;
};

template <class T>
class ObjFunctor : Functor
{
protected:
    T* _obj;
    typedef void (T::*funcType)();
    funcType _func;

public:
    AUTO_SIZE;

    ObjFunctor(T* obj, funcType func) : _obj(obj), _func(func) {}

    void operator()() { (_obj->*func)(); }

};

template <class T>
class MMObjFunctor : Functor
{
protected:
    MMPointer<T> _obj;
    typedef int (T::*funcType)();
    funcType _func;

public:
    AUTO_SIZE;

    ObjFunctor(T* obj, funcType func) : _obj(obj), _func(func) {}

    int operator()() { return (_obj->*func)(); }

};

#endif // FUNCTOR_H
