#pragma once
#include "CLevel.h"

class CGrid;
class CTilemap;

class CGameLevel :
    public CLevel
{
private:
    CGrid* m_MapGrid;

public:
    virtual void BeginPlay() override;
    virtual void Tick() override;
    virtual void OnEnter() override;
    virtual void OnExit() override;

private:
    void LoadMap();
    CTilemap* AddTilemap(const wstring& _ObjectName);

public:
    CGameLevel();
    ~CGameLevel();
};

