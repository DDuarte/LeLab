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

    //! Access as a reference
    T& operator *() const { assert(_obj && "Tried to * on a NULL smart pointer"); return *_obj; }
    //! Access as a pointer
    T* operator ->() const { assert(_obj && "Tried to -> on a NULL smart pointer"); return _obj; }

    //! Assigning a plain pointer
    void operator=(T* obj)
    {
        if (_obj) _obj->Release();
        _obj = obj;
        if (_obj) _obj->AddRef();
    }

    //! Assigning a smart pointer
    void operator=(const MMPointer<T>& p)
    {
        if(_obj) _obj->Release();
        _obj = p._obj;
        if(_obj) _obj->AddRef();
    }

    //! Automatic conversion to plain pointer
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
