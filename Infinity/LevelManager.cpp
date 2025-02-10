#include "pch.h"
#include "LevelManager.h"
#include "CLevel.h"
#include "CTitleLevel.h"
#include "CGameLevel.h"
#include "CSpriteEditorLevel.h"
#include "CFlipbookEditorLevel.h"

LevelManager::LevelManager()
	: m_Levels{}
	, m_CurLevel(nullptr)
{
}

LevelManager::~LevelManager()
{
	Delete_Arr(m_Levels);
}

void LevelManager::Init()
{
	// m_arrLevel[TITLE] = new TitleLevel;
	m_Levels[LevelType::TITLE] = new CTitleLevel;
	m_Levels[LevelType::GAME] = new CGameLevel;
	m_Levels[LevelType::SPRITE_EDITOR] = new CSpriteEditorLevel;
	m_Levels[LevelType::FLIPBOOK_EDITOR] = new CFlipbookEditorLevel;
	m_Levels[LevelType::TILEMAP_EDITOR] = nullptr;
	

	// StartLevel 을 현재 레벨로 지정
	LoadLevel(LevelType::SPRITE_EDITOR);
}

void LevelManager::Tick()
{
	if (nullptr == m_CurLevel)
		return;

	m_CurLevel->Tick();
}

void LevelManager::FinalTick()
{
	if (nullptr == m_CurLevel)
		return;

	m_CurLevel->FinalTick();
}

void LevelManager::Render(HDC _dc)
{
	if (nullptr == m_CurLevel)
		return;

	m_CurLevel->Render(_dc);
}

void LevelManager::LoadLevel(LevelType _NextType)
{
	if (m_CurLevel == m_Levels[_NextType])
		return;

	if (nullptr != m_CurLevel)
		m_CurLevel->OnExit();

	SetCurrentLevel(_NextType);

	if (nullptr != m_CurLevel)
	{
		m_CurLevel->OnEnter();
	}
}
