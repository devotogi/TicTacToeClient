#pragma once
class FPS
{
private:
    int _lastTick = 0;
    int _sumTick = 0;

public:
    bool Ok()
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
};

