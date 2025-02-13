#include "pch.h"
#include "CSpriteRenderer.h"
#include "CTransform.h"
#include "CSprite.h"

CSpriteRenderer::CSpriteRenderer()
	: CRenderer(ComponentType::SPRITERENDERER)
	, m_Sprite(nullptr)
{
}

CSpriteRenderer::~CSpriteRenderer()
{
}

void CSpriteRenderer::BeginPlay()
{
}

void CSpriteRenderer::Tick()
{
}

void CSpriteRenderer::FinalTick()
{
}

void CSpriteRenderer::Render(HDC _hdc)
{
	CTransform* transform = GetOwner()->GetComponent<CTransform>();
	m_Sprite->Render(_hdc, transform->GetPosition() - (m_Sprite->GetSize() / 2));
}