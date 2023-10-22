#include "pch.h"
#include "App.h"
#include "D2D1Core.h"
#include "TCPNetwork.h"
#include "UDPNetwork.h"
#include "DataManager.h"
#include "PacketHandler.h"
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	TCPNetwork tcpNetwork;
	UDPNetwork udpNetwork;

	char sendBuffer[1000] = { 0 };
	char* bufferPtr = (char*)sendBuffer;

	*(__int16*)bufferPtr = 4; bufferPtr += 2; // packetSize
	*(__int16*)bufferPtr = 998; bufferPtr += 2; // packetType

	// 자신의 public Ip 받아오기
	udpNetwork.Send(sendBuffer, 4);

	while (PacketQueue::GetInstance()->GetQueue().empty())
	{
		udpNetwork.Recv();
		Sleep(1);
	}

	shared_ptr<Packet> packet = PacketQueue::GetInstance()->GetQueue().front();
	char* dataPtr = packet->GetBuffer();
	int port = *(int*)dataPtr;			dataPtr += 4;
	int publicIpSize = *(int*)dataPtr;	dataPtr += 4;
	char* publicIp = dataPtr;

	::memcpy(DataManager::GetInstance()->PublicIP, publicIp, publicIpSize);
	DataManager::GetInstance()->Port = port;
	
	IN_ADDR addr = { 0, };
	char myaddr[256] = { 0 };
	gethostname(myaddr, sizeof(myaddr));

	HOSTENT* ptr = gethostbyname(myaddr);
	while (ptr && ptr->h_name)
	{
		if (ptr->h_addrtype == PF_INET)//IPv4 주소 타입일 때
		{
			memcpy(&addr, ptr->h_addr_list[0], ptr->h_length);//메모리 복사
			break;//반복문 탈출
		}
		ptr++;
	}

	char* localIp = inet_ntoa(addr);
	int localIpSize = strlen(localIp);
	::memcpy(DataManager::GetInstance()->PrivateIP, localIp, localIpSize);

	{
		char sendBuffer[1000] = { 0 };
		char* bufferPtr = (char*)sendBuffer;

		int pktSize = 4 + 4 + 4 + localIpSize + 4 + publicIpSize;

		*(__int16*)bufferPtr = pktSize;								bufferPtr += 2;		  // packetSize
		*(__int16*)bufferPtr = C2S_CLIENTINIT;						bufferPtr += 2;		  // packetType
		*(int*)bufferPtr = port;									bufferPtr += 4;		
		*(int*)bufferPtr = localIpSize;								bufferPtr += 4;		
		::memcpy(bufferPtr, localIp, localIpSize);					bufferPtr += localIpSize;
		*(int*)bufferPtr = publicIpSize;						    bufferPtr += 4;
		::memcpy(bufferPtr, publicIp, publicIpSize);			    bufferPtr += publicIpSize;

		tcpNetwork.Send(sendBuffer, pktSize);
	}

	while (DataManager::GetInstance()->Start == false) 
	{
		tcpNetwork.Recv();

		while (PacketQueue::GetInstance()->GetQueue().empty() == false) 
		{
			shared_ptr<Packet> packet = PacketQueue::GetInstance()->GetQueue().front();
			PacketQueue::GetInstance()->GetQueue().pop();
			PacketHandler::HandlePacket(packet);

			Sleep(1);
		}
	}

	D2D1Core::GetInstance()->Init();
	App app(hInstance, 0, 0, 700, 700,&tcpNetwork,&udpNetwork);
}