#include "ServerApplication.h"
#include <memory>

int main(int argc, char * argv[])
{
    std::unique_ptr<ServerApplication> sa(new ServerApplication());
    sa->Run(argc, argv);

    //new ServerApplication();
    //ServerApplication::Get().Run(argc, argv);
    //delete ServerApplication::GetPtr();

    system("PAUSE");

    return 0;
}
