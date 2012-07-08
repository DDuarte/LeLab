#include "ServerApplication.h"

// remove
#include "Session.h"
#include <iostream>
#include "Defines.h"
#include "Packet.h"

int main(int argc, char * argv[])
{
    new ServerApplication();
    ServerApplication::Get().Run(argc, argv);
    delete ServerApplication::GetPtr();

    system("PAUSE");

    return 0;
}
