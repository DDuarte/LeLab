#include "ServerApplication.h"

int main(int argc, char * argv[])
{
    new ServerApplication();
    ServerApplication::Get().Run(argc, argv);
    delete ServerApplication::GetPtr();

    system("PAUSE");

    return 0;
}
