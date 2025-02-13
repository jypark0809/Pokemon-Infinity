#include "pch.h"
#include "CCamera.h"
#include "CGameObject.h"
#include "CTransform.h"

CCamera::CCamera()
	: CComponent(ComponentType::CAMERA)
	, m_Target(nullptr)
{
}

CCamera::~CCamera()
{
}

void CCamera::BeginPlay()
{
	m_Resolution = CEngine::GetInstance()->GetResolution();
	m_LookAt = (m_Resolution / 2.f);
}

void CCamera::Tick()
{
}

void CCamera::FinalTick()
{
	if (m_Target)
		m_LookAt = m_Target->GetComponent<CTransform>()->GetPosition();
	else
		m_LookAt = GetOwner()->GetComponent<CTransform>()->GetPosition();

	m_Diff = (m_LookAt + m_LookAtOffset) - (m_Resolution / 2.f);
}

void CCamera::Render(HDC hdc)
{
	// POSTPROC
}