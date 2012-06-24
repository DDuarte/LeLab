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
    T& operator [](int index) { assert(index < i && "Bad index on MMBlob::[]"); return buffer[index]; }
    //! Indirection
    operator T*() { return _buffer; }

    //! Sizeof
    AUTO_SIZE
};

#endif // MMBLOB_H
