#include "pch.h"
#include "CSprite.h"
#include "CTexture.h"
#include "AssetManager.h"

CSprite::CSprite()
	: CAsset(AssetType::SPRITE)
	, m_Mode(SpriteMode::SINGLE)
	, m_Atlas(nullptr)
	, m_LeftTop{}
	, m_Size{}
	, m_Offset{}
	, m_Duration(0.1f)
	, m_Border(0, 0, 0, 0)
{
}

CSprite::~CSprite()
{
}

void CSprite::Create(CTexture* _Atlas, Vec2 _LeftTop, Vec2 _Size, Vec2 _Offset, float _Duration)
{
	m_Atlas = _Atlas;
	m_LeftTop = _LeftTop;
	m_Size = _Size;
	m_Offset = _Offset;
	m_Duration = _Duration;
}

void CSprite::Render(HDC _hdc, Vec2 _OriginDest)
{
	BLENDFUNCTION blend = {};
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;
	blend.SourceConstantAlpha = 255; // 추가 알파값
	blend.AlphaFormat = AC_SRC_ALPHA; // 알파 채널의 알파값을 투명도로 사용

	AlphaBlend(_hdc
		, _OriginDest.x + m_Offset.x
		, _OriginDest.y + m_Offset.y
		, m_Size.x, m_Size.y
		, m_Atlas->GetDC()
		, m_LeftTop.x, m_LeftTop.y
		, m_Size.x, m_Size.y
		, blend);
}


int CSprite::Save(const wstring& _RelativePath)
{
	// 에셋이 저정되는 경로 (로딩된 에셋의 원본파일 위치)
	SetRelativePath(_RelativePath);

	// 파일 최종 경로
	fs::path fullPath = CONTENT_PATH;
	fullPath /= _RelativePath;

	// 파일 입출력
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, fullPath.c_str(), L"wb");
	assert(pFile);

	SaveWString(pFile, GetName());
	SaveWString(pFile, GetKey());
	SaveWString(pFile, GetRelativePath());

	fwrite(&m_LeftTop, sizeof(Vec2), 1, pFile);
	fwrite(&m_Size, sizeof(Vec2), 1, pFile);
	fwrite(&m_Offset, sizeof(Vec2), 1, pFile);
	fwrite(&m_Duration, sizeof(float), 1, pFile);

	SaveAssetInfo(pFile, m_Atlas);

	fclose(pFile);

	return S_OK;
}


int CSprite::Load(const wstring& _RelativePath)
{
	// 파일 최종 경로
	fs::path fullPath = CONTENT_PATH;
	fullPath /= _RelativePath;

	// 파일 입출력
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

	fread(&m_LeftTop, sizeof(Vec2), 1, pFile);
	fread(&m_Size, sizeof(Vec2), 1, pFile);
	fread(&m_Offset, sizeof(Vec2), 1, pFile);
	fread(&m_Duration, sizeof(float), 1, pFile);

	m_Atlas = (CTexture*)LoadAssetInfo(pFile, AssetType::TEXTURE);

	fclose(pFile);
	return S_OK;
}
