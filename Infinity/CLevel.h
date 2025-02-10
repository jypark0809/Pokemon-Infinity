#pragma once

#include "CBase.h"

class CObject;

class CLevel
	: public CBase
{
private:
	vector<CObject*>	m_Objects[(UINT)LayerType::COUNT];

public:
	virtual void BeginPlay();			// ������ ����, ������ �����ϰ� �ִ� ������Ʈ���� �ʱ�ȭ�۾��� �����ϴ� �ܰ�
	virtual void Tick();				// �������Ӹ��� ������Ʈ�� �� ��
	virtual void FinalTick();			// ������Ʈ�� ������ ������, ������ �۾�
	virtual void Render(HDC _dc);		// ������Ʈ�� ȭ�鿡 �׸�

	virtual void OnEnter();			// ������ ��ȯ�Ǹ鼭, �ش� ������ ������ �� ȣ�� ��
	virtual void OnExit();			// ������ ��ȯ�Ǹ鼭, �ش� ������ ���� ������ ȣ�� ��

	const vector<CObject*>& GetObjects(LayerType _Layer) { return m_Objects[(UINT)_Layer]; }
	void AddObject(CObject* _Object, LayerType _LayerType);
	void DeleteObject(CObject* _Object);
	void RemoveObjects(int _LayerIdx);
	virtual void Destroy();


public:
	CLevel();
	~CLevel();
};

