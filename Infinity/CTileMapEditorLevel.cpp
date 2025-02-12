#include "pch.h"
#include "CTilemapEditorLevel.h"
#include "CGameObject.h"
#include "CGrid.h"

CTilemapEditorLevel::CTilemapEditorLevel()
	: m_Grid(nullptr)
	, m_vecTilemap{}
{
	// Map
	CGameObject* pMap = new CGameObject;
	m_Grid = pMap->AddComponent<CGrid>();
	m_Grid->SetCellSize(32);
	m_Grid->SetColumn(10);
	m_Grid->SetRow(10);
	pMap->SetName(L"Map");
	AddObject(pMap, LayerType::MAP);
}

CTilemapEditorLevel::~CTilemapEditorLevel()
{
}

void CTilemapEditorLevel::BeginPlay()
{
	CLevel::BeginPlay();
}

void CTilemapEditorLevel::Tick()
{
	CLevel::Tick();
}

void CTilemapEditorLevel::FinalTick()
{
	CLevel::FinalTick();
}

void CTilemapEditorLevel::Render(HDC _hdc)
{
	CLevel::Render(_hdc);
}

void CTilemapEditorLevel::OnEnter()
{
	Vec2 vResolutionHD = Vec2(1280, 720);
	CEngine::GetInstance()->ChangeWindowSize(int(vResolutionHD.x), int(vResolutionHD.y));

	CreateSubWindow();

	CLevel::OnEnter();
}

void CTilemapEditorLevel::OnExit()
{
	CLevel::OnExit();
}

bool CTilemapEditorLevel::Cango(Vec2Int _CellPos)
{
	return false;
}

void CTilemapEditorLevel::CreateSubWindow()
{
	m_SubWindow = CreateWindow(
		L"TilePalette", L"Tile Palette",
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		720, 720, NULL, NULL, GetModuleHandle(NULL), NULL
	);

	if (m_SubWindow == NULL) {
		MessageBox(NULL, L"Failed to create subwindow", L"Error", MB_OK | MB_ICONERROR);
		return;
	}

	ShowWindow(m_SubWindow, SW_SHOW);
	UpdateWindow(m_SubWindow);
}

void CTilemapEditorLevel::DestroySubWindow()
{
	if (m_SubWindow) {
		DestroyWindow(m_SubWindow);
		m_SubWindow = NULL; // 핸들을 초기화
	}
}
