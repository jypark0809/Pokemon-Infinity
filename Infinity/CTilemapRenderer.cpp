#include "pch.h"
#include "CTilemapRenderer.h"
#include "CTransform.h"
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

void CTilemapRenderer::BeginPlay()
{
	m_TileSize = m_Grid->GetTileSize();
	m_Column = m_Grid->GetColumn();
	m_Row = m_Grid->GetRow();
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
			CSprite* pSprite = m_vecTile[Idx]->GetSprite();

			if (nullptr == pSprite)
				continue;

			Vec2 vRenderPos = vPos + Vec2(Col * m_TileSize, Row * m_TileSize);
			pSprite->Render(_hdc, vRenderPos);
		}
	}
}

