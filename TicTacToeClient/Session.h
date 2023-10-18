#pragma once
class Session
{
private:
	SOCKET _socket;
	SOCKADDR_IN _sockAddrIn;

public:
	Session();
	~Session();

	void Send(char* buffer, int size);
};

