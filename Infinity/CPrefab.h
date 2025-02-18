#pragma once
#include "CAsset.h"
class CPrefab :
    public CAsset
{
private:
    CGameObject* m_GameObject;       // Root Object

public:
    void SetObject(CGameObject* _GameObject) { m_GameObject = _GameObject; }

    virtual int Load(const wstring& _RelativePath) override;
    virtual int Save(const wstring& _RelativePath) override;

public:
    CPrefab();
    virtual ~CPrefab();
};

