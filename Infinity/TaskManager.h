#pragma once
class TaskManager
{
	DECLARE_SINGLE(TaskManager);
private:
	vector<Task>	m_vecTask;
	vector<CObject*>	m_vecGarbage;

public:
	void AddTask(const Task& _Task) { m_vecTask.push_back(_Task); }

public:
	void Tick();
};

