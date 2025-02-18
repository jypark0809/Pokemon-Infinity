#pragma once
#include "CComponent.h"
class CScript :
    public CComponent
{
public:
    virtual void BeginPlay() override;
    virtual void Tick() override;
    virtual void FinalTick() override;
    virtual void Render(HDC _hdc) override;

    // Collision
    // virtual void OnCollisionEnter(Collider* collider, Collider* other);
    // virtual void OnCollisionStay(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider);
    // virtual void OnCollisionExit(Collider* collider, Collider* other);

    virtual int Save(FILE* _File) { return S_OK; }
    virtual int Load(FILE* _File) { return S_OK; }

public:
    CScript();
    ~CScript();
};

