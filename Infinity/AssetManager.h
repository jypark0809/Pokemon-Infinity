#pragma once

class CTexture;
class CSprite;
class CFlipbook;
class CTile;
class CPrefab;

class AssetManager
{
	DECLARE_SINGLE(AssetManager)
private:
	fs::path m_ContentPath;
	map<wstring, CTexture*>		m_Textures;
	map<wstring, CSprite*>		m_Sprites;
	map<wstring, CFlipbook*>	m_Flipbooks;
	map<wstring, CTile*>		m_Tiles;
	map<wstring, CPrefab*>		m_Prefabs;

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

	CTile* GetTile(const wstring& _Key);
	CTile* LoadTile(const wstring& _Key, const wstring& _RelativePath);
	CTile* CreateTile(const wstring& _Key, CSprite* _Sprite);

	CPrefab* GetPrefab(const wstring& _Key);
	CPrefab* LoadPrefab(const wstring& _Key, const wstring& _RelativePath);
	CPrefab* CreatePrefab(const wstring& _Key, CGameObject* _GameObject);
};

