#pragma once
#include "CLevel.h"

class CGrid;
class CTexture;
class CTilemap;
class CCamera;

enum PaintingTool
{
    PaintBrush,
    Eraser
};

class CTilemapEditorLevel :
    public CLevel
{
private:
    HMENU               m_hMenu;
    CGrid*              m_Grid;
    CTilemap*           m_Tilemap;
    PaintingTool        m_PaintingTool;

    HMENU               m_hSubMenu;
    HWND                m_SubWnd;
    HDC                 m_hSubDC;
    CTexture*           m_SubBackBuffer;
    CTexture*           m_TileTexture;   // Tileset

public:
    virtual void BeginPlay() override;
    virtual void Tick() override;
    virtual void FinalTick() override;
    virtual void Render(HDC _hdc) override;

    virtual void OnEnter() override;
    virtual void OnExit() override;

    void SetTilemap(CTilemap* _Tilemap) { m_Tilemap = _Tilemap; }
    void SetPaintingTool(PaintingTool _Tool) { m_PaintingTool = _Tool; }
    CTilemap* GetTilemap() { return m_Tilemap; }

    void AddTilemap(const wstring& _TilemapName);

    int SaveMap();
    int LoadMap();
    void LoadFile();

private:
    void ChangeSubWindowSize(int _Width, int _Height);
    void LoadTile();

    void CreateSubWindow();
    void DestroySubWindow();


public:
    CTilemapEditorLevel();
    ~CTilemapEditorLevel();
};

LRESULT CALLBACK    TilePaletteProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    TilePaletteHelperProc(HWND, UINT, WPARAM, LPARAM);
