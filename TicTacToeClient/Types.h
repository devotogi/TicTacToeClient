#pragma once

enum SceneType :int
{
	Menu,
	SingelGame,
	Loading,
	MultiGame
};

enum BitmapName : int 
{
	MenuBg = 0,
	SingGameBg = 1,
	P1OBg = 2,
	P2XBg = 3,
	LoadingBg = 4,
};

enum UIType : int 
{
	SingleGameBtn = 0,
	SingleGameBackBtn = 1,
	MultiGameBtn = 2,
};

enum ResultType : int
{
	DEFAULT = 2,
	WIN = 1,
	DRAW = 0,
	LOSE = -1
};

enum TileType : int
{
	None = 0,
	P1O = 1,
	P2X = 2
};

struct Pos
{
	int x = 0;
	int y = 0;

	bool operator==(const Pos& other)
	{
		return other.x == x && other.y == y;
	}

	bool operator!= (const Pos& other)
	{
		return !(*this == other);
	}

	bool operator<(const Pos& other) const
	{
		if (y != other.y)
			return y < other.y;
		return x < other.x;
	}

	bool operator>(const Pos& other) const
	{
		if (y != other.y)
			return y > other.y;
		return x > other.x;
	}
};

enum PacketType : __int16 
{
	S2C_CLIENTINIT,
	C2S_CLIENTINIT,
	C2S_CLIENTREADY,
	S2C_UDPINFO,
	UDP_PING_SEND,
	UDP_PING_RECV,
	UDP_PING_COMPLETE,
	UDP_PING_GAMESTART,
	UDP_PING_SETSTONE,
	UDP_PING_RESULT,
	UDP_PING_TIMEOUT,
	UDP_TIME_FLOW,
	C2S_GAME_END,
	S2C_EXIT_ROOM,
};

enum LoadingState : __int16 
{
	WANTPING,
	UDPHOLEPUNCH,
	END,
};