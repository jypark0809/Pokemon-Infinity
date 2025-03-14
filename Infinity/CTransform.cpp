#include "pch.h"
#include "CTransform.h"
#include "LevelManager.h"
#include "CLevel.h"
#include "CCamera.h"

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

void CTransform::SetParent(CTransform* _Parent)
{
	m_ParentTransform = _Parent;
	_Parent->m_ChildTranforms.push_back(this);
}

void CTransform::AddChild(CTransform* _Child)
{
	m_ChildTranforms.push_back(_Child);
	_Child->SetParent(this);
}

Vec2 CTransform::GetViewPos()
{
	CLevel* curLevel = LevelManager::GetInstance()->GetCurrentLevel();
	CCamera* pCamera = curLevel->GetCamera();
	return pCamera->GetViewPos(m_Position);
}