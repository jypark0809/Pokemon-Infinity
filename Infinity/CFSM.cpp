#include "pch.h"
#include "CFSM.h"
#include "CState.h"

CFSM::CFSM()
	: CComponent(ComponentType::FSM)
	, m_CurState(nullptr)
{
}

CFSM::~CFSM()
{
    Delete_Vec(m_vecState);
}

void CFSM::BeginPlay()
{
}

void CFSM::Tick()
{
}

void CFSM::FinalTick()
{
    if (nullptr == m_CurState)
        return;

    m_CurState->FinalTick();
}

void CFSM::Render(HDC _hdc)
{
}

void CFSM::AddState(int _Idx, CState* _State)
{
    if (m_vecState.size() <= _Idx)
    {
        m_vecState.resize(_Idx + 1);
    }

    m_vecState[_Idx] = _State;
    _State->m_Owner = this;
}

void CFSM::ChangeState(int _Idx)
{
    if (nullptr != m_CurState)
        m_CurState->Exit();

    m_CurState = m_vecState[_Idx];

    if (nullptr != m_CurState)
        m_CurState->Enter();
}

