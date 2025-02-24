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
    int                 m_TileSize;
    int                 m_Column;
    int                 m_Row;

public:
    void SetGrid(CGrid* _Grid);
    void SetTilemapRenderer(CTilemapRenderer* _tmRenderer) { m_tmRenderer = _tmRenderer; }

    int GetRow() { return m_Row; }
    int GetColumn() { return m_Column; }
    int GetTileSize() { return m_TileSize; }

    void AddTile(int _Column, int _Row, const wstring& _SpriteKey);
    vector<CTile*>& GetTileVector() { return m_vecTile; }

    void BeginPlay() override;
    void Tick() override;
    void FinalTick() override;
    void Render(HDC _hdc) override;

    Vec2Int WorldToCell(Vec2 _Pos);

    virtual int Save(FILE* _File) { return S_OK; }
    virtual int Load(FILE* _File) { return S_OK; }

public:
    CTilemap();
    ~CTilemap();
};

