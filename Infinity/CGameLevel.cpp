#include "pch.h"
#include "CGameLevel.h"
#include "AssetManager.h"
#include "CGameObject.h"

#include "CPlayerController.h"
#include "CTransform.h"
#include "CGrid.h"
#include "CTilemap.h"
#include "CTile.h"
#include "CTilemapRenderer.h"
#include "CFlipbookPlayer.h"
#include "CSpriteRenderer.h"

CGameLevel::CGameLevel()
{
	// Player
	CGameObject* pPlayer = new CGameObject;
	pPlayer->SetName(L"Player");
	AddObject(pPlayer, LayerType::PLAYER);
	
	pPlayer->AddComponent<CPlayerController>();
	CFlipbookPlayer* fbPlayer = pPlayer->AddComponent<CFlipbookPlayer>();
	CSpriteRenderer* spRenderer = pPlayer->AddComponent<CSpriteRenderer>(); // TODO : 자동으로 추가
	fbPlayer->SetSpriteRenderer(spRenderer);

	AddObject(pPlayer, LayerType::PLAYER);
}

CGameLevel::~CGameLevel()
{
}

void CGameLevel::BeginPlay()
{
	CLevel::BeginPlay();

	LoadMap();
}

void CGameLevel::Tick()
{
	CLevel::Tick();
}

void CGameLevel::OnEnter()
{
	CLevel::OnEnter();
}

void CGameLevel::OnExit()
{
	CLevel::OnExit();
}

void CGameLevel::LoadMap()
{
	fs::path fullPath = CONTENT_PATH;
	fullPath /= L"Map\\Map_Test.map";

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, fullPath.c_str(), L"rb");

	int tileSize, columns, rows, tilemapCount;

	fread(&tileSize, sizeof(int), 1, pFile);
	fread(&columns, sizeof(int), 1, pFile);
	fread(&rows, sizeof(int), 1, pFile);
	fread(&tilemapCount, sizeof(int), 1, pFile);

	CGameObject* pMapObj = new CGameObject;
	pMapObj->SetName(L"Map");

	m_MapGrid = pMapObj->AddComponent<CGrid>();
	m_MapGrid->SetTileSize(tileSize);
	m_MapGrid->SetColumn(columns);
	m_MapGrid->SetRow(rows);
	AddObject(pMapObj, LayerType::MAP);

	for (size_t i = 0; i < tilemapCount; ++i)
	{
		wstring tilemapName;
		int tileCount;
		LoadWString(pFile, tilemapName);
		fread(&tileCount, sizeof(int), 1, pFile);
		CTilemap* pTilemap = AddTilemap(tilemapName);

		for (size_t j = 0; j < tileCount; ++j)
		{
			CTile* pTile = dynamic_cast<CTile*>(LoadAssetInfo(pFile, AssetType::TILE));
			if (pTile)
			{
				int x, y;
				fread(&x, sizeof(int), 1, pFile);
				fread(&y, sizeof(int), 1, pFile);

				pTilemap->AddTile(x, y, pTile->GetKey());
			}
		}
	}

	fclose(pFile);
}

CTilemap* CGameLevel::AddTilemap(const wstring& _ObjectName)
{
	CGameObject* tilemapObj = new CGameObject;
	tilemapObj->SetName(_ObjectName);

	CTilemap* tilemap = tilemapObj->AddComponent<CTilemap>();
	tilemap->SetGrid(m_MapGrid);

	CTilemapRenderer* tmRenderer = tilemapObj->AddComponent<CTilemapRenderer>();
	tmRenderer->SetTilemap(tilemap);

	CGameObject* owner = m_MapGrid->GetOwner();
	owner->AddChild(tilemapObj);

	return tilemap;
}