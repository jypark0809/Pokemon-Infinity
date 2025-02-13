#pragma once
#include "CRenderer.h"

class CTilemap;
class CGrid;

class CTilemapRenderer :
    public CRenderer
{
private:
    CGrid*          m_Grid;
    CTilemap*       m_Tilemap;
    UINT            m_TileSize;
    int             m_Column;
    int             m_Row;

public:
    void SetTilemap(CTilemap* _Tilemap) { m_Tilemap = _Tilemap; }
    CTilemap* GetTilemap() { return m_Tilemap; }

    void BeginPlay() override;
    void Tick() override;
    void FinalTick() override;
    void Render(HDC _hdc) override;

public:
    CTilemapRenderer();
    ~CTilemapRenderer();
};

