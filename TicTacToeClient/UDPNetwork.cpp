#include "pch.h"
#include "UDPNetwork.h"
UDPNetwork::UDPNetwork()
{
	_socket = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if (_socket == INVALID_SOCKET)
	{
		cout << "Failed socket()" << endl;
		return;
	}

	u_long on = 1;
	if (::ioctlsocket(_socket, FIONBIO, &on) == INVALID_SOCKET) 
	{
		cout << "FIONBIO Error" << endl;
		return;
	}

	memset(&_sockAddrIn, 0, sizeof(_sockAddrIn));
	_sockAddrIn.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &_sockAddrIn.sin_addr);
	_sockAddrIn.sin_port = htons(30002);

	char snedBuffer[1000] = {0};
	char* bufferPtr = (char*)snedBuffer;

	*(__int16*)bufferPtr = 4; bufferPtr += 2;
	*(__int16*)bufferPtr = 0; bufferPtr += 2;
	sendto(_socket, snedBuffer, 4, 0, (sockaddr*)&_sockAddrIn, sizeof(sockaddr));
}

UDPNetwork::~UDPNetwork()
{
	closesocket(_socket);
	WSACleanup();
}

void UDPNetwork::Recv()
{
	char buffer[1000] = {};

	int size = sizeof(_sockAddrIn);
	int recvLen = ::recvfrom(_socket, buffer, 1000, 0, (sockaddr*)&_sockAddrIn, &size);

	if (recvLen == SOCKET_ERROR)
	{
		int code = WSAGetLastError();

		if (code == WSAEWOULDBLOCK)
			return;

		// ERROR
		cout << "Recv Error" << endl;
		return;
	}
}
