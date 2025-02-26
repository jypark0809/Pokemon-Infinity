#include "pch.h"
#include "CGrid.h"
#include "CTransform.h"
#include "LevelManager.h"
#include "CLevel.h"
#include "CCamera.h"

CGrid::CGrid()
	: CComponent(ComponentType::GRID)
{
}

CGrid::~CGrid()
{
}

Vec2Int CGrid::WorldToCell(Vec2 _WorldPosition)
{
	CCamera* pCamera = LevelManager::GetInstance()->GetCurrentLevel()->GetCamera();
	Vec2 vWorldPosition = pCamera->GetWorldPos(_WorldPosition);
	Vec2 vDiff = vWorldPosition - GetOwner()->GetComponent<CTransform>()->GetPosition();

	int column = (int)vDiff.x / m_TileSize;
	int row = (int)vDiff.y / m_TileSize;

	// 존재하지 않는 행렬위치를 지정한 경우
	if (m_Row <= row || m_Column <= column)
	{
		return Vec2Int(-1, -1);
	}

	return Vec2Int(column, row);
}

Vec2 CGrid::CellToWorld(Vec2Int _CellPosition)
{
	return Vec2();
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
	Vec2 vPos = GetOwner()->GetComponent<CTransform>()->GetViewPos();
	DrawGrid(_hdc, vPos);
}

void CGrid::DrawGrid(HDC _hdc, Vec2 vPos)
{
	// 수평 경계 그리기
	for (UINT Row = 0; Row <= m_Row; ++Row) {
		MoveToEx(_hdc, (int)vPos.x, (int)vPos.y + Row * m_TileSize, nullptr);
		LineTo(_hdc, (int)vPos.x + m_TileSize * m_Column, (int)vPos.y + Row * m_TileSize);
	}

	// 수직 경계 그리기
	for (UINT Col = 0; Col <= m_Column; ++Col) {
		MoveToEx(_hdc, (int)vPos.x + Col * m_TileSize, (int)vPos.y, nullptr);
		LineTo(_hdc, (int)vPos.x + Col * m_TileSize, (int)vPos.y + m_TileSize * m_Row);
	}
}

void CGrid::RenderWorldScale(HDC _hdc)
{
	Vec2 vPos = GetOwner()->GetComponent<CTransform>()->GetPosition();
	DrawGrid(_hdc, vPos);
}