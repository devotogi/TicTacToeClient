#include "pch.h"
#include "RingBuffer.h"
// [][][][][][r/w]
int RingBuffer::GetFreeSize()
{
	int ret = 0;

	if (_readPos <= _writePos) 
		ret = _capacity - _writePos;
	else 
		ret = _readPos - _writePos;

	return ret;
}

void RingBuffer::AddReadPos(int numOfBytes)
{
	_readPos = (_readPos + numOfBytes) % _capacity;
	_size -= numOfBytes;
}

void RingBuffer::AddWritePos(int numOfBytes)
{
	_writePos = (_readPos + numOfBytes) % _capacity;
	_size += numOfBytes;
}
