#pragma once
#include "CBase.h"

class CAsset :
	public CBase
{
private:
    wstring     m_Key;              // 에셋 키값
    wstring     m_RelativePath;     // 에셋 상대경로
    AssetType   m_Type;             // 에셋 타입

public:
    void SetKey(const wstring& _Key) { m_Key = _Key; }
    const wstring& GetKey() { return m_Key; }

    void SetRelativePath(const wstring& _Path) { m_RelativePath = _Path; }
    const wstring& GetRelativePath() { return m_RelativePath; }

    virtual int Load(const wstring& _RelativePath) = 0;
    virtual int Save(const wstring& _RelativePath) { return 0; }

public:
    CAsset(AssetType _Type);
    virtual ~CAsset();
};

