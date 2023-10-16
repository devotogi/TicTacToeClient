#pragma once
class PacketHandler
{
public:
	static void HandlePacket(shared_ptr<Packet> packet);

private:
	static void HandlePacket_S2C_CLIENTINIT(shared_ptr<Packet> packet);
};

