#include "pch.h"
#include "CTilemap.h"
#include "AssetManager.h"
#include "CTexture.h"
#include "CSprite.h"
#include "CGrid.h"
#include "CTile.h"

CTilemap::CTilemap()
	:CComponent(ComponentType::TILEMAP)
	, m_Grid(nullptr)
	, m_tmRenderer(nullptr)
{
}

CTilemap::~CTilemap()
{
}

void CTilemap::BeginPlay()
{
	m_TileSize = m_Grid->GetTileSize();
	m_Column = m_Grid->GetColumn();
	m_Row = m_Grid->GetRow();
}

void CTilemap::Tick()
{
}

void CTilemap::FinalTick()
{
}

void CTilemap::Render(HDC _hdc)
{
}

void CTilemap::AddTile(int _Column, int _Row, const wstring& _TileKey)
{
	// 존재하지 않는 행렬위치를 지정한 경우
	if (_Row < 0 || m_Row <= _Row || _Column < 0 || m_Column <= _Column)
		return;

	CTile* pTile = AssetManager::GetInstance()->GetTile(_TileKey);
	assert(pTile);

	int Idx = _Row * m_Column + _Column;
	m_vecTile[Idx] = pTile;
}

Vec2Int CTilemap::WorldToCell(Vec2 _Pos)
{
	return Vec2Int(static_cast<int>(_Pos.x/m_TileSize), static_cast<int>(_Pos.y/m_TileSize));
}
