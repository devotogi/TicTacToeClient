#include "pch.h"
#include "Session.h"
#include "DataManager.h"
#include "Session.h"
Session::Session()
{
	_socket = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if (_socket == INVALID_SOCKET)
	{
		cout << "Failed socket()" << endl;
		return;
	}

	memset(&_sockAddrIn, 0, sizeof(_sockAddrIn));
	_sockAddrIn.sin_family = AF_INET;
	inet_pton(AF_INET, DataManager::GetInstance()->OPublicIP, &_sockAddrIn.sin_addr);
	_sockAddrIn.sin_port = htons(DataManager::GetInstance()->OPort);
}

Session::~Session()
{
	::closesocket(_socket);
}

void Session::Send(char* buffer, int size)
{ 
	sendto(_socket, buffer, size, 0, (sockaddr*)&_sockAddrIn, sizeof(sockaddr));
}
