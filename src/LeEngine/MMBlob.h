#ifndef MMBLOB_H
#define MMBLOB_H

#include "MMObject.h"
#include "Defines.h"

//! Managed buffer, fixed size
template <class T, int i>
class MMBlob : public MMObject
{
protected:
    //! Inner buffer
    T _buffer[i];

public:
    //! Indexer
    T& operator [](int index);
    //! Indirection
    operator T*() { return _buffer; }

    //! Sizeof
    AUTO_SIZE
};

//! Managed buffer, dynamic size
template <class T>
class MMDynamicBlob : public MMObject
{
protected:
    //! Length
    uint32 _dataSize;
    //! Inner buffer
    T* _buffer;

public:
    //! Indexer
    T& operator [](int index);
    //! Indirection
    operator T*() { return _buffer; }

    //! Constructor
    MMDynamicBlob(uint32 size);
    //! Destructor
    ~MMDynamicBlob() { if (_buffer) delete[] _buffer; }

    //! Sizeof
    uint32 Size() { return _dataSize+sizeof(this); } // override
    //! Blob size
    uint32 BlobSize() { return _dataSize; }
};

#endif // MMBLOB_H
