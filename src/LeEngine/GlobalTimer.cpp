#include "GlobalTimer.h"
#include <ctime>

bool GlobalTimer::Start()
{
    ThisFrameIndex = clock();
    LastFrameIndex = ThisFrameIndex;
    dT = 0;
    return true;
}

void GlobalTimer::Update()
{
    LastFrameIndex = ThisFrameIndex;
    ThisFrameIndex = clock();
    dT = ((float)(ThisFrameIndex - LastFrameIndex))/1000.0f;
}
