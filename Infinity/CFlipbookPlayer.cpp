#include "pch.h"
#include "CFlipbookPlayer.h"
#include "TimeManager.h"
#include "CTransform.h"
#include "CSpriteRenderer.h"
#include "CTexture.h"
#include "CSprite.h"
#include "CFlipbook.h"
#include "CGameObject.h"

CFlipbookPlayer::CFlipbookPlayer()
	: CComponent(ComponentType::FLIPBOOKPLAYER)
	, m_CurFlip(nullptr)
	, m_Loop(false)
{
	
}

CFlipbookPlayer::~CFlipbookPlayer()
{
	// TODO : Delete Flipbook
}

void CFlipbookPlayer::BeginPlay()
{
}

void CFlipbookPlayer::Tick()
{
}

void CFlipbookPlayer::FinalTick()
{
	if (!m_CurFlip)
		return;

	// SpriteRenderer
	CSprite* pSprite = m_CurFlip->GetSprite();
	m_spRenderer->SetSprite(pSprite);

	// Flipbook
	m_CurFlip->FinalTick();
	if (m_CurFlip->IsCompleted() == true)
	{
		if (m_Loop == true)
			m_CurFlip->Reset();
	}
}

void CFlipbookPlayer::Render(HDC _hdc)
{
}

void CFlipbookPlayer::Play(int _Idx, bool _Loop)
{
	m_CurFlip = m_Flipbooks[_Idx];
	m_Loop = _Loop;
}

void CFlipbookPlayer::AddFlipbook(int _Idx, CFlipbook* _Flipbook)
{
	if (m_Flipbooks.size() < (_Idx + 1))
		m_Flipbooks.resize(_Idx + 1);

	m_Flipbooks[_Idx] = _Flipbook;
}