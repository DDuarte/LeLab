#include "MMPointer.h"

template <class T>
inline void MMPointer<T>::operator=(T* obj)
{
    if (_obj)
        _obj->Release();
    _obj = obj;
    if (_obj)
        _obj->AddRef();
}

template <class T>
inline void MMPointer<T>::operator=(const MMPointer<T>& p)
{
    if(_obj)
        _obj->Release();
    _obj = p._obj;
    if(_obj)
        _obj->AddRef();
}

template <class T>
inline T& MMPointer<T>::operator *() const
{
    assert(_obj && "Tried to * on a NULL smart pointer");
    return *obj;
}

template <class T>
inline T* MMPointer<T>::operator ->() const
{
    assert(_obj && "Tried to -> on a NULL smart pointer");
    return obj;
}
