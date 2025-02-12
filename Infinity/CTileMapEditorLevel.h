#pragma once
#include "CLevel.h"

class CGrid;
class CTilemap;

class CTilemapEditorLevel :
    public CLevel
{
private:
    HWND                m_SubWindow;
    CGrid*              m_Grid;
    vector<CTilemap*>   m_vecTilemap;

public:
    virtual void BeginPlay() override;
    virtual void Tick() override;
    virtual void FinalTick() override;
    virtual void Render(HDC _hdc) override;

    virtual void OnEnter() override;
    virtual void OnExit() override;

    bool Cango(Vec2Int _CellPos);

private:
    void CreateSubWindow();
    void DestroySubWindow();


public:
    CTilemapEditorLevel();
    ~CTilemapEditorLevel();
};

