#pragma once
#include "CLevel.h"

class CGrid;
class CTexture;
class CTilemap;

class CTilemapEditorLevel :
    public CLevel
{
private:
    HWND                m_SubWnd;
    HDC                 m_hSubDC;
    CTexture*           m_SubBackBuffer;

    CGrid*              m_Grid;

public:
    virtual void BeginPlay() override;
    virtual void Tick() override;
    virtual void FinalTick() override;
    virtual void Render(HDC _hdc) override;

    virtual void OnEnter() override;
    virtual void OnExit() override;

    bool Cango(Vec2Int _CellPos);

private:
    int SaveMap(const wstring& _RelativePath);
    int LoatMap(const wstring& _RelativePath);

    void CreateSubWindow();
    void DestroySubWindow();


public:
    CTilemapEditorLevel();
    ~CTilemapEditorLevel();
};

LRESULT CALLBACK    TilemapEditorProc(HWND, UINT, WPARAM, LPARAM);
