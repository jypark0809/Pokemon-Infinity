#pragma once
#include "CComponent.h"

class CTilemap;

class CGrid :
    public CComponent
{
private:
    vector<CTilemap*>   m_vecTilemap;
    UINT                m_TileSize;
    int                 m_Column;
    int                 m_Row;

private:
    void DrawGrid(HDC _hdc, Vec2 vPos);

public:
    UINT GetTileSize() { return m_TileSize; }
    void SetTileSize(UINT _Tilesize) { m_TileSize = _Tilesize; }

    int GetColumn() { return m_Column; }
    void SetColumn(UINT _Column) { m_Column = _Column; }

    int GetRow() { return m_Row; }
    void SetRow(UINT _Row) { m_Row = _Row; }

    virtual void BeginPlay() override;
    virtual void Tick()override;
    virtual void FinalTick() override;
    virtual void Render(HDC _hdc) override;

public:
    CGrid();
    ~CGrid();
};

