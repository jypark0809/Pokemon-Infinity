#include "pch.h"
#include "CTile.h"
#include "AssetManager.h"
#include "CSprite.h"

CTile::CTile()
    : CAsset(AssetType::TILE)\
    , m_Sprite(nullptr)
    , m_Blocked(false)
{
}

CTile::~CTile()
{
}

int CTile::Save(const wstring& _RelativePath)
{
	// ������ �����Ǵ� ��� (�ε��� ������ �������� ��ġ)
	SetRelativePath(_RelativePath);

	// ���� ���� ���
	fs::path fullPath = CONTENT_PATH;
	fullPath /= _RelativePath;

	// ���� �����
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, fullPath.c_str(), L"wb");
	assert(pFile);

	SaveWString(pFile, GetName());
	SaveWString(pFile, GetKey());
	SaveWString(pFile, GetRelativePath());

	fwrite(&m_Blocked, sizeof(bool), 1, pFile);
	SaveAssetInfo(pFile, m_Sprite);

	fclose(pFile);

	return S_OK;
}

int CTile::Load(const wstring& _RelativePath)
{
	// ���� ���� ���
	fs::path fullPath = CONTENT_PATH;
	fullPath /= _RelativePath;

	// ���� �����
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

	fread(&m_Blocked, sizeof(bool), 1, pFile);

	m_Sprite = (CSprite*)LoadAssetInfo(pFile, AssetType::SPRITE);

	fclose(pFile);
	return S_OK;
}

