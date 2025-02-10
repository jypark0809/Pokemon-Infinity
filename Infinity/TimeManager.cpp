#include "pch.h"
#include "TimeManager.h"

TimeManager::TimeManager()
	: m_PrevCount{}
	, m_CurCount{}
	, m_Frequency{}
	, m_DeltaTime(0.f)
	, m_CallCount(0)
	, m_AccTime(0.f)
{

}

TimeManager::~TimeManager()
{

}


void TimeManager::Init()
{
	// �ʴ� ī���� ��
	QueryPerformanceFrequency(&m_Frequency);

	// ���� ī���� ��
	QueryPerformanceCounter(&m_PrevCount);
	QueryPerformanceCounter(&m_CurCount);
}

void TimeManager::Tick()
{
	// ���� ī���� ��
	QueryPerformanceCounter(&m_CurCount);

	// ���� ī���ð� ����ī������ ���̸� �ʴ� ī���� ���� ����� ����� �ð����� ���Ѵ�.
	m_DeltaTime = (float)(m_CurCount.QuadPart - m_PrevCount.QuadPart) / (float)m_Frequency.QuadPart;

	// ���� ī������ ���� ī�������� �����صд�.(������ �����ӿ��� ����ϱ� ���ؼ�)
	m_PrevCount = m_CurCount;

	// FPS üũ
	++m_CallCount;
	m_AccTime += m_DeltaTime;
	if (1.f < m_AccTime)
	{
		wchar_t buff[255] = {};
		swprintf(buff, 255, L"FPS : %d", m_CallCount);
		SetWindowText(CEngine::GetInstance()->GetMainWnd(), buff);

		m_CallCount = 0;
		m_AccTime -= 1.f;
	}
}
