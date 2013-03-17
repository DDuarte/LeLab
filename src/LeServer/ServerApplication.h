#ifndef SERVERAPPLICATION_H
#define SERVERAPPLICATION_H

#include <LeEngine/IApplication.h>

class ServerApplication : public IApplication
{
public:
    void Run(int argc, char* argv[]);
};

#endif // SERVERAPPLICATION_H
