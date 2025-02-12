#pragma once
#include "CComponent.h"

class CTile;

class CTilemap :
    public CComponent
{
private:
    vector<CTile*>      m_vecTile; // 모든 타일 정보

public:
    void BeginPlay() override;
    void Tick() override;
    void FinalTick() override;
    void Render(HDC _hdc) override;

    Vec2Int WorldToCell(Vec2 _Pos);

public:
    CTilemap();
    ~CTilemap();
};

