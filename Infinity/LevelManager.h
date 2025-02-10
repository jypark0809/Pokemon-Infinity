#pragma once

class CLevel;

class LevelManager
{
	DECLARE_SINGLE(LevelManager);
private:
	CLevel*		m_Levels[LevelType::COUNT];
	CLevel*		m_CurLevel;

private:
	void LoadLevel(LevelType _NextType);
	void SetCurrentLevel(LevelType _NextType) { m_CurLevel = m_Levels[_NextType]; }

public:
	CLevel* GetCurrentLevel() { return m_CurLevel; }

public:
	void Init();
	void Tick();
	void FinalTick();
	void Render(HDC _dc);

	friend class TaskManager;
};

