#include "pch.h"
#include "CObject.h"
#include "TaskManager.h"
#include "CComponent.h"
#include "CCamera.h"


CObject::CObject()
	: m_Pos{}
	, m_Scale{}
	, m_Layer(LayerType::DEFAULT)
	, m_Dead(false)
{
}

CObject::~CObject()
{
	Delete_Vec(m_vecComponent);
}

void CObject::BeginPlay()
{
	for (size_t i = 0; i < m_vecComponent.size(); ++i)
	{
		m_vecComponent[i]->BeginPlay();
	}
}

void CObject::FinalTick()
{
	for (size_t i = 0; i < m_vecComponent.size(); ++i)
	{
		m_vecComponent[i]->FinalTick();
	}
}

void CObject::Render(HDC _dc)
{

}

CComponent* CObject::AddComponent(CComponent* _Component)
{
	m_vecComponent.push_back(_Component);
	_Component->SetOwner(this);
	return _Component;
}

CComponent* CObject::GetComponent(ComponentType _Type)
{
	for (size_t i = 0; i < m_vecComponent.size(); ++i)
	{
		if (_Type == m_vecComponent[i]->GetType())
			return m_vecComponent[i];
	}

	return nullptr;
}

Vec2 CObject::GetViewPos()
{
	return GetComponent<CCamera>()->GetViewPos(m_Pos);
}

void CObject::Destroy()
{
	Task task = {};

	task.Type = TASK_TYPE::DELETE_OBJECT;
	task.Param0 = (DWORD_PTR)this;

	TaskManager::GetInstance()->AddTask(task);
}