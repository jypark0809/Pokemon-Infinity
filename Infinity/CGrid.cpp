#include "pch.h"
#include "CGrid.h"


CGrid::CGrid(UINT _CellSize, UINT _Columns, UINT _Rows)
	: CComponent(ComponentType::GRID)
	, m_CellSize(_CellSize)
	, m_Columns(_Columns)
	, m_Rows(_Rows)
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
	// TODO : 카메라
	// Vec2 vPos = GetOwner()->GetViewPos();
	DrawGrid(_hdc, Vec2(10.f, 0.f), m_CellSize, m_Rows, m_Columns);
}

void CGrid::DrawGrid(HDC _hdc, Vec2 vPos, UINT m_CellSize, UINT m_Row, UINT m_Col)
{
	// 수평 경계 그리기
	for (UINT Row = 0; Row <= m_Row; ++Row) {
		MoveToEx(_hdc, (int)vPos.x, (int)vPos.y + Row * m_CellSize, nullptr);
		LineTo(_hdc, (int)vPos.x + m_CellSize * m_Col, (int)vPos.y + Row * m_CellSize);
	}

	// 수직 경계 그리기
	for (UINT Col = 0; Col <= m_Col; ++Col) {
		MoveToEx(_hdc, (int)vPos.x + Col * m_CellSize, (int)vPos.y, nullptr);
		LineTo(_hdc, (int)vPos.x + Col * m_CellSize, (int)vPos.y + m_CellSize * m_Row);
	}
}

