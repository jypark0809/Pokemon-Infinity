#include "pch.h"
#include "CPrefab.h"
#include "AssetManager.h"
#include "CGameObject.h"

CPrefab::CPrefab()
    : CAsset(AssetType::PREFAB)
{
}

CPrefab::~CPrefab()
{
    // TODO : 메모리 해제?
}

int CPrefab::Load(const wstring& _RelativePath)
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

	CGameObject* pRootObject = new CGameObject;
	if (pRootObject->Load(pFile) != S_OK)
		SAFE_DELETE(pRootObject);

	fclose(pFile);
	return S_OK;
}

int CPrefab::Save(const wstring& _RelativePath)
{
	fs::path fullPath = CONTENT_PATH;
	fullPath /= _RelativePath;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, fullPath.c_str(), L"wb");
	assert(pFile);

	SaveWString(pFile, GetName());
	SaveWString(pFile, GetKey());
	SaveWString(pFile, GetRelativePath());

	m_GameObject->Save(pFile);

	fclose(pFile);
	return S_OK;
}
