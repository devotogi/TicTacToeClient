#pragma once
class UDPNetwork
{
private:
	SOCKET _socket;
	SOCKADDR_IN _sockAddrIn;

	int _lastTick = 0;
	int _sumTick = 0;

public:
	UDPNetwork();
	~UDPNetwork();

public:
	void Recv();
	void Send(char* buffer, int size);
	void Ping();
};

