#pragma once
#include "CAsset.h"

enum SpriteMode
{
    SINGLE,     // Single
    MULTIPLE    // Atlas
};

struct Border
{
    UINT Left;
    UINT Right;
    UINT Top;
    UINT Bottom;

    Border(UINT _Left, UINT _Right, UINT _Top, UINT _Bottom)
    {
        Left = _Left;
        Right = _Right;
        Top = _Top;
        Bottom = _Bottom;
    }
};

class CTexture;

class CSprite :
    public CAsset
{
private:
    SpriteMode  m_Mode;
    CTexture*   m_Atlas;
    Vec2        m_LeftTop;
    Vec2        m_Size;
    Vec2        m_Offset;
    float       m_Duration;     // Animation
    Border      m_Border;       // 9-slicing

public:
    CTexture* GetAltasTexture() { return m_Atlas; }
    Vec2 GetLeftTop() { return m_LeftTop; }
    Vec2 GetSize() { return m_Size; }
    Vec2 GetOffset() { return m_Offset; }
    float GetDuration() { return m_Duration; }
    Border GetBorder() { return m_Border; }

    void SetSpriteMode(SpriteMode _Mode) { m_Mode = _Mode; }
    void SetAtlas(CTexture* _Tex) { m_Atlas = _Tex; }
    void SetOffset(Vec2 _Offset) { m_Offset = _Offset; }
    void SetDuration(float _Duration) { m_Duration = _Duration; }
    void SetBorder(UINT _Left, UINT _Right, UINT _Top, UINT _Bottom)
    {
        m_Border.Left = _Left;
        m_Border.Right = _Right;
        m_Border.Top = _Top;
        m_Border.Bottom = _Bottom;
    }

public:
    virtual int Load(const wstring& _RelativePath) override;
    virtual int Save(const wstring& _RelativePath) override;
    void Create(CTexture* _Atlas, Vec2 _LeftTop, Vec2 _Size, Vec2 _Offset, float _Duration = 0.f);
    void Render(HDC _hdc, Vec2 _OriginDest);

public:
    CSprite();
    ~CSprite();

    friend class CFlipbook;
};

