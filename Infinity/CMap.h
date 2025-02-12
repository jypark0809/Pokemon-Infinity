#pragma once
#include "CGameObject.h"

class CGrid;

class CMap :
    public CGameObject
{
private:
    CGrid* m_Grid;

public:
    virtual void BeginPlay() override;
    virtual void Tick() override;
    virtual void FinalTick() override;
    virtual void Render(HDC _hdc) override;

public:
    CMap();
    ~CMap();
};

