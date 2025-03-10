#pragma once
#include "CBase.h"

class CFSM;

class CState :
    public CBase
{
private:
    CFSM* m_Owner;

protected:
    CFSM* GetFSM() { return m_Owner; }

public:
    virtual void Enter() = 0;
    virtual void FinalTick() = 0;
    virtual void Exit() = 0;

public:
    CState();
    virtual ~CState();

    friend class CFSM;
};

