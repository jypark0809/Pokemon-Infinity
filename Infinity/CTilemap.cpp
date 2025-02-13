#include "pch.h"
#include "CTilemap.h"
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

Vec2Int CTilemap::WorldToCell(Vec2 _Pos)
{
	return Vec2Int(static_cast<int>(_Pos.x/m_TileSize), static_cast<int>(_Pos.y/m_TileSize));
}
