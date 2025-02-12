#pragma once

#include "CBase.h"

class CGameObject;

class CLevel
	: public CBase
{
private:
	vector<CGameObject*>	m_Objects[(UINT)LayerType::COUNT];

public:
	virtual void BeginPlay();			// 레벨이 시작, 레벨이 소유하고 있던 오브젝트들이 초기화작업을 수행하는 단계
	virtual void Tick();				// 매프레임마다 오브젝트가 할 일
	virtual void FinalTick();			// 오브젝트가 할일이 끝나고, 마무리 작업
	virtual void Render(HDC _dc);		// 오브젝트를 화면에 그림

	virtual void OnEnter();			// 레벨이 전환되면서, 해당 레벨로 진입할 때 호출 됨
	virtual void OnExit();			// 레벨이 전환되면서, 해당 레벨을 빠져 나갈때 호출 됨

	const vector<CGameObject*>& GetObjects(LayerType _Layer) { return m_Objects[(UINT)_Layer]; }
	void AddObject(CGameObject* _Object, LayerType _LayerType);
	void DeleteObject(CGameObject* _Object);
	void RemoveObjects(int _LayerIdx);
	virtual void Destroy();


public:
	CLevel();
	~CLevel();
};

