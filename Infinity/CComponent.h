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
    virtual void BeginPlay();
    virtual void Tick();
    virtual void FinalTick();
    virtual void Render(HDC _hdc);

    void SetOwner(CGameObject* _Owner) { m_Owner = _Owner; }
    CGameObject* GetOwner() { return m_Owner; }
    ComponentType GetType() { return m_Type; }

    virtual int Save(FILE* _File) = 0;
    virtual int Load(FILE* _File) = 0;

public:
    CComponent(ComponentType _Type);
    virtual ~CComponent();

    friend class CGameObject;
};

