#pragma once
class PacketHandler
{
public:
	static void HandlePacket(shared_ptr<Packet> packet);
};

