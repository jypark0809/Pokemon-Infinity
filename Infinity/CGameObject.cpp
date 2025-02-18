#include "pch.h"
#include "CGameObject.h"
#include "TaskManager.h"
#include "AssetManager.h"
#include "CComponent.h"
#include "CTransform.h"

CGameObject::CGameObject()
	: m_Parent(nullptr)
	, m_Children{}
	, m_Layer(LayerType::NONE)
{
	AddComponent<CTransform>();
}

CGameObject::~CGameObject()
{
	Delete_Vec(m_Children);
	Delete_Vec(m_vecComponent);
}

void CGameObject::BeginPlay()
{
	for (size_t i = 0; i < m_vecComponent.size(); ++i)
	{
		m_vecComponent[i]->BeginPlay();
	}
}

void CGameObject::Tick()
{
	
}

void CGameObject::FinalTick()
{
	for (size_t i = 0; i < m_vecComponent.size(); ++i)
	{
		m_vecComponent[i]->FinalTick();
	}
}

void CGameObject::Render(HDC _hdc)
{
	for (size_t i = 0; i < m_vecComponent.size(); ++i)
	{
		m_vecComponent[i]->Render(_hdc);
	}
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

int CGameObject::Load(FILE* _File)
{
	// 레이어 
	fread(&m_Layer, sizeof(LayerType), 1, _File);

	// 부모 오브젝트
	wstring parentName;
	LoadWString(_File, parentName);
	SetName(parentName);

	// 자식 오브젝트
	size_t childCount;
	fread(&childCount, sizeof(size_t), 1, _File);
	for (size_t i = 0; i < childCount; ++i) {
		CGameObject* child = new CGameObject;
		if (child->Load(_File) == S_OK) {
			child->SetParent(this); // 부모 설정
			m_Children.push_back(child); // 자식 오브젝트 추가
		}
		else
		{
			delete child;
		}
	}

	// 컴포넌트
	size_t componentCount;
	fread(&componentCount, sizeof(size_t), 1, _File);
	for (size_t i = 0; i < componentCount; ++i)
	{
		ComponentType type;
		fread(&type, sizeof(ComponentType), 1, _File);

		CComponent* component = nullptr;
		switch (type) {
		case ComponentType::TRANSFORM:
			component = new CTransform;
			break;
			// TODO : 다른 컴포넌트 타입 추가
		default:
			break;
		}

		if (component && component->Load(_File) == S_OK) {
			m_vecComponent.push_back(component);
		}
		else
		{
			delete component;
		}
	}

	return S_OK;
}

int CGameObject::Save(FILE* _File)
{
	// 레이어
	fwrite(&m_Layer, sizeof(LayerType), 1, _File);

	// 부모 오브젝트
	wstring parentName = m_Parent ? m_Parent->GetName() : L"";
	SaveWString(_File, parentName);

	// 자식 오브젝트
	size_t childCount = m_Children.size();
	fwrite(&childCount, sizeof(size_t), 1, _File);
	for (size_t i = 0; i < m_Children.size(); ++i)
	{
		m_Children[i]->Save(_File);
	}

	// 컴포넌트
	size_t componentCount = m_vecComponent.size();
	fwrite(&componentCount, sizeof(size_t), 1, _File);
	for (size_t i = 0; i < m_vecComponent.size(); ++i)
	{
		ComponentType type = m_vecComponent[i]->GetType(); // 컴포넌트 타입 가져오기
		fwrite(&type, sizeof(ComponentType), 1, _File); // 타입 저장
		m_vecComponent[i]->Save(_File); // 각 컴포넌트의 Save 호출
	}

	return S_OK;
}
