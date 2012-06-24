#ifndef APPLICATION_H
#define APPLICATION_H

#include "Singleton.h"

class Application : public Singleton<Application>
{
public:
    void Run(int argc, char* argv[]);
};

#endif // APPLICATION_H
