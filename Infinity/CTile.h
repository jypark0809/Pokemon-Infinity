#pragma once
#include "CObject.h"
class CTile :
    public CObject
{
	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void FinalTick() override;
	virtual void Render(HDC hdc) override;
};

