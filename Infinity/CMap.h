#pragma once
#include "CObject.h"

class CGrid;

class CMap :
    public CObject
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

