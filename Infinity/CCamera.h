#pragma once
#include "CComponent.h"

class CObject;

class CCamera
	: public CComponent
{
private:
	Vec2		m_LookAt;			// ī�޶� �ٶ󺸴� ���� ��ǥ
	Vec2		m_LookAtOffset;	// ī�޶� �������� �߰����� Offset
	Vec2		m_Diff;			// ī�޶� �ٶ󺸴� ��ǥ��, ���� �߽ɰ��� ���̰�
	CObject*	m_Target;			// TargetObject

public:
	Vec2 GetViewPos(Vec2 _WorldPos) { return _WorldPos - m_Diff; }
	Vec2 GetWorldPos(Vec2 _ViewPos) { return _ViewPos + m_Diff; }
	void SetTarget(CObject* _Target) { m_Target = _Target; }

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void FinalTick() override;
	virtual void Render(HDC hdc) override;

private:
	void FollowTarget();

public:
	CCamera();
	virtual ~CCamera();
};

