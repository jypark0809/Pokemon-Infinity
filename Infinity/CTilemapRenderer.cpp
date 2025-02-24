#include "pch.h"
#include "CTilemapRenderer.h"
#include "LevelManager.h"
#include "CLevel.h"
#include "CTransform.h"
#include "CCamera.h"
#include "CTilemap.h"
#include "CGrid.h"
#include "CSprite.h"
#include "CTile.h"

CTilemapRenderer::CTilemapRenderer()
	: CRenderer(ComponentType::TILEMAPRENDERER)
	, m_Tilemap(nullptr)
{
}

CTilemapRenderer::~CTilemapRenderer()
{
}

void CTilemapRenderer::SetTilemap(CTilemap* _Tilemap)
{
	m_Tilemap = _Tilemap;
	m_TileSize = m_Tilemap->GetTileSize();
	m_Column = m_Tilemap->GetColumn();
	m_Row = m_Tilemap->GetRow();
}

void CTilemapRenderer::BeginPlay()
{
}

void CTilemapRenderer::Tick()
{
}

void CTilemapRenderer::FinalTick()
{
}

void CTilemapRenderer::Render(HDC _hdc)
{
	Vec2 vPos = GetOwner()->GetComponent<CTransform>()->GetViewPos();
	vector<CTile*>& m_vecTile = m_Tilemap->GetTileVector();

	for (int Row = 0; Row < m_Row; ++Row)
	{
		for (int Col = 0; Col < m_Column; ++Col)
		{
			int Idx = Row * m_Column + Col;
			if (m_vecTile[Idx] == nullptr)
				continue;

			CSprite* pSprite = m_vecTile[Idx]->GetSprite();

			if (nullptr == pSprite)
				continue;

			Vec2 vRenderPos = vPos + Vec2(Col * m_TileSize, Row * m_TileSize);
			pSprite->Render(_hdc, vRenderPos);
		}
	}
}

