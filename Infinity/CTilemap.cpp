#include "pch.h"
#include "CTilemap.h"

CTilemap::CTilemap()
	:CComponent(ComponentType::TILEMAP)
{
}

CTilemap::~CTilemap()
{
}

void CTilemap::BeginPlay()
{
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
	return Vec2Int();
}
