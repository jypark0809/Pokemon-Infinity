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
	CCamera* m_Camera;

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

	// TEMP
	void CreateFlipbook(const wstring& _FlipbookName, CTexture* _Atlas, Vec2 _LeftTop, Vec2 _Size, int _FrmCount);
	void LoadFlipbook(const wstring& _FlipbookName, CTexture* _Atlas, Vec2 _LeftTop, Vec2 _Size, int _FrmCount);

public:
	CPlayer();
	virtual ~CPlayer();
};

