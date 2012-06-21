#ifndef MMPOINTER_H
#define MMPOINTER_H

//! Smart pointer, interacts with MObject
template <class T>
class MMPointer
{
protected:
    //! Plain pointer
    T* _obj;

public:
    //! Empty constructor
    MMPointer() : _obj(NULL) {}
    //! Constructor with a pointer
    MMPointer(T* obj) : _obj(obj) { *this = obj; }
    //! Copy constructor
    MMPointer(const MMPointer<T>& p) : _obj(NULL) { *this = p; }
    //! Destructor
    ~MMPointer() { if (_obj) _obj->Release(); }

    //! Assigning a plain pointer
    void operator =(T* obj);
    //! Assigning a smart pointer
    void operator =(const MMPointer<T>& p); 

    //! Access as a reference
    T& operator *() const;
    //! Access as a pointer
    T* operator ->() const;

    //! Automatic conversion to T*
    operator T*() const { return _obj; }

    //! Null checking
    bool IsValid() const { return _obj != NULL; }
    //! Null checking
    bool operator !() { return !_obj; }

    //! Comparison with smart pointer
    bool operator ==(const MMPointer<T>& p) const { return _obj == p._obj; }
    //! Comparison with normal pointer
    bool operator ==(const T* obj) const { return _obj == obj; }
};

#endif // MMPOINTER_H
