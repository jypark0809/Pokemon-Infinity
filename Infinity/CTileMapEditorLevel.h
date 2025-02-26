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
    CTilemap*           m_CurrentTilemap;
    PaintingTool        m_PaintingTool;

    HMENU               m_hSubMenu;
    HWND                m_SubWnd;
    HDC                 m_hSubDC;
    CTexture*           m_SubBackBuffer;
    CTexture*           m_TileTexture;   // Tileset

    HWND                m_hComboBox;
    HWND                m_hEditControl;

public:
    virtual void BeginPlay() override;
    virtual void Tick() override;
    virtual void FinalTick() override;
    virtual void Render(HDC _hdc) override;

    virtual void OnEnter() override;
    virtual void OnExit() override;

    void SetCurrentTilemap(CTilemap* _Tilemap) { m_CurrentTilemap = _Tilemap; }
    void SetPaintingTool(PaintingTool _Tool) { m_PaintingTool = _Tool; }
    CTilemap* GetCurrentTilemap() { return m_CurrentTilemap; }
    CGrid* GetGrid() { return m_Grid; }

    CGrid* CreateGrid(int _Tilesize, int _Columns, int _Rows, const wstring& _ObjectName);
    CTilemap* AddTilemap(const wstring& _ObjectName);
    void UpdateTilePaletteHelper();

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

LRESULT CALLBACK    CreateGirdProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    TilePaletteProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    TilePaletteHelperProc(HWND, UINT, WPARAM, LPARAM);
