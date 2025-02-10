#include "pch.h"
#include "CGameLevel.h"
#include "CPlayer.h"

Vec2 vResolution = Vec2(512, 384);

CGameLevel::CGameLevel()
{
	// Player
	CObject* pNewObj = new CPlayer;
	pNewObj->SetName(L"Player");
	pNewObj->SetPos(Vec2(vResolution.x / 2, vResolution.y / 2));
	AddObject(pNewObj, LayerType::PLAYER);
}

CGameLevel::~CGameLevel()
{
}

void CGameLevel::BeginPlay()
{
	CLevel::BeginPlay();
}

void CGameLevel::Tick()
{
	CLevel::Tick();
}

void CGameLevel::OnEnter()
{
	CLevel::OnEnter();
}

void CGameLevel::OnExit()
{
	CLevel::OnExit();
}