#pragma once
class TimeManager
{
	DECLARE_SINGLE(TimeManager);

private:
	LARGE_INTEGER	m_PrevCount;	// 이전프레임에 체크한 값
	LARGE_INTEGER	m_CurCount;		// 이번 프레임에 체크한 값
	LARGE_INTEGER	m_Frequency;	// 1초당 카운팅 수

	float			m_DeltaTime;	// 1 프레임 간격 시간
	int				m_CallCount;	// 1초동안 호출되는 횟수(FPS)
	float			m_AccTime;		// 누적시간 체크용도

public:
	void Init();
	void Tick();

	float GetDeltaTime() { return m_DeltaTime; }
};

