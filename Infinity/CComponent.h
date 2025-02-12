#pragma once
#include "CBase.h"
#include "CObject.h"

class CObject;
class CGameObject;

class CComponent :
    public CBase
{
private:
    CObject*            m_Owner;
    CGameObject*        m_gOwner;
    const ComponentType m_Type;

public:
    void SetOwner(CObject* _Owner) { m_Owner = _Owner; }
    void SetOwner(CGameObject* _Owner) { m_gOwner = _Owner; }
    CObject* GetOwner() { return m_Owner; }
    ComponentType GetType() { return m_Type; }

    virtual void BeginPlay();
    virtual void Tick();
    virtual void FinalTick() = 0;
    virtual void Render(HDC _hdc);

public:
    CComponent(ComponentType _Type);
    virtual ~CComponent();

    friend class CObject;
};

