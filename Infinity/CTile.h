#pragma once
#include "CGameObject.h"
class CTile :
    public CGameObject
{
	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void FinalTick() override;
	virtual void Render(HDC hdc) override;
};

