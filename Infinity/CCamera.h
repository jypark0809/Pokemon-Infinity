#pragma once
#include "CComponent.h"

class CGameObject;

class CCamera
	: public CComponent
{
private:
	Vec2			m_Resolution;
	CGameObject*	m_Target;			// TargetObject
	Vec2			m_LookAt;			// ī�޶� �ٶ󺸴� ���� ��ǥ
	Vec2			m_LookAtOffset;		// ī�޶� �������� �߰����� Offset
	Vec2			m_Diff;				// ī�޶� �ٶ󺸴� ��ǥ��, ���� �߽ɰ��� ���̰�

public:
	Vec2 GetViewPos(Vec2 _WorldPos) { return _WorldPos - m_Diff; }
	Vec2 GetWorldPos(Vec2 _ViewPos) { return _ViewPos + m_Diff; }
	void SetTarget(CGameObject* _Target) { m_Target = _Target; }

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void FinalTick() override;
	virtual void Render(HDC hdc) override;

	virtual int Save(FILE* _File) { return S_OK; }
	virtual int Load(FILE* _File) { return S_OK; }

public:
	CCamera();
	virtual ~CCamera();
};

