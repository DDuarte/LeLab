#ifndef IAPPLICATION_H
#define IAPPLICATION_H

#include "Singleton.h"

class IApplication : public Singleton<IApplication>
{
public:
    virtual void Run(int argc, char* argv[]) = 0;
private:
};

#endif // IAPPLICATION_H
