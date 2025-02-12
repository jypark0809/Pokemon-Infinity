#include "pch.h"
#include "CTransform.h"

CTransform::CTransform()
	: CComponent(ComponentType::TRANSFORM)
	, m_ParentTransform(nullptr)
	, m_ChildTranforms{}
	, m_Position(Vec2(0.f, 0.f))
	, m_Rotation(Vec2(0.f, 0.f))
	, m_Scale(Vec2(1.f, 1.f))
{
}

CTransform::~CTransform()
{
}

void CTransform::BeginPlay()
{
}

void CTransform::Tick()
{
}

void CTransform::FinalTick()
{
}

void CTransform::Render(HDC _hdc)
{
}
