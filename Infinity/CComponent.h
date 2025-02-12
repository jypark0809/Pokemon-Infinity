#pragma once
#include "CBase.h"
#include "CGameObject.h"

class CGameObject;
class CGameObject;

class CComponent :
    public CBase
{
private:
    CGameObject*            m_Owner;
    const ComponentType     m_Type;

public:
    void SetOwner(CGameObject* _Owner) { m_Owner = _Owner; }
    CGameObject* GetOwner() { return m_Owner; }
    ComponentType GetType() { return m_Type; }

    virtual void BeginPlay();
    virtual void Tick();
    virtual void FinalTick() = 0;
    virtual void Render(HDC _hdc);

public:
    CComponent(ComponentType _Type);
    virtual ~CComponent();

    friend class CGameObject;
};

