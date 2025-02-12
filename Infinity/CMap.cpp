#include "pch.h"
#include "CMap.h"
#include "CGrid.h"

CMap::CMap()
	:m_Grid(nullptr)
{
	m_Grid = (CGrid*)AddComponent(new CGrid(32, 10, 10));
}

CMap::~CMap()
{
}

void CMap::BeginPlay()
{
}

void CMap::Tick()
{
}

void CMap::FinalTick()
{
}

void CMap::Render(HDC _hdc)
{
	m_Grid->Render(_hdc);
}
