#include "pch.h"
#include "CCamera.h"
#include "CObject.h"

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
	Vec2 vResolution = CEngine::GetInstance()->GetResolution();
	m_LookAt = (vResolution / 2.f);
}

void CCamera::Tick()
{
}

void CCamera::FinalTick()
{
	FollowTarget();

	// �ػ� �߽ɰ�, ī�޶� LookAt ���� ���̰��� ���
	Vec2 vResolution = CEngine::GetInstance()->GetResolution();
	m_Diff = (m_LookAt + m_LookAtOffset) - (vResolution / 2.f);
}

void CCamera::Render(HDC hdc)
{
	// POSTPROC
}

void CCamera::FollowTarget()
{
	if (nullptr == m_Target)
		return;

	m_LookAt = m_Target->GetPos();
}