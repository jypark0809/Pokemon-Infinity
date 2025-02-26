#pragma once
#include "CBase.h"

class CComponent;
class CTransform;

class CGameObject :
    public CBase
{
public:
	CTransform*				transform;
private:
	CGameObject*			m_Parent;		// 부모 오브젝트
	vector<CGameObject*>	m_Children;		// 자식 오브젝트들
	vector<CComponent*>		m_vecComponent;	// 컴포넌트
	LayerType				m_Layer;		// 레이어
	bool					m_Dead;			// 오브젝트가 삭제예정 상태인지 체크하는 용도

public:
	virtual void BeginPlay();
	virtual void Tick();
	virtual void FinalTick();
	virtual void Render(HDC _hdc);

	void SetParent(CGameObject* _Parent);
	CGameObject* GetParent() { return m_Parent; }
	void AddChild(CGameObject* _Child);
	vector<CGameObject*> GetChildren() { return m_Children; }

	void SetLayerType(LayerType _Layer) { m_Layer = _Layer; }
	LayerType GetLayerType() { return m_Layer; }

	CComponent* AddComponent(CComponent* _Component);
	CComponent* GetComponent(ComponentType _Type);
	bool IsDead() { return m_Dead; }
	void Destroy();

	int Load(FILE* _File);
	int Save(FILE* _File);

	template<typename T>
	T*GetComponent()
	{
		T* pComponent = nullptr;
		for (size_t i = 0; i < m_vecComponent.size(); ++i)
		{
			pComponent = dynamic_cast<T*>(m_vecComponent[i]);

			if (nullptr != pComponent)
				return pComponent;
		}

		return nullptr;
	}

	template<typename T>
	T* AddComponent()
	{
		T* pComponent = new T;

		if (pComponent == nullptr)
			throw std::runtime_error("Failed to create component");

		// pComponent->BeginPlay();
		pComponent->SetOwner(this);

		m_vecComponent.push_back(pComponent);

		return pComponent;
	}

public:
	CGameObject();
	virtual ~CGameObject();

	friend class CLevel;
	friend class TaskManager;
};

