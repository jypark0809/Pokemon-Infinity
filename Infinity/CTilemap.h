#pragma once
#include "CComponent.h"

class CTile;
class CGrid;
class CTilemapRenderer;

class CTilemap :
    public CComponent
{
private:
    CGrid*              m_Grid;
    CTilemapRenderer*   m_tmRenderer;
    vector<CTile*>      m_vecTile;
    UINT                m_TileSize;
    int                 m_Column;
    int                 m_Row;

public:
    void SetGrid(CGrid* _Grid) { m_Grid = _Grid; }
    void SetTilemapRenderer(CTilemapRenderer* _tmRenderer) { m_tmRenderer = _tmRenderer; }
    vector<CTile*>& GetTileVector() { return m_vecTile; }

    void BeginPlay() override;
    void Tick() override;
    void FinalTick() override;
    void Render(HDC _hdc) override;

    Vec2Int WorldToCell(Vec2 _Pos);

public:
    CTilemap();
    ~CTilemap();
};

