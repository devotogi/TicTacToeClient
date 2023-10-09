#pragma once
struct Packet
{
public:
	__int16 _pktSize;
	__int16 _pktCode;

private:
	char _buffer[4096] = { 0 };

public:
	void deapCopyBuffer(void* src, int size);
	char* GetBuffer() { return _buffer; }
};

