#pragma once
class PacketHandler
{
public:
	static void HandlePacket(shared_ptr<Packet> packet);

private:
	static void HandlePacket_S2C_CLIENTINIT(shared_ptr<Packet> packet);
	static void HandlePacket_S2C_UDPINFO(shared_ptr<Packet> packet);
	static void HandlePacket_UDP_PING_RECV(shared_ptr<Packet> packet);
	static void HandlePacket_UDP_PING_SEND(shared_ptr<Packet> packet);
	static void HandlePacket_UDP_PING_COMPLETE(shared_ptr<Packet> packet);
	static void HandlePacket_UDP_PING_GAMESTART(shared_ptr<Packet> packet);
};

