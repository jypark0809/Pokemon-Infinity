#pragma once
#include "CBase.h"

class CAsset :
	public CBase
{
private:
    wstring     m_Key;              // ���� Ű��
    wstring     m_RelativePath;     // ���� �����
    AssetType   m_Type;             // ���� Ÿ��

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

