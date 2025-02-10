#include "pch.h"
#include "CPlayer.h"
#include "KeyManager.h"
#include "TimeManager.h"
#include "AssetManager.h"
#include "CCamera.h"
#include "CFlipbookPlayer.h"
#include "CSprite.h"
#include "CFlipbook.h"


CPlayer::CPlayer()
	: m_fbPlayer(nullptr)
	, m_State(PlayerState::IDLE)
	, m_Dir(Dir::DOWN)
	, m_Speed(5.f)
{
	// Camera
	m_Camera = AddComponent<CCamera>();
	m_Camera->SetTarget(this);

	m_fbPlayer = AddComponent<CFlipbookPlayer>();
	CTexture* pAtlasTex = AssetManager::GetInstance()->LoadTexture(L"NPC_Red", L"Texture\\Characters\\NPC_Red.png");

	m_fbPlayer->AddFlipbook(0, AssetManager::GetInstance()->LoadFlipbook(L"Red_Move_Down", L"Flipbook\\Red_Move_Down.flip"));
	//m_fbPlayer->AddFlipbook(1, AssetManager::GetInstance()->LoadFlipbook(L"IDLE_LEFT", L"Flipbook\\IDLE_LEFT.flip"));
	//m_fbPlayer->AddFlipbook(2, AssetManager::GetInstance()->LoadFlipbook(L"IDLE_RIGHT", L"Flipbook\\IDLE_RIGHT.flip"));
	//m_fbPlayer->AddFlipbook(3, AssetManager::GetInstance()->LoadFlipbook(L"IDLE_UP", L"Flipbook\\IDLE_UP.flip"));
	//m_fbPlayer->AddFlipbook(4, AssetManager::GetInstance()->LoadFlipbook(L"MOVE_DOWN", L"Flipbook\\MOVE_DOWN.flip"));
	//m_fbPlayer->AddFlipbook(5, AssetManager::GetInstance()->LoadFlipbook(L"MOVE_LEFT", L"Flipbook\\MOVE_LEFT.flip"));
	//m_fbPlayer->AddFlipbook(6, AssetManager::GetInstance()->LoadFlipbook(L"MOVE_RIGHT", L"Flipbook\\MOVE_RIGHT.flip"));
	//m_fbPlayer->AddFlipbook(7, AssetManager::GetInstance()->LoadFlipbook(L"MOVE_UP", L"Flipbook\\MOVE_UP.flip"));

	m_fbPlayer->Play(0, true);
}

CPlayer::~CPlayer()
{

}
void CPlayer::BeginPlay()
{
	
}

void CPlayer::Tick()
{
	/*switch (m_State)
	{
	case PlayerState::IDLE:
		TickIdle();
		break;
	case PlayerState::MOVE:
		TickMove();
		break;
	case PlayerState::RUN:
		TickRun();
		break;
	}*/
}

void CPlayer::Render(HDC _dc)
{
	m_fbPlayer->Render(_dc);
}

void CPlayer::TickIdle()
{
	
}

void CPlayer::TickMove()
{
	
}

void CPlayer::TickRun()
{
}

void CPlayer::SetDir(Dir _Dir)
{
	m_Dir = _Dir;
	UpdateAnimation();
}

void CPlayer::SetState(PlayerState _State)
{
	if (m_State == _State)
		return;

	m_State = _State;
	UpdateAnimation();
}

void CPlayer::UpdateAnimation()
{
	switch (m_State)
	{
	case PlayerState::IDLE:

		break;
	case PlayerState::MOVE:

		break;
	case PlayerState::RUN:

		break;
	}
}
