#pragma once
#include "CAsset.h"

class CSprite;

class CTile :
    public CAsset
{
private:
    CSprite*    m_Sprite;
    bool        m_Blocked;

public:
    void SetSprite(CSprite* _Sprite) { m_Sprite = _Sprite; }
    CSprite* GetSprite() { return m_Sprite; }

    virtual int Save(const wstring& _RelativePath) override;
    virtual int Load(const wstring& _RelativePath) override;

public:
    CTile();
    ~CTile();
};

