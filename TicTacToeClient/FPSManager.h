#pragma once
class FPSManager
{
private:
	static FPSManager* _instance;
	int _lastTick = 0;
	int _sumTick = 0;

public:
	static FPSManager* GetInstnace() 
	{
		if (_instance == nullptr)
			_instance = new FPSManager();

		return _instance;
	}

	bool Ok();
};

