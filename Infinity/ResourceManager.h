#pragma once

class ResourceManager
{
	DECLARE_SINGLE(ResourceManager)

public:
	void Init(HWND _hwnd, fs::path _resourcePath);
	void Clear();

	const fs::path& GetResourcePath() {	return m_ResourcePath; }

private:
	HWND m_hwnd;
	fs::path m_ResourcePath;
};

