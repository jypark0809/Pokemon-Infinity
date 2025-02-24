#pragma once
#include "CLevel.h"

class CGrid;
class CTexture;
class CTilemap;
class CCamera;

class CTilemapEditorLevel :
    public CLevel
{
private:
    HWND                m_SubWnd;
    HDC                 m_hSubDC;
    CTexture*           m_SubBackBuffer;
    CTexture*           m_TileTexture;              // Tile Paletteø° æ≤¿œ Texture
    CGrid*              m_Grid;
    CTilemap*           m_Tilemap;

    // CGameObject*        m_TilePalette;
    // CCamera*            m_SubCamera;

public:
    virtual void BeginPlay() override;
    virtual void Tick() override;
    virtual void FinalTick() override;
    virtual void Render(HDC _hdc) override;

    virtual void OnEnter() override;
    virtual void OnExit() override;

    // bool Cango(Vec2Int _CellPos);
    void LoadFile();

private:
    void ChangeSubWindowSize(int _Width, int _Height);
    int SaveMap(const wstring& _RelativePath);
    int LoadMap(const wstring& _RelativePath);
    void LoadTile();

    void CreateSubWindow();
    void DestroySubWindow();


public:
    CTilemapEditorLevel();
    ~CTilemapEditorLevel();
};

LRESULT CALLBACK    TilemapEditorProc(HWND, UINT, WPARAM, LPARAM);
