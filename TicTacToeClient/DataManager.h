#pragma once
class DataManager
{
public:
	static DataManager* GetInstance() 
	{
		static DataManager dataManager;

		return &dataManager;
	}

	char PrivateIP[30] = { 0 };
	char PublicIP[30] = { 0 };
	unsigned int Port;

	char OPrivateIP[30] = { 0 };
	char OPublicIP[30] = { 0 };
	unsigned int OPort;

	bool Start = false;
};

