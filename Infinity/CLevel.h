#pragma once

#include "CBase.h"

class CGameObject;
class CCamera;

class CLevel
	: public CBase
{
private:
	CCamera*				m_Camera;
	vector<CGameObject*>	m_Objects[(UINT)LayerType::COUNT];

public:
	virtual void BeginPlay();		// ������ ����, ������ �����ϰ� �ִ� ������Ʈ���� �ʱ�ȭ�۾��� �����ϴ� �ܰ�
	virtual void Tick();			// �������Ӹ��� ������Ʈ�� �� ��
	virtual void FinalTick();		// ������Ʈ�� ������ ������, ������ �۾�
	virtual void Render(HDC _dc);	// ������Ʈ�� ȭ�鿡 �׸�

	virtual void OnEnter();			// ������ ��ȯ�Ǹ鼭, �ش� ������ ������ �� ȣ�� ��
	virtual void OnExit();			// ������ ��ȯ�Ǹ鼭, �ش� ������ ���� ������ ȣ�� ��

	CCamera* GetCamera() { return m_Camera; }
	const vector<CGameObject*>& GetObjects(LayerType _Layer) { return m_Objects[(UINT)_Layer]; }
	void AddObject(CGameObject* _Object, LayerType _LayerType);
	void DeleteObject(CGameObject* _Object);
	void RemoveObjects(int _LayerIdx);
	virtual void Destroy();

public:
	CLevel();
	~CLevel();
};

