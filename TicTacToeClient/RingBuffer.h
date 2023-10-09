#pragma once
// [w][][][r][][]
class RingBuffer
{
private:
	int _writePos = 0;
	int _readPos = 0;
	int _capacity = 100;
	int _size = 0;
	BYTE _buffer[100] = {};
	
public:
	RingBuffer() {};
	~RingBuffer() {};

	BYTE* GetWriteBufferPos() { return &_buffer[_writePos]; }
	BYTE* GetReadBufferPos() { return &_buffer[_readPos]; }
	BYTE* GetFirstBufferPos() { return _buffer; }
	int   GetWritePos() { return _writePos; }
	int   GetReadPos() { return _readPos; }
	int   GetDataSize() { return _size; };
	int	  GetFreeSize();
	int   GetCapacity() { return _capacity; }

	void  AddReadPos(int numOfBytes);
	void  AddWritePos(int numOfBytes);
};

