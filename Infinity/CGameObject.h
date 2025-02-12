#pragma once
#include "CBase.h"

class CComponent;

class CGameObject :
    public CBase
{
private:
	vector<CComponent*> m_vecComponent;
	LayerType			m_Layer;
	bool				m_Dead;			// 오브젝트가 삭제예정 상태인지 체크하는 용도

public:
	void SetLayerType(LayerType _Layer) { m_Layer = _Layer; }
	LayerType GetLayerType() { return m_Layer; }

	CComponent* AddComponent(CComponent* _Component);
	CComponent* GetComponent(ComponentType _Type);
	bool IsDead() { return m_Dead; }
	void Destroy();

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
		pComponent->BeginPlay();
		pComponent->SetOwner(this);

		if (pComponent == nullptr)
			throw std::runtime_error("Failed to create component");

		m_vecComponent.push_back(pComponent);

		return pComponent;
	}

	virtual void BeginPlay();
	virtual void Tick();
	virtual void FinalTick();
	virtual void Render(HDC hdc);

public:
	CGameObject();
	virtual ~CGameObject();

	friend class CLevel;
	friend class TaskManager;
};

