#ifndef APPLICATION_H
#define APPLICATION_H

#include "IApplication.h"

class Application : public IApplication
{
public:
    void Run(int argc, char* argv[]);
};

#endif // APPLICATION_H
