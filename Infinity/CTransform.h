#pragma once
#include "CComponent.h"

class CCamera;

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
    void Translate(Vec2 _Translation)
    {
        m_Position.x += _Translation.x;
        m_Position.y += _Translation.y;
    }

    Vec2 GetScale() { return m_Scale; }
    void SetScale(Vec2 _Scale) { m_Scale = _Scale; }

    void SetParent(CTransform* _Parent);
    void AddChild(CTransform* _Child);

    Vec2 GetViewPos();

    virtual int Save(FILE* _File) { return S_OK; }
    virtual int Load(FILE* _File) { return S_OK; }

public:
    CTransform();
    ~CTransform();

    friend class CGameObject;
};

