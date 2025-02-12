#pragma once
#include "CLevel.h"

class CMap;

class CTilemapEditorLevel :
    public CLevel
{
private:
    CMap* m_Map;

public:
    virtual void BeginPlay() override;
    virtual void Tick() override;
    virtual void FinalTick() override;
    virtual void Render(HDC _hdc) override;

    virtual void OnEnter() override;
    virtual void OnExit() override;
public:
    CTilemapEditorLevel();
    ~CTilemapEditorLevel();
};

