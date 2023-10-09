#pragma once
#define Buffer 4096
class TCPNetwork
{
private:
	SOCKET _socket;
	SOCKADDR_IN _sockAddrIn;

	char _buffer[Buffer * 3] = { 0 };
	int _bufferSize = 4096;
	int _writePos = 0;
	int _readPos = 0;

public:
	TCPNetwork();
	~TCPNetwork();

public:
	void Recv();
};

