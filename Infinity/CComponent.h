#pragma once
#include "CBase.h"

class CObject;

class CComponent :
    public CBase
{
private:
    CObject*            m_Owner;
    const ComponentType m_Type;

public:
    void SetOwner(CObject* _Owner) { m_Owner = _Owner; }
    CObject* GetOwner() { return m_Owner; }
    ComponentType GetType() { return m_Type; }

    virtual void BeginPlay();
    virtual void FinalTick() = 0;
    virtual void Render(HDC _hdc);

public:
    CComponent(ComponentType _Type);
    virtual ~CComponent();

    friend class CObject;
};

