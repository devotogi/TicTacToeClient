#pragma once
class UDPNetwork
{
private:
	SOCKET _socket;
	SOCKADDR_IN _sockAddrIn;

public:
	UDPNetwork();
	~UDPNetwork();

public:
	void Recv();
	void Send(char* buffer, int size);
};

