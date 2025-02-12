#pragma once
#include "CComponent.h"
class CGrid :
    public CComponent
{
private:
    UINT m_TileSize;
    UINT m_Column;
    UINT m_Row;

private:
    void DrawGrid(HDC _hdc, Vec2 vPos, UINT m_TileSize, UINT m_Row, UINT m_Col);

public:
    void SetCellSize(UINT _Tilesize) { m_TileSize = _Tilesize; }
    void SetColumn(UINT _Column) { m_Column = _Column; }
    void SetRow(UINT _Row) { m_Row = _Row; }

    virtual void BeginPlay() override;
    virtual void Tick()override;
    virtual void FinalTick() override;
    virtual void Render(HDC _hdc) override;

public:
    CGrid();
    ~CGrid();
};

