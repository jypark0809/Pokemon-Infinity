#pragma once
#include "CComponent.h"

class CTilemapRenderer :
    public CComponent
{
private:

public:
    void BeginPlay() override;
    void Tick() override;
    void FinalTick() override;
    void Render(HDC _hdc) override;

public:
    CTilemapRenderer();
    ~CTilemapRenderer();
};

