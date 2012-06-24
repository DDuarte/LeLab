#include "GlobalTimer.h"
#include "Defines.h"
#include <ctime>

float GlobalTimer::dT = 0;
uint32 GlobalTimer::LastFrameIndex = 0;
uint32 GlobalTimer::ThisFrameIndex = 0;

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
