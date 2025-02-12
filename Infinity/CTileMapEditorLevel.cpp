#include "pch.h"
#include "CTilemapEditorLevel.h"
#include "CGameObject.h"
#include "CMap.h"
#include "CGrid.h"

CTilemapEditorLevel::CTilemapEditorLevel()
	:m_Map(nullptr)
{
	m_Map = new CMap;
	AddObject(m_Map, LayerType::MAP);
}

CTilemapEditorLevel::~CTilemapEditorLevel()
{
}

void CTilemapEditorLevel::BeginPlay()
{

}

void CTilemapEditorLevel::Tick()
{
}

void CTilemapEditorLevel::FinalTick()
{
}

void CTilemapEditorLevel::Render(HDC _hdc)
{
	CLevel::Render(_hdc);
}

void CTilemapEditorLevel::OnEnter()
{
}

void CTilemapEditorLevel::OnExit()
{
}


