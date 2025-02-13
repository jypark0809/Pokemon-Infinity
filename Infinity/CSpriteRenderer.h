#pragma once
#include "CRenderer.h"

class CSprite;
class CRenderer;

class CSpriteRenderer :
    public CRenderer
{
private:
    CSprite*        m_Sprite;

public:
    CSprite* GetSprite() { return m_Sprite; }
    void SetSprite(CSprite* _Sprite) { m_Sprite = _Sprite; }

    virtual void BeginPlay() override;
    virtual void Tick() override;
    virtual void FinalTick() override;
    virtual void Render(HDC _hdc) override;

public:
    CSpriteRenderer();
    ~CSpriteRenderer();
};