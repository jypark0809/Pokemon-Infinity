#include "pch.h"
#include "CFlipbook.h"
#include "AssetManager.h"
#include "TimeManager.h"
#include "CSprite.h"

CFlipbook::CFlipbook()
	: CAsset(AssetType::FLIPBOOK)
	, m_fbPlayer(nullptr)
	, m_Sprites{}
	, m_Index(0)
	, m_Time(0.f)
	, m_Completed(false)
{
}

CFlipbook::~CFlipbook()
{
}

void CFlipbook::FinalTick()
{
	if (m_Completed)
		return;

	m_Time += DT;

	if (m_Sprites[m_Index]->m_Duration < m_Time)
	{
		m_Time -= m_Sprites[m_Index]->m_Duration; // m_Duration(초)보다 더 지난 시간 보정
		if (m_Index < m_Sprites.size() - 1)
			m_Index++;
		else
			m_Completed = true;
	}
}

int CFlipbook::Save(const wstring& _RelativePath)
{
	fs::path fullPath = CONTENT_PATH;
	fullPath /= _RelativePath;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, fullPath.c_str(), L"wb");
	assert(pFile);

	SaveWString(pFile, GetName());
	SaveWString(pFile, GetKey());
	SaveWString(pFile, GetRelativePath());

	size_t SpriteCount = m_Sprites.size();
	fwrite(&SpriteCount, sizeof(size_t), 1, pFile);

	for (size_t i = 0; i < SpriteCount; ++i)
	{
		SaveAssetInfo(pFile, m_Sprites[i]);
	}

	fclose(pFile);
	return S_OK;
}

int CFlipbook::Load(const wstring& _RelativePath)
{
	fs::path fullPath = CONTENT_PATH;
	fullPath /= _RelativePath;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, fullPath.c_str(), L"rb");
	assert(pFile);

	wstring Name, Key, Path;
	LoadWString(pFile, Name);
	LoadWString(pFile, Key);
	LoadWString(pFile, Path);

	SetName(Name);
	SetKey(Key);
	SetRelativePath(Path);

	size_t SpriteCount = 0;
	fread(&SpriteCount, sizeof(size_t), 1, pFile);

	for (size_t i = 0; i < SpriteCount; ++i)
	{
		CSprite* pSprite = (CSprite*)LoadAssetInfo(pFile, AssetType::SPRITE);
		m_Sprites.push_back(pSprite);
	}

	fclose(pFile);
	return S_OK;
}

void CFlipbook::Reset()
{
	m_Time = 0.0f;
	m_Index = 0;
	m_Completed = false;
}