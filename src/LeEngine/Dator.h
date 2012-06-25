#ifndef DATOR_H
#define DATOR_H

#include <string>
#include <list>
#include <algorithm>
#include <boost/lexical_cast.hpp>

class BaseDator
{
protected:
    BaseDator() {}
    BaseDator(BaseDator& b) { *this = b; }

public:
    virtual BaseDator& operator =(std::string& s) = 0;
    virtual BaseDator& operator +=(std::string& s) = 0;
    virtual BaseDator& operator -=(std::string& s) = 0;
    virtual bool operator ==(std::string& s) = 0;
    virtual bool operator !=(std::string& s) = 0;
    virtual operator std::string() = 0;

    virtual bool HasMultipleValues() const = 0;
};

template <class T>
class Dator : public BaseDator
{
protected:
    T& _target;
    T ToVal(std::string& s) { return boost::lexical_cast<T, std::string>(s); }
    std::string ToString(T& val) { return boost::lexical_cast<std::string, T>(val); }

public:
    Dator(T& t) : _target(t) {}

    BaseDator& operator =(std::string& s) { _target = ToVal(s); return *this; }
    BaseDator& operator +=(std::string& s) { _target += ToVal(s); return *this; }
    BaseDator& operator -=(std::string& s) { _target -= ToVal(s); return *this; }
    bool operator ==(std::string& s) { return s == (std::string)(*this); }
    bool operator !=(std::string& s) { return s != (std::string)(*this); }
    operator std::string() { return ToString(_target); }

    bool HasMultipleValues() const { return false; }
};

template <class T>
class ListDator : public BaseDator
{
protected:
    std::list<T>& _values;
    T ToVal(std::string& s) { return boost::lexical_cast<T, std::string>(s); }

    std::string ToString(T& val) { return boost::lexical_cast<std::string, T>(val); }

public:
    ListDator(std::list<T>& v) : _values(v) {}

    BaseDator& operator =(std::string& s) { _values.clear(); _values.push_back(ToVal(s)) return *this; }
    BaseDator& operator +=(std::string& s) { _values.push_back(ToVal(s)) return *this; }
    BaseDator& operator -=(std::string& s) { _values.remove(ToVal(s)); return *this; }
    bool operator ==(std::string& s) { return std::find(_values.begin(), _values.end(), ToVal(s)) != _values.end(); }
    bool operator !=(std::string& s) { return !((*this) == s); }
    operator std::string() { return ToString(_values.back()); }
    operator std::list<T>&() { return _values; }
 
    bool HasMultipleValues() const { return true; }
};


#endif // DATOR_H
