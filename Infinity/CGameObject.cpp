#include "pch.h"
#include "CGameObject.h"
#include "TaskManager.h"
#include "CComponent.h"

CGameObject::CGameObject()
{

}

CGameObject::~CGameObject()
{
}

void CGameObject::BeginPlay()
{
}

void CGameObject::Tick()
{
}

void CGameObject::FinalTick()
{
}

void CGameObject::Render(HDC hdc)
{
}

CComponent* CGameObject::AddComponent(CComponent* _Component)
{
	m_vecComponent.push_back(_Component);
	_Component->SetOwner(this);
	return _Component;
}

CComponent* CGameObject::GetComponent(ComponentType _Type)
{
	for (size_t i = 0; i < m_vecComponent.size(); ++i)
	{
		if (_Type == m_vecComponent[i]->GetType())
			return m_vecComponent[i];
	}

	return nullptr;
}

void CGameObject::Destroy()
{
	Task task = {};

	task.Type = TASK_TYPE::DELETE_OBJECT;
	task.Param0 = (DWORD_PTR)this;

	TaskManager::GetInstance()->AddTask(task);
}
