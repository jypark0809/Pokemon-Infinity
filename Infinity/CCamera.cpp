#include "pch.h"
#include "CCamera.h"
#include "CGameObject.h"
#include "CTransform.h"

CCamera::CCamera()
	: CComponent(ComponentType::CAMERA)
	, m_Target(nullptr)
	, m_Speed(100)
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

#include "KeyManager.h"
#include "TimeManager.h"
void CCamera::FinalTick()
{
	// TEMP
	if (KeyManager::GetInstance()->GetButton(Key::LEFT))
		m_Target->GetComponent<CTransform>()->Translate(Vec2(-m_Speed * DT, 0));
	if (KeyManager::GetInstance()->GetButton(Key::UP))
		m_Target->GetComponent<CTransform>()->Translate(Vec2(0, -m_Speed * DT));
	if (KeyManager::GetInstance()->GetButton(Key::DOWN))
		m_Target->GetComponent<CTransform>()->Translate(Vec2(0, m_Speed * DT));
	if (KeyManager::GetInstance()->GetButton(Key::RIGHT))
		m_Target->GetComponent<CTransform>()->Translate(Vec2(m_Speed * DT, 0));

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