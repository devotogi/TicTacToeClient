#include "pch.h"
#include "FPSManager.h"

FPSManager* FPSManager::_instance = nullptr;

bool FPSManager::Ok()
{
    bool ok = false;

    int currentTick = ::GetTickCount64();
    int deltaTick = currentTick - _lastTick;
    _sumTick += deltaTick;

    if (_sumTick >= 50)
    {
        ok = true;
        _sumTick = 0;
    }

    _lastTick = currentTick;
    
    return ok;
}
