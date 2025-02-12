#pragma once
#include "CBase.h"

class CComponent;
// class CCollider;

class CObject
	: public CBase
{
protected:
	Vec2				m_Pos;
	Vec2				m_Scale;
	vector<CComponent*>	m_vecComponent;
	LayerType			m_Layer;
	bool				m_Dead;				// 오브젝트가 삭제예정 상태인지 체크하는 용도

public:
	void SetPos(Vec2 _pos) { m_Pos = _pos; }
	Vec2 GetPos() { return m_Pos; }

	void SetScale(Vec2 _Scale) { m_Scale = _Scale; }
	Vec2 GetScale() { return m_Scale; }

	void SetLayerType(LayerType _Layer) { m_Layer = _Layer; }
	LayerType GetLayerType() { return m_Layer; }

	Vec2 GetViewPos();

	CComponent* AddComponent(CComponent* _Component);
	CComponent* GetComponent(ComponentType _Type);
	// void RemoveComponent(CComponent* _Component);

	bool IsDead() { return m_Dead; }
	void Destroy();

	template<typename T>
	T* GetComponent();

	template<typename T>
	T* AddComponent();

public:
	virtual void BeginPlay();
	virtual void Tick() = 0;
	virtual void FinalTick();
	virtual void Render(HDC hdc);

public:
	CObject();
	virtual ~CObject();

	friend class CLevel;
	friend class TaskManager;
};

template<typename T>
T* CObject::GetComponent()
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
T* CObject::AddComponent()
{
	T* pComponent = new T;
	// pComponent->Init();
	pComponent->SetOwner(this);

	if (pComponent == nullptr)
		throw std::runtime_error("Failed to create component");

	m_vecComponent.push_back(pComponent);

	return pComponent;
}
