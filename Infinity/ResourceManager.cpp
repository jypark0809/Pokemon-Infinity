#include "pch.h"
#include "ResourceManager.h"

ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{
	Clear();
}

void ResourceManager::Init(HWND _hwnd, fs::path _resourcePath)
{
	m_hwnd = _hwnd;
	m_ResourcePath = _resourcePath;

	// fs::current_path();
	// m_ResourcePath.relative_path();
	// fs::absolute(_resourcePath);
}
