#pragma once
class TimeManager
{
	DECLARE_SINGLE(TimeManager);

private:
	LARGE_INTEGER	m_PrevCount;	// ���������ӿ� üũ�� ��
	LARGE_INTEGER	m_CurCount;		// �̹� �����ӿ� üũ�� ��
	LARGE_INTEGER	m_Frequency;	// 1�ʴ� ī���� ��

	float			m_DeltaTime;	// 1 ������ ���� �ð�
	int				m_CallCount;	// 1�ʵ��� ȣ��Ǵ� Ƚ��(FPS)
	float			m_AccTime;		// �����ð� üũ�뵵

public:
	void Init();
	void Tick();

	float GetDeltaTime() { return m_DeltaTime; }
};

