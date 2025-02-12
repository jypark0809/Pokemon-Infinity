#pragma once
#include "CComponent.h"
class CGrid :
    public CComponent
{
private:
    UINT m_CellSize;
    UINT m_Columns;
    UINT m_Rows;

private:
    void DrawGrid(HDC _hdc, Vec2 vPos, UINT m_CellSize, UINT m_Row, UINT m_Col);

public:
    virtual void BeginPlay() override;
    virtual void Tick()override;
    virtual void FinalTick() override;
    virtual void Render(HDC _hdc) override;

public:
    CGrid(UINT _CellSize, UINT _Columns, UINT _Rows);
    ~CGrid();
};

