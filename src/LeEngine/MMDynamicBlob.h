#ifndef MMDYNAMICBLOB_H
#define MMDYNAMICBLOB_H

#include "MMObject.h"
#include "Defines.h"

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
    T& operator [](int index) { assert(index < _dataSize && "Bad index on MMDynamicBlob::[]"); return buffer[index]; }
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

#endif // MMDYNAMICBLOB_H
