#include "pch.h"
#include "PacketHandler.h"
#include "DataManager.h"
#include "SceneManager.h"
#include "LoadingScene.h"
#include "Session.h"
#include "MultiGameScene.h"

void PacketHandler::HandlePacket(shared_ptr<Packet> packet)
{
	__int16 code = packet->_pktCode;
	PacketType type = static_cast<PacketType>(code);

	switch (type)
	{
	case S2C_CLIENTINIT:
		HandlePacket_S2C_CLIENTINIT(packet);
		break;

	case S2C_UDPINFO:
		HandlePacket_S2C_UDPINFO(packet);
		break;

	case UDP_PING_RECV:
		HandlePacket_UDP_PING_RECV(packet);
		break;

	case UDP_PING_COMPLETE:
		HandlePacket_UDP_PING_COMPLETE(packet);
		break;

	case UDP_PING_SETSTONE:
		HandlePacket_UDP_PING_SETSTONE(packet);
		break;

	case UDP_PING_RESULT:
		HandlePacket_UDP_PING_RESULT(packet);
		break;

	case UDP_PING_TIMEOUT:
		HandlePacket_UDP_PING_TIMEOUT(packet);
		break;
	}
}

void PacketHandler::HandlePacket_S2C_CLIENTINIT(shared_ptr<Packet> packet)
{
	DataManager::GetInstance()->Start = true;
}

void PacketHandler::HandlePacket_S2C_UDPINFO(shared_ptr<Packet> packet)
{
	char* buffer = packet->GetBuffer();
	int localIpSize = *(int*)buffer;	buffer += 4;
	char* localIp = (char*)buffer;		buffer += localIpSize;
	int publicIpSize = *(int*)buffer;	buffer += 4;
	char* publicIp = (char*)buffer;		buffer += publicIpSize;
	int port = *(int*)buffer;			buffer += 4;
	int playerNumber = *(int*)buffer;	buffer += 4;

	DataManager::GetInstance()->OPort = port;
	::memcpy(DataManager::GetInstance()->OPrivateIP, localIp, localIpSize);
	::memcpy(DataManager::GetInstance()->OPublicIP, publicIp, publicIpSize);
	DataManager::GetInstance()->PlayerNumber = playerNumber;

	DataManager::GetInstance()->Session = ::make_shared<Session>();

	Scene* scene = SceneManager::GetInstance()->GetScene();
	static_cast<LoadingScene*>(scene)->SetState(LoadingState::UDPHOLEPUNCH);
}

void PacketHandler::HandlePacket_UDP_PING_RECV(shared_ptr<Packet> packet)
{
	Scene* scene = SceneManager::GetInstance()->GetScene();
	static_cast<LoadingScene*>(scene)->AddPercent();
}

void PacketHandler::HandlePacket_UDP_PING_SEND(shared_ptr<Packet> packet)
{
	char buffer[100] = {0};
	char* bufferPtr = reinterpret_cast<char*>(buffer);
	
	*(__int16*)bufferPtr = 4;				bufferPtr += 2;
	*(__int16*)bufferPtr = UDP_PING_RECV;	bufferPtr += 2;

	DataManager::GetInstance()->Session->Send(buffer, 4);
}

void PacketHandler::HandlePacket_UDP_PING_COMPLETE(shared_ptr<Packet> packet)
{
	Scene* scene = SceneManager::GetInstance()->GetScene();
	static_cast<LoadingScene*>(scene)->CanComplete();
}

void PacketHandler::HandlePacket_UDP_PING_GAMESTART(shared_ptr<Packet> packet)
{
	Scene* scene = SceneManager::GetInstance()->GetScene();
	static_cast<LoadingScene*>(scene)->GameStart();
}

void PacketHandler::HandlePacket_UDP_PING_SETSTONE(shared_ptr<Packet> packet)
{
	Scene* scene = SceneManager::GetInstance()->GetScene();

	char* buffer = packet->GetBuffer();
	int y = *(int*)buffer;	buffer += 4;
	int x = *(int*)buffer;	buffer += 4;

	static_cast<MultiGameScene*>(scene)->SetStone(y, x);
}

void PacketHandler::HandlePacket_UDP_PING_RESULT(shared_ptr<Packet> packet)
{
	Scene* scene = SceneManager::GetInstance()->GetScene();

	char* buffer = packet->GetBuffer();
	int gameResult = *(int*)buffer;	buffer += 4;
	gameResult *= -1;
	static_cast<MultiGameScene*>(scene)->GameResult(static_cast<ResultType>(gameResult));
}

void PacketHandler::HandlePacket_UDP_PING_TIMEOUT(shared_ptr<Packet> packet)
{
	Scene* scene = SceneManager::GetInstance()->GetScene();
	static_cast<MultiGameScene*>(scene)->TimeOut();
}

void PacketHandler::HandlePacket_UDP_TIME_FLOW(shared_ptr<Packet> packet)
{
	Scene* scene = SceneManager::GetInstance()->GetScene();
	char* buffer = packet->GetBuffer();
	int time = *(int*)buffer;	buffer += 4;
	static_cast<MultiGameScene*>(scene)->TimeFlow(time);
}
