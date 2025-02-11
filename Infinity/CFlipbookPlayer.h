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
    void AddFlipbook(int _Idx, CFlipbook* _Flipbook);
    void Play(int _Idx, bool _Loop);


public:
    virtual void Tick() override;
    virtual void FinalTick() override;
    void Render(HDC _dc);

public:
    CFlipbookPlayer();
    ~CFlipbookPlayer();
};

