#pragma once
#include "CComponent.h"
class CTransform :
    public CComponent
{
private:
    CTransform*             m_ParentTransform;
    vector<CTransform*>     m_ChildTranforms;
    Vec2                    m_Position;
    Vec2                    m_Rotation;
    Vec2                    m_Scale;

public:
    virtual void BeginPlay() override;
    virtual void Tick() override;
    virtual void FinalTick() override;
    virtual void Render(HDC _hdc) override;

    Vec2 GetPosition() { return m_Position; }
    void SetPosition(Vec2 _position) { m_Position = _position; }

    Vec2 GetScale() { return m_Scale; }
    void SetScale(Vec2 _Scale) { m_Scale = _Scale; }

    void AddChild(CTransform* _Child) { m_ChildTranforms.push_back(_Child); }

    Vec2 GetViewPos();

    virtual int Save(FILE* _File) { return S_OK; }
    virtual int Load(FILE* _File) { return S_OK; }

public:
    CTransform();
    ~CTransform();

    friend class CGameObject;
};

