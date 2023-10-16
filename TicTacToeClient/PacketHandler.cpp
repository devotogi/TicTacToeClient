#include "pch.h"
#include "PacketHandler.h"
#include "DataManager.h"
void PacketHandler::HandlePacket(shared_ptr<Packet> packet)
{
	__int16 code = packet->_pktCode;
	PacketType type = static_cast<PacketType>(code);

	switch (type)
	{
	case S2C_CLIENTINIT:
		HandlePacket_S2C_CLIENTINIT(packet);
		break;
	}
}

void PacketHandler::HandlePacket_S2C_CLIENTINIT(shared_ptr<Packet> packet)
{
	DataManager::GetInstance()->Start = true;
}
