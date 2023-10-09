#include "pch.h"
#include "TCPNetwork.h"

TCPNetwork::TCPNetwork()
{
	WSAData wsaData;

	if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		cout << "WSAStartup Error" << endl;
		return;
	}

	_socket = ::socket(AF_INET, SOCK_STREAM, 0);

	if (_socket == INVALID_SOCKET)
	{
		cout << "Create Socket Error" << endl;
		return;
	}

	u_long on = 1;
	if (::ioctlsocket(_socket, FIONBIO, &on) == INVALID_SOCKET)
	{
		cout << "FIONBIO Error" << endl;
		return;
	}

	::memset(&_sockAddrIn, 0, sizeof(_sockAddrIn));
	_sockAddrIn.sin_family = AF_INET;
	::inet_pton(AF_INET, "127.0.0.1", &_sockAddrIn.sin_addr);
	_sockAddrIn.sin_port = ::htons(7777);

	while (true)
	{
		if (::connect(_socket, (SOCKADDR*)&_sockAddrIn, sizeof(_sockAddrIn)) == SOCKET_ERROR)
		{
			// 원래 블록했어야 했는데... 너가 논블로킹으로 하라며?
			if (::WSAGetLastError() == WSAEWOULDBLOCK)
				continue;
			// 이미 연결된 상태라면 break
			if (::WSAGetLastError() == WSAEISCONN)
				break;
			// Error
			Sleep(1000);
		}
	}
}

TCPNetwork::~TCPNetwork()
{
	::closesocket(_socket);
	::WSACleanup();
}

void TCPNetwork::Recv()
{
	int recvLen = ::recv(_socket, _buffer, _bufferSize - _writePos, 0);

	if (recvLen == SOCKET_ERROR)
	{
		int code = WSAGetLastError();

		if (code == WSAEWOULDBLOCK)
			return;

		// ERROR
		cout << "Recv Error" << endl;

		return;
	}

	_writePos += recvLen;

	while (true)
	{
		if (_writePos >= Buffer * 2)
		{
			int dataSize = _writePos - _readPos;
			::memcpy(&_buffer[0], &_buffer[_readPos], dataSize);
			_readPos = 0;
			_writePos = dataSize;
		}

		int dataSize = _writePos - _readPos;

		if (dataSize < 2) // pkt HeaderSize 
			return;

		__int16* pktSizePtr = reinterpret_cast<__int16*>(&_buffer[_readPos]);
		__int16 pktSize = *pktSizePtr;

		__int16* pktCode = pktSizePtr + 1;

		if (dataSize < pktSize)
			return;

		shared_ptr<Packet> packet = make_shared<Packet>();
		packet->_pktSize = pktSize;
		packet->_pktCode = *pktCode;
		packet->deapCopyBuffer(&_buffer[_readPos + 4], pktSize - 4);
		PacketQueue::GetInstance()->GetQueue().push(packet);

		_readPos += pktSize;

		if (_readPos == _writePos)
		{
			_readPos = 0;
			_writePos = 0;
		}
	}
}
