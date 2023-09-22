#pragma once
class Bitmap;
class ResourceManager
{
private:
	static map<int, Bitmap*> _resource;
public:
	static void InsertBitmap(int key, Bitmap* bitmap);
	static Bitmap* GetBitmap(int key);
	static void RemoveBitmap(int key);
};

