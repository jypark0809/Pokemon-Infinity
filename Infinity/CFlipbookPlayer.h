#pragma once
#include "CComponent.h"

class CFlipbook;

class CFlipbookPlayer :
    public CComponent
{

private:
    vector<CFlipbook*>  m_Flipbooks;
    CFlipbook*          m_CurFlip;
    bool                m_Loop;

public:
    virtual void BeginPlay() override;
    virtual void Tick() override;
    virtual void FinalTick() override;
    virtual void Render(HDC _hdc) override;

    void AddFlipbook(int _Idx, CFlipbook* _Flipbook);
    void Play(int _Idx, bool _Loop);

public:
    CFlipbookPlayer();
    ~CFlipbookPlayer();
};

