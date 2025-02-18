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
	/*CGameObject* pParent = GetOwner()->GetParent();
	if (pParent)
	{
		CTransform* pParentTransform = pParent->GetComponent<CTransform>();
		m_ParentTransform = pParentTransform;
		pParentTransform->AddChild(this);
	}*/
		
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

Vec2 CTransform::GetViewPos()
{
	// TODO : Camera
	return m_Position;
}