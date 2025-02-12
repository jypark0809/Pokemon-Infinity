#pragma once
class CBase
{
	static UINT g_NextID;
private:
	const UINT	m_ID;	// ���� ID
	wstring		m_Name; // ������Ʈ �̸�

public:
	const wstring& GetName() { return m_Name; }
	void SetName(const wstring& _Name) { m_Name = _Name; }

	UINT GetID() { return m_ID; }

public:
	// �ڱ��ڽ��� �����ؼ� ��ȯ�ϴ� �Լ�
	// virtual CBase* Clone() = 0;

public:
	CBase();
	CBase(const CBase& _Origin);
	virtual ~CBase();
};

