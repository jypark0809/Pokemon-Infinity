#pragma once
#include "CLevel.h"


class CTileMapEditorLevel :
    public CLevel
{
    virtual void BeginPlay() override;
    virtual void Tick() override;

    virtual void OnEnter() override;
    virtual void OnExit() override;
public:
    CTileMapEditorLevel();
    ~CTileMapEditorLevel();
};

