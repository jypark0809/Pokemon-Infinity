#pragma once
#include "CComponent.h"

class CState;

class CFSM :
    public CComponent
{
private:
    vector<CState*> m_vecState;
    CState* m_CurState;

public:
    void AddState(int _Idx, CState* _State);
    void ChangeState(int _Idx);

public:
    virtual void BeginPlay() override;
    virtual void Tick()override;
    virtual void FinalTick() override;
    virtual void Render(HDC _hdc) override;


public:
    CFSM();
    ~CFSM();

};

