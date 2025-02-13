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
    Vec2 GetPosition() { return m_Position; }
    void SetPosition(Vec2 _position) { m_Position = _position; }

    Vec2 GetScale() { return m_Scale; }
    void SetScale(Vec2 _Scale) { m_Scale = _Scale; }

    Vec2 GetViewPos();

    virtual void BeginPlay() override;
    virtual void Tick() override;
    virtual void FinalTick() override;
    virtual void Render(HDC _hdc) override;

public:
    CTransform();
    ~CTransform();
};

