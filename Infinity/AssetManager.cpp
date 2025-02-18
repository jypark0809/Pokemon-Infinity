#include "pch.h"
#include "AssetManager.h"
#include "CTexture.h"
#include "CSprite.h"
#include "CFlipbook.h"
#include "CTile.h"
#include "CPrefab.h"

AssetManager::AssetManager()
{

}

AssetManager::~AssetManager()
{
	Delete_Map(m_Textures);
	Delete_Map(m_Sprites);
	Delete_Map(m_Flipbooks);
}

void AssetManager::Init()
{
	m_ContentPath = fs::current_path();
	m_ContentPath = m_ContentPath.parent_path();
	m_ContentPath /= L"Resources";

	// fs::path relativePath = m_ContentPath.relative_path();
	// fs::path absolutePath = fs::absolute(_resourcePath);
}

CTexture* AssetManager::GetTexture(const wstring& _Key)
{
	map<wstring, CTexture*>::iterator iter = m_Textures.find(_Key);

	if (iter == m_Textures.end())
		return nullptr;

	return iter->second;
}

CTexture* AssetManager::CreateTexture(const wstring& _Key, UINT _Width, UINT _Height)
{
	CTexture* pTex = GetTexture(_Key);

	if (nullptr != pTex)
		return pTex;

	pTex = new CTexture;
	pTex->Create(_Width, _Height);
	m_Textures.insert(make_pair(_Key, pTex));

	return pTex;
}

CTexture* AssetManager::LoadTexture(const wstring& _Key, const wstring& _RelativePath)
{
	CTexture* pTex = GetTexture(_Key);

	if (nullptr != pTex)
		return pTex;

	pTex = new CTexture;
	if (FAILED(pTex->Load(_RelativePath)))
	{
		MessageBox(nullptr, L"Loading Failed to load texture", L"AssetManager", MB_OK);
		delete pTex;
		return nullptr;
	}

	pTex->SetName(_Key);
	pTex->SetKey(_Key);
	pTex->SetRelativePath(_RelativePath);
	m_Textures.insert(make_pair(_Key, pTex));

	return pTex;
}

CSprite* AssetManager::GetSprite(const wstring& _Key)
{
	map<wstring, CSprite*>::iterator iter = m_Sprites.find(_Key);

	if (iter == m_Sprites.end())
		return nullptr;

	return iter->second;
}

CSprite* AssetManager::LoadSprite(const wstring& _Key, const wstring& _RelativePath)
{
	CSprite* pSprite = GetSprite(_Key);

	if (nullptr != pSprite)
		return pSprite;

	pSprite = new CSprite;
	if (FAILED(pSprite->Load(_RelativePath)))
	{
		MessageBox(nullptr, L"Failed to load sprite", L"AssetManager", MB_OK);
		delete pSprite;
		return nullptr;
	}

	pSprite->SetKey(_Key);
	pSprite->SetRelativePath(_RelativePath);
	m_Sprites.insert(make_pair(_Key, pSprite));

	return pSprite;
}

CSprite* AssetManager::CreateSprite(const wstring& _Key, CTexture* _Tex, Vec2 _LeftTop, Vec2 _Size, Vec2 _Offset, float _Duration)
{
	CSprite* pSprite = GetSprite(_Key);

	if (nullptr != pSprite)
		return pSprite;

	pSprite = new CSprite;
	pSprite->Create(_Tex, _LeftTop, _Size, _Offset, _Duration);
	pSprite->SetName(_Key);
	pSprite->SetKey(_Key);
	m_Sprites.insert(make_pair(_Key, pSprite));

	return pSprite;
}

CFlipbook* AssetManager::GetFlipbook(const wstring& _Key)
{
	map<wstring, CFlipbook*>::iterator iter = m_Flipbooks.find(_Key);

	if (iter == m_Flipbooks.end())
		return nullptr;

	return iter->second;
}

CFlipbook* AssetManager::LoadFlipbook(const wstring& _Key, const wstring& _RelativePath)
{
	CFlipbook* pFlipbook = GetFlipbook(_Key);

	if (nullptr != pFlipbook)
		return pFlipbook;

	pFlipbook = new CFlipbook;
	if (FAILED(pFlipbook->Load(_RelativePath)))
	{
		MessageBox(nullptr, L"Failed to load flipbook", L"AssetManager", MB_OK);
		delete pFlipbook;
		return nullptr;
	}

	pFlipbook->SetName(_Key);
	pFlipbook->SetKey(_Key);
	pFlipbook->SetRelativePath(_RelativePath);
	m_Flipbooks.insert(make_pair(_Key, pFlipbook));

	return pFlipbook;
}

CFlipbook* AssetManager::CreateFlipbook(const wstring& _Key, const vector<CSprite*>& _vecSprite)
{
	CFlipbook* pFlipbook = GetFlipbook(_Key);

	if (nullptr != pFlipbook)
		return pFlipbook;

	pFlipbook = new CFlipbook;
	for (size_t i = 0; i < _vecSprite.size(); ++i)
	{
		pFlipbook->AddSprite(_vecSprite[i]);
	}
	pFlipbook->SetName(_Key);
	pFlipbook->SetKey(_Key);
	m_Flipbooks.insert(make_pair(_Key, pFlipbook));

	return pFlipbook;
}

CTile* AssetManager::GetTile(const wstring& _Key)
{
	map<wstring, CTile*>::iterator iter = m_Tiles.find(_Key);

	if (iter == m_Tiles.end())
		return nullptr;

	return iter->second;
}

CTile* AssetManager::LoadTile(const wstring& _Key, const wstring& _RelativePath)
{
	CTile* pTile = GetTile(_Key);

	if (nullptr != pTile)
		return pTile;

	pTile = new CTile;
	if (FAILED(pTile->Load(_RelativePath)))
	{
		MessageBox(nullptr, L"Failed to load flipbook", L"AssetManager", MB_OK);
		delete pTile;
		return nullptr;
	}

	pTile->SetName(_Key);
	pTile->SetKey(_Key);
	pTile->SetRelativePath(_RelativePath);
	m_Tiles.insert(make_pair(_Key, pTile));

	return pTile;
}

CTile* AssetManager::CreateTile(const wstring& _Key, CSprite* _Sprite)
{
	CTile* pTile = GetTile(_Key);

	if (nullptr != pTile)
		return pTile;

	pTile = new CTile;
	pTile->SetSprite(_Sprite);
	pTile->SetName(_Key);
	pTile->SetKey(_Key);
	m_Tiles.insert(make_pair(_Key, pTile));

	return pTile;
}

CPrefab* AssetManager::GetPrefab(const wstring& _Key)
{
	map<wstring, CPrefab*>::iterator iter = m_Prefabs.find(_Key);

	if (iter == m_Prefabs.end())
		return nullptr;

	return iter->second;
}

CPrefab* AssetManager::LoadPrefab(const wstring& _Key, const wstring& _RelativePath)
{
	CPrefab* pPrefab = GetPrefab(_Key);

	if (nullptr != pPrefab)
		return pPrefab;

	pPrefab = new CPrefab;
	if (FAILED(pPrefab->Load(_RelativePath)))
	{
		MessageBox(nullptr, L"Failed to load flipbook", L"AssetManager", MB_OK);
		delete pPrefab;
		return nullptr;
	}

	pPrefab->SetName(_Key);
	pPrefab->SetKey(_Key);
	pPrefab->SetRelativePath(_RelativePath);
	m_Prefabs.insert(make_pair(_Key, pPrefab));

	return pPrefab;
}

CPrefab* AssetManager::CreatePrefab(const wstring& _Key, CGameObject* _GameObject)
{
	CPrefab* pPrefab = GetPrefab(_Key);

	if (nullptr != pPrefab)
		return pPrefab;

	pPrefab = new CPrefab;
	pPrefab->SetName(_Key);
	pPrefab->SetKey(_Key);
	pPrefab->SetObject(_GameObject);
	m_Prefabs.insert(make_pair(_Key, pPrefab));

	return pPrefab;
}



