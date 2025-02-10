#pragma once
class CBase
{
	static UINT g_NextID;
private:
	const UINT	m_ID;	// 고유 ID
	wstring		m_Name; // 오브젝트 이름

public:
	void SetName(const wstring& _Name) { m_Name = _Name; }
	const wstring& GetName() { return m_Name; }

	UINT GetID() { return m_ID; }

public:
	// 자기자신을 복제해서 반환하는 함수
	// virtual CBase* Clone() = 0;

public:
	CBase();
	CBase(const CBase& _Origin);
	virtual ~CBase();
};

