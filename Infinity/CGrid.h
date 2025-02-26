#pragma once
#include "CComponent.h"

class CTilemap;

class CGrid :
    public CComponent
{
private:
    vector<CTilemap*>   m_vecTilemap;
    int                 m_TileSize;
    int                 m_Column;
    int                 m_Row;

private:
    void DrawGrid(HDC _hdc, Vec2 vPos);
    

public:
    int GetRow() { return m_Row; }
    int GetColumn() { return m_Column; }
    int GetTileSize() { return m_TileSize; }
    vector<CTilemap*> GetTilemapVector() { return m_vecTilemap; }

    void SetRow(int _Row) { m_Row = _Row; }
    void SetColumn(int _Column) { m_Column = _Column; }
    void SetTileSize(UINT _Tilesize) { m_TileSize = _Tilesize; }
    void AddTilemap(CTilemap* _Tilemap) { m_vecTilemap.push_back(_Tilemap); }

    void RenderWorldScale(HDC _hdc);
    Vec2Int WorldToCell(Vec2 _WorldPosition);
    Vec2 CellToWorld(Vec2Int _CellPosition);

    virtual void BeginPlay() override;
    virtual void Tick()override;
    virtual void FinalTick() override;
    virtual void Render(HDC _hdc) override;

    virtual int Save(FILE* _File) { return S_OK; }
    virtual int Load(FILE* _File) { return S_OK; }

public:
    CGrid();
    ~CGrid();
};

