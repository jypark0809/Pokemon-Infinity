#pragma once

class CTexture;
class CSprite;
class CFlipbook;

class AssetManager
{
	DECLARE_SINGLE(AssetManager)
private:
	fs::path m_ContentPath;
	map<wstring, CTexture*>		m_Textures;
	map<wstring, CSprite*>		m_Sprites;
	map<wstring, CFlipbook*>	m_Flipbooks;

public:
	void Init();

	const fs::path& GetContentPath() { return m_ContentPath; }

	CTexture* GetTexture(const wstring& _Key);
	CTexture* LoadTexture(const wstring& _Key, const wstring& _RelativePath);
	CTexture* CreateTexture(const wstring& _Key, UINT _Width, UINT _Height);

	CSprite* GetSprite(const wstring& _Key);
	CSprite* LoadSprite(const wstring& _Key, const wstring& _RelativePath);
	CSprite* CreateSprite(const wstring& _Key, CTexture* _Tex, Vec2 _LeftTop, Vec2 _Size, Vec2 _Offset, float _Duration = 0.f);

	CFlipbook* GetFlipbook(const wstring& _Key);
	CFlipbook* LoadFlipbook(const wstring& _Key, const wstring& _RelativePath);
	CFlipbook* CreateFlipbook(const wstring& _Key, const vector<CSprite*>& _vecSprite);
};

