#pragma once
#include "CAsset.h"

class CSprite;

class CTile :
    public CAsset
{
    CSprite*    m_Sprite;
    bool        m_Blocked;

public:
    virtual int Save(const wstring& _RelativePath) override;
    virtual int Load(const wstring& _RelativePath) override;

    // void AddSprite(CSprite* _Sprite) { m_Sprites.push_back(_Sprite); }

public:
    CTile();
    ~CTile();
};

