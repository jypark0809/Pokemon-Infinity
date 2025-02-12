#include "pch.h"
#include "CLevel.h"
#include "CGameObject.h"

CLevel::CLevel()
{
}

CLevel::~CLevel()
{
	for (UINT i = 0; i < (UINT)LayerType::COUNT; ++i)
	{
		Delete_Vec(m_Objects[i]);
	}
}

void CLevel::BeginPlay()
{
	for (UINT i = 0; i < (UINT)LayerType::COUNT; ++i)
	{
		for (size_t j = 0; j < m_Objects[i].size(); ++j)
		{
			m_Objects[i][j]->BeginPlay();
		}
	}
}

void CLevel::Tick()
{
	for (UINT i = 0; i < (UINT)LayerType::COUNT; ++i)
	{
		for (size_t j = 0; j < m_Objects[i].size(); ++j)
		{
			m_Objects[i][j]->Tick();
		}
	}
}

void CLevel::FinalTick()
{
	for (UINT i = 0; i < (UINT)LayerType::COUNT; ++i)
	{
		for (size_t j = 0; j < m_Objects[i].size(); ++j)
		{
			m_Objects[i][j]->FinalTick();
		}
	}
}

void CLevel::Render(HDC _dc)
{
	// TODO : Order in Layer 순서에 맞게 랜더링 하도록 수정

	for (UINT i = 0; i < (UINT)LayerType::COUNT; ++i)
	{
		vector<CGameObject*>& veCGameObject = m_Objects[i];
		vector<CGameObject*>::iterator iter = veCGameObject.begin();

		for (; iter != veCGameObject.end(); )
		{
			if ((*iter)->IsDead())
			{
				iter = veCGameObject.erase(iter);
			}
			else
			{
				(*iter)->Render(_dc);
				++iter;
			}
		}
	}
}

void CLevel::AddObject(CGameObject* _Object, LayerType _LayerType)
{
	m_Objects[(UINT)_LayerType].push_back(_Object);
	_Object->m_Layer = _LayerType;
}

void CLevel::DeleteObject(CGameObject* _Object)
{
	LayerType layerType = _Object->GetLayerType();
	vector<CGameObject*>& vecObj = m_Objects[static_cast<UINT>(layerType)];
	for (size_t i = 0; i < vecObj.size(); ++i)
	{
		if (vecObj[i] == _Object)
		{
			_Object->Destroy();
		}
	}
}

// 특정 Layer에 속하는 오브젝트들 제거
void CLevel::RemoveObjects(int _LayerIdx)
{
	Delete_Vec(m_Objects[_LayerIdx]);
}

void CLevel::Destroy()
{
	for (int i = 0; i < (int)LayerType::COUNT; ++i)
		RemoveObjects(i);
}

void CLevel::OnEnter()
{
	BeginPlay();
}

void CLevel::OnExit()
{
}
