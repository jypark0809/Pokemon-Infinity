#include "pch.h"
#include "CTilemapEditorLevel.h"
#include "AssetManager.h"
#include "CGameObject.h"
#include "CGrid.h"
#include "CTilemap.h"
#include "CTilemapRenderer.h"
#include "CCamera.h"
#include "CTexture.h"

Vec2 vResolutionHD = Vec2(720, 720);

CTilemapEditorLevel::CTilemapEditorLevel()
	: m_SubWnd(nullptr)
	, m_hSubDC(nullptr)
	, m_Grid(nullptr)
{
	// Gird
	CGameObject* pMap = new CGameObject;
	pMap->SetName(L"Map");
	m_Grid = pMap->AddComponent<CGrid>();
	m_Grid->SetTileSize(32);
	m_Grid->SetColumn(10);
	m_Grid->SetRow(10);
	AddObject(pMap, LayerType::MAP);

	// Camera
	CGameObject* pCamera = new CGameObject;
	pCamera->AddComponent<CCamera>();
}

CTilemapEditorLevel::~CTilemapEditorLevel()
{
}

void CTilemapEditorLevel::BeginPlay()
{
	// TEMP
	CGameObject* Ground = new CGameObject;
	CTilemap* tmGround = Ground->AddComponent<CTilemap>();
	tmGround->SetTilemapRenderer(Ground->AddComponent<CTilemapRenderer>());


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
	SELECT_BRUSH(m_SubBackBuffer->GetDC(), BRUSH_TYPE::DARKGRAY);
	Rectangle(m_SubBackBuffer->GetDC(), -1, -1, vResolutionHD.x + 1, vResolutionHD.y + 1);

	// TODO : TilePalette


	// BackBuffer 에 그려진 최종 그림을 MainBuffer 로 복사
	BitBlt(m_hSubDC, 0, 0, vResolutionHD.x, vResolutionHD.y, m_SubBackBuffer->GetDC(), 0, 0, SRCCOPY);





	CLevel::Render(_hdc);
}

void CTilemapEditorLevel::OnEnter()
{
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

int CTilemapEditorLevel::SaveMap(const wstring& _RelativePath)
{
	/*fs::path fullPath = CONTENT_PATH;
	fullPath /= _RelativePath;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, fullPath.c_str(), L"wb");
	assert(pFile);

	SaveWString(pFile, GetName());
	SaveWString(pFile, GetKey());
	SaveWString(pFile, GetRelativePath());

	size_t SpriteCount = m_Sprites.size();
	fwrite(&SpriteCount, sizeof(size_t), 1, pFile);

	for (size_t i = 0; i < SpriteCount; ++i)
	{
		SaveAssetInfo(pFile, m_Sprites[i]);
	}

	fclose(pFile);
	*/
	return S_OK;
}

int CTilemapEditorLevel::LoatMap(const wstring& _RelativePath)
{
	return S_OK;
}

void CTilemapEditorLevel::CreateSubWindow()
{
	m_SubWnd = CreateWindow(
		L"TilePalette", L"Tile Palette",
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		720, 720, NULL, NULL, GetModuleHandle(NULL), NULL
	);

	if (m_SubWnd == NULL) {
		MessageBox(NULL, L"Failed to create subwindow", L"Error", MB_OK | MB_ICONERROR);
		return;
	}

	ShowWindow(m_SubWnd, SW_SHOW);
	UpdateWindow(m_SubWnd);

	m_hSubDC = GetDC(m_SubWnd);
	m_SubBackBuffer = AssetManager::GetInstance()->CreateTexture(L"SubBackBuffer", vResolutionHD.x, vResolutionHD.y);
}

void CTilemapEditorLevel::DestroySubWindow()
{
	if (m_SubWnd) {
		DestroyWindow(m_SubWnd);
		m_SubWnd = NULL; // 핸들을 초기화
	}
}

LRESULT CALLBACK TilemapEditorProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// 메뉴 선택을 구문 분석합니다:
		switch (wmId)
		{
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}