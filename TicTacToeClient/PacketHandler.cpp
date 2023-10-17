#include "pch.h"
#include "PacketHandler.h"
#include "DataManager.h"
#include "SceneManager.h"
#include "LoadingScene.h"
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

	DataManager::GetInstance()->OPort = port;
	::memcpy(DataManager::GetInstance()->OPrivateIP, localIp, localIpSize);
	::memcpy(DataManager::GetInstance()->OPublicIP, publicIp, publicIpSize);

	Scene* scene = SceneManager::GetInstance()->GetScene();
	static_cast<LoadingScene*>(scene)->SetState(LoadingState::UDPHOLEPUNCH);
}
