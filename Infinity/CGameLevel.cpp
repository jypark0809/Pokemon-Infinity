#include "pch.h"
#include "CGameLevel.h"
#include "CPlayerController.h"
#include "CTransform.h"

CGameLevel::CGameLevel()
{
	// Player
	CGameObject* pPlayer = new CGameObject;
	pPlayer->AddComponent<CPlayerController>();
	pPlayer->SetName(L"Player");
	AddObject(pPlayer, LayerType::PLAYER);
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