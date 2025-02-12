#pragma once
#include "CObject.h"

enum PlayerState
{
	IDLE,
	MOVE,
	RUN,
};

class CCamera;
class CFlipbookPlayer;

class CPlayer :
    public CObject
{
	PlayerState m_State;
	Dir m_Dir;
	float m_Speed;
	CFlipbookPlayer* m_fbPlayer;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC _dc) override;

private:
	void SetDir(Dir _Dir);
	void SetState(PlayerState _State);
	void UpdateAnimation();

	virtual void TickIdle();
	virtual void TickMove();
	virtual void TickRun();

public:
	CPlayer();
	virtual ~CPlayer();
};

