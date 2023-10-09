#include "pch.h"
#include "Packet.h"

void Packet::deapCopyBuffer(void* src, int size)
{
	::memcpy(_buffer, src, size);
}
