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
	// 초당 카운팅 수
	QueryPerformanceFrequency(&m_Frequency);

	// 현재 카운팅 값
	QueryPerformanceCounter(&m_PrevCount);
	QueryPerformanceCounter(&m_CurCount);
}

void TimeManager::Tick()
{
	// 현재 카운팅 값
	QueryPerformanceCounter(&m_CurCount);

	// 이전 카운팅과 현재카운팅의 차이를 초당 카운팅 수로 나누어서 진행된 시간값을 구한다.
	m_DeltaTime = (float)(m_CurCount.QuadPart - m_PrevCount.QuadPart) / (float)m_Frequency.QuadPart;

	// 이전 카운팅을 현재 카운팅으로 갱신해둔다.(다음번 프레임에서 사용하기 위해서)
	m_PrevCount = m_CurCount;

	// FPS 체크
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
