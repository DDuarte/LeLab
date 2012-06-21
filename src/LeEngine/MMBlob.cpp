#include "MMBlob.h"

template <class T, int i>
inline T& MMBlob<T, i>::operator[](int index)
{
    assert(index < i && "Bad index on MMBlob::[]");
    return buffer[index];
}

template <class T>
inline T& MMDynamicBlob<T>::operator[](int index)
{
    assert(index < _dataSize && "Bad index on MMDynamicBlob::[]");
    return buffer[index];
}
