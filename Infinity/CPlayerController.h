#pragma once
#include "CScript.h"

enum PlayerState
{
	IDLE,
	MOVE,
	RUN,
};

class CFlipbookPlayer;

class CPlayerController :
    public CScript
{
private:
	PlayerState m_State;
	Dir m_Dir;
	float m_Speed;
	CFlipbookPlayer* m_fbPlayer;

private:
	void SetDir(Dir _Dir);
	void SetState(PlayerState _State);
	void UpdateAnimation();

	virtual void TickIdle();
	virtual void TickMove();
	virtual void TickRun();

public:
	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void FinalTick() override;
	virtual void Render(HDC _hdc) override;

public:
	CPlayerController();
	virtual ~CPlayerController();
};

