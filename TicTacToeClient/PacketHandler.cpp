#include "pch.h"
#include "PacketHandler.h"

void PacketHandler::HandlePacket(shared_ptr<Packet> packet)
{
	__int16 code = packet->_pktCode;

	switch (code)
	{

	}
}
