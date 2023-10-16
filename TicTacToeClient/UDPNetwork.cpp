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
	inet_pton(AF_INET, "58.236.130.58", &_sockAddrIn.sin_addr);
	_sockAddrIn.sin_port = htons(30002);
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

	char* bufferPtr = buffer;

	shared_ptr<Packet> packet = make_shared<Packet>();
	packet->_pktSize = *(__int16*)bufferPtr;
	packet->_pktCode = *(__int16*)(bufferPtr + 2);
	char* dataPtr = (bufferPtr + 4);
	packet->deapCopyBuffer(dataPtr, packet->_pktSize - 4);
	PacketQueue::GetInstance()->GetQueue().push(packet);
}

void UDPNetwork::Send(char* buffer, int size)
{
	sendto(_socket, buffer, size, 0, (sockaddr*)&_sockAddrIn, sizeof(sockaddr));
}
