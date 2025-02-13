#include "pch.h"
#include "CGrid.h"


CGrid::CGrid()
	: CComponent(ComponentType::GRID)
{
}

CGrid::~CGrid()
{
}

void CGrid::BeginPlay()
{
}

void CGrid::Tick()
{
}

void CGrid::FinalTick()
{
}

void CGrid::Render(HDC _hdc)
{
	// TODO : ī�޶�
	// Vec2 vPos = GetOwner()->GetViewPos();
	DrawGrid(_hdc, Vec2(0.f, 0.f));
}

void CGrid::DrawGrid(HDC _hdc, Vec2 vPos)
{
	// ���� ��� �׸���
	for (UINT Row = 0; Row <= m_Row; ++Row) {
		MoveToEx(_hdc, (int)vPos.x, (int)vPos.y + Row * m_TileSize, nullptr);
		LineTo(_hdc, (int)vPos.x + m_TileSize * m_Column, (int)vPos.y + Row * m_TileSize);
	}

	// ���� ��� �׸���
	for (UINT Col = 0; Col <= m_Column; ++Col) {
		MoveToEx(_hdc, (int)vPos.x + Col * m_TileSize, (int)vPos.y, nullptr);
		LineTo(_hdc, (int)vPos.x + Col * m_TileSize, (int)vPos.y + m_TileSize * m_Row);
	}
}

