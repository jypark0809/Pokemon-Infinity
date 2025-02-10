#include "pch.h"
#include "CLevel.h"
#include "CObject.h"

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
	for (UINT i = 0; i < (UINT)LayerType::COUNT; ++i)
	{
		vector<CObject*>& veCObject = m_Objects[i];
		vector<CObject*>::iterator iter = veCObject.begin();

		for (; iter != veCObject.end(); )
		{
			if ((*iter)->IsDead())
			{
				iter = veCObject.erase(iter);
			}
			else
			{
				(*iter)->Render(_dc);
				++iter;
			}
		}
	}
}

void CLevel::AddObject(CObject* _Object, LayerType _LayerType)
{
	m_Objects[(UINT)_LayerType].push_back(_Object);
	_Object->m_Layer = _LayerType;
}

void CLevel::DeleteObject(CObject* _Object)
{
	LayerType layerType = _Object->GetLayerType();
	vector<CObject*>& vecObj = m_Objects[static_cast<UINT>(layerType)];
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
}

void CLevel::OnExit()
{
}
