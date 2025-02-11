#include "pch.h"
#include "CFlipbookPlayer.h"
#include "TimeManager.h"
#include "CTexture.h"
#include "CSprite.h"
#include "CFlipbook.h"
#include "CObject.h"

CFlipbookPlayer::CFlipbookPlayer()
	: CComponent(ComponentType::FLIPBOOK_PLAYER)
	, m_CurFlip(nullptr)
	, m_Loop(false)
{
}

CFlipbookPlayer::~CFlipbookPlayer()
{
	// TODO : Delete Flipbook
}


void CFlipbookPlayer::Tick()
{
}

void CFlipbookPlayer::FinalTick()
{
	if (!m_CurFlip)
		return;

	m_CurFlip->FinalTick();

	if (m_CurFlip->IsCompleted() == true)
	{
		if (m_Loop == true)
			m_CurFlip->Reset();
	}
}

void CFlipbookPlayer::Render(HDC _dc)
{
	CSprite* pSprite	= m_CurFlip->GetSprite();

	CTexture* pAtlas	= pSprite->GetAltasTexture();
	Vec2 vLeftTop		= pSprite->GetLeftTop();
	Vec2 vSize			= pSprite->GetSize();
	Vec2 vOffset		= pSprite->GetOffset();

	Vec2 vPos = GetOwner()->GetViewPos();

	BLENDFUNCTION blend = {};
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;
	blend.SourceConstantAlpha = 255; // 추가 알파값
	blend.AlphaFormat = AC_SRC_ALPHA; // 알파 채널의 알파값을 투명도로 사용

	AlphaBlend(_dc
		, vPos.x - vSize.x / 2.f + vOffset.x
		, vPos.y - vSize.y / 2.f + vOffset.y
		, vSize.x, vSize.y
		, pAtlas->GetDC()
		, vLeftTop.x, vLeftTop.y
		, vSize.x, vSize.y
		, blend);
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