#include "pch.h"
#include "TaskManager.h"
#include "LevelManager.h"
#include "CLevel.h"
#include "CGameObject.h"

TaskManager::TaskManager()

{

}

TaskManager::~TaskManager()
{

}

void TaskManager::Tick()
{
	// Clear Gargabe
	for (size_t i = 0; i < m_vecGarbage.size(); ++i)
	{
		delete m_vecGarbage[i];
	}
	m_vecGarbage.clear();

	// Task Execution
	for (size_t i = 0; i < m_vecTask.size(); ++i)
	{
		Task& task = m_vecTask[i];

		switch (task.Type)
		{
		case TASK_TYPE::CREATE_OBJECT:
		{
			CLevel* pCurLevel = LevelManager::GetInstance()->GetCurrentLevel();

			CGameObject* pNewObj = (CGameObject*)task.Param0;
			LayerType Layer = (LayerType)task.Param1;

			pCurLevel->AddObject(pNewObj, Layer);
			pNewObj->BeginPlay();
		}
		break;
		case TASK_TYPE::DELETE_OBJECT:
		{
			CGameObject* pObject = (CGameObject*)task.Param0;

			// 같은 오브젝트에 대해서 동시에 여러번 삭제 요청이 들어온 경우 예외처리
			if (!pObject->m_Dead)
			{
				pObject->m_Dead = true;
				m_vecGarbage.push_back(pObject);
			}
		}
		break;
		case TASK_TYPE::CHANGE_LEVEL:
		{
			LevelType NextLevelType = (LevelType)task.Param0;
			LevelManager::GetInstance()->LoadLevel(NextLevelType);
		}
		break;
		}
	}

	m_vecTask.clear();
}
