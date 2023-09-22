#include "pch.h"
#include "ResourceManager.h"
#include "D2D1Core.h"
#include "Bitmap.h"

std::map<int, Bitmap*> ResourceManager::_resource;

void ResourceManager::InsertBitmap(int _key, Bitmap* bitmap)
{
	_resource.insert({ _key, bitmap });
}

Bitmap* ResourceManager::GetBitmap(int _key)
{
	if (_resource.find(_key) != _resource.end())
		return _resource.find(_key)->second;
	else
		return nullptr;
}

void ResourceManager::RemoveBitmap(int key)
{
	Bitmap* bitmap = GetBitmap(key);
	delete bitmap;

	_resource.erase(key);
}
