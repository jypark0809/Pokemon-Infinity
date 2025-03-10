#include "pch.h"
#include "CPlayerController.h"
#include "KeyManager.h"
#include "TimeManager.h"
#include "AssetManager.h"
#include "CCamera.h"
#include "CTransform.h"
#include "CFlipbookPlayer.h"
#include "CSpriteRenderer.h"
#include "CSprite.h"
#include "CFlipbook.h"

CPlayerController::CPlayerController()
	: m_fbPlayer(nullptr)
	, m_spRenderer(nullptr)
	, m_State(PlayerState::IDLE)
	, m_Dir(Dir::DOWN)
	, m_Speed(50.f)
{
	
}

CPlayerController::~CPlayerController()
{

}
void CPlayerController::BeginPlay()
{
	Vec2 vResolution = CEngine::GetInstance()->GetResolution();
	GetOwner()->GetComponent<CTransform>()->SetPosition(Vec2(vResolution.x / 2, vResolution.y / 2));
	
	m_fbPlayer = GetOwner()->GetComponent<CFlipbookPlayer>();
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

void CPlayerController::Tick()
{
	
}

void CPlayerController::FinalTick()
{
	if (KeyManager::GetInstance()->GetButton(Key::LEFT))
		GetOwner()->transform->Translate(Vec2(-m_Speed * DT, 0));
	if (KeyManager::GetInstance()->GetButton(Key::RIGHT))
		GetOwner()->transform->Translate(Vec2(m_Speed * DT, 0));
}

void CPlayerController::Render(HDC _dc)
{
}

void CPlayerController::TickIdle()
{
	
}

void CPlayerController::TickMove()
{
	
}

void CPlayerController::TickRun()
{
}

void CPlayerController::SetDir(Dir _Dir)
{
	m_Dir = _Dir;
	UpdateAnimation();
}

void CPlayerController::SetState(PlayerState _State)
{
	if (m_State == _State)
		return;

	m_State = _State;
	UpdateAnimation();
}

void CPlayerController::UpdateAnimation()
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
