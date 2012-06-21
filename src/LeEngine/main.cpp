#include "Log.h"

int main(int argc, char **argv) 
{
    Log::Get().Init();
    Log::Get().Write(LOG_ALL_INTERNAL, "Initializing...");

    // Do super complicated stuff here...

    Log::Get().Write(LOG_ALL_INTERNAL, "Closing...");
    return 0;
}
