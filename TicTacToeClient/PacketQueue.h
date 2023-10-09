#pragma once
class PacketQueue
{
private:
	queue<shared_ptr<Packet>> _q;

public:
	static PacketQueue* GetInstance()
	{
		static PacketQueue packetQueue;
		return &packetQueue;
	}

	queue<shared_ptr<Packet>>& GetQueue()
	{
		return _q;
	}
};

