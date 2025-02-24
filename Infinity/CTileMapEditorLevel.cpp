#include "pch.h"
#include "CTilemapEditorLevel.h"
#include "AssetManager.h"
#include "KeyManager.h"
#include "CGameObject.h"
#include "CGrid.h"
#include "CTilemap.h"
#include "CTilemapRenderer.h"
#include "CCamera.h"
#include "CTexture.h"
#include "CSprite.h"
#include "CTile.h"

Vec2 vResolutionHD = Vec2(256, 960);
Vec2Int vSelectedIndex;

CTilemapEditorLevel::CTilemapEditorLevel()
	: m_SubWnd(nullptr)
	, m_hSubDC(nullptr)
	, m_SubBackBuffer(nullptr)
	, m_TileTexture(nullptr)
{
	{
		CGameObject* pMap = new CGameObject;
		pMap->SetName(L"Map");
		m_Grid = pMap->AddComponent<CGrid>();
		m_Grid->SetTileSize(32);
		m_Grid->SetColumn(50);
		m_Grid->SetRow(50);
		AddObject(pMap, LayerType::MAP);

		CGameObject* pGround = new CGameObject;
		pGround->SetName(L"Ground");
		m_Tilemap = pGround->AddComponent<CTilemap>();
		m_Tilemap->SetGrid(m_Grid);
		CTilemapRenderer* tmRenderer = pGround->AddComponent<CTilemapRenderer>();
		tmRenderer->SetTilemap(m_Tilemap);
		pMap->AddChild(pGround);
	}
}

CTilemapEditorLevel::~CTilemapEditorLevel()
{
}

void CTilemapEditorLevel::BeginPlay()
{
	LoadTile(); // AssetManager 에서?

	LoadFile();

	ChangeSubWindowSize(m_TileTexture->GetWidth(), m_TileTexture->GetHeight());

	CLevel::BeginPlay();
}

void CTilemapEditorLevel::Tick()
{
	CLevel::Tick();

	if (KeyManager::GetInstance()->GetButtonDown(Key::LBUTTON))
	{
		Vec2Int vClickedPos = m_Grid->WorldToCell(KeyManager::GetInstance()->GetMousePos());
		wstring textureName = m_TileTexture->GetName() + L"_%d";

		wchar_t szKey[255] = {};
		int index = vSelectedIndex.y * (m_TileTexture->GetWidth() / 32) + vSelectedIndex.x;
		swprintf_s(szKey, 255, textureName.c_str(), index);

		wstring Path = L"Tile\\";
		Path = Path + szKey + L".tile";
		CTile* pTile = AssetManager::GetInstance()->LoadTile(szKey, Path);
		m_Tilemap->AddTile(vClickedPos.x, vClickedPos.y, szKey);
	}
}

void CTilemapEditorLevel::FinalTick()
{
	CLevel::FinalTick();
}

void CTilemapEditorLevel::Render(HDC _hdc)
{
	{
		SELECT_BRUSH(m_SubBackBuffer->GetDC(), BRUSH_TYPE::DARKGRAY);
		Rectangle(m_SubBackBuffer->GetDC(), -1, -1, vResolutionHD.x + 1, vResolutionHD.y + 1);
	}

	if (m_TileTexture)
	{
		m_TileTexture->Render(m_SubBackBuffer->GetDC(), Vec2(0, 0));
		
		// Tile Palette
		CGameObject* pGridObj = new CGameObject;
		CGrid* grid = pGridObj->AddComponent<CGrid>();
		grid->SetTileSize(32);
		int column = m_TileTexture->GetWidth() / 32;
		int row = m_TileTexture->GetHeight() / 32;
		grid->SetColumn(column);
		grid->SetRow(row);
		grid->Render(m_SubBackBuffer->GetDC());
	}

	// BackBuffer 에 그려진 최종 그림을 MainBuffer 로 복사
	BitBlt(m_hSubDC, 0, 0, vResolutionHD.x, vResolutionHD.y, m_SubBackBuffer->GetDC(), 0, 0, SRCCOPY);

	CLevel::Render(_hdc);
}

void CTilemapEditorLevel::OnEnter()
{
	CEngine::GetInstance()->ChangeWindowSize(1024, 960);

	CreateSubWindow();

	CLevel::OnEnter();
}

void CTilemapEditorLevel::OnExit()
{
	CLevel::OnExit();
}

void CTilemapEditorLevel::LoadFile()
{
	wstring InitialDir = CONTENT_PATH.wstring() + L"\\Texture";

	// 파일 경로 문자열
	wchar_t szFilePath[255] = {};
	OPENFILENAME Desc = {};
	Desc.lStructSize = sizeof(OPENFILENAME);
	Desc.hwndOwner = nullptr;
	Desc.lpstrFile = szFilePath; // 최종적으로 고른 경로를 받아낼 목적지
	Desc.nMaxFile = 255;
	Desc.lpstrFilter = L"그림 파일\0*.png;*.bmp\0모든 파일(*.*)\0*.*";
	Desc.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	Desc.lpstrInitialDir = InitialDir.c_str();

	if (GetOpenFileName(&Desc))
	{
		fs::path filePath(szFilePath);
		wstring fullPath = filePath.wstring();
		wstring relativePath = fullPath.substr(fullPath.find(L"Texture\\"));
		wstring fileName = filePath.stem().wstring(); // .png 제외

		CTexture* pTex = AssetManager::GetInstance()->LoadTexture(fileName, relativePath);
		pTex->SetName(fileName);
		m_TileTexture = pTex;
	}

	// Save Tile
	wstring textureName = m_TileTexture->GetName();
	wstring tileName = textureName + L"_%d";

	int columns = m_TileTexture->GetWidth() / 32;
	int rows = m_TileTexture->GetHeight() / 32;

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < columns; ++j)
		{
			wchar_t szKey[255] = {};
			int index = i * columns + j;
			swprintf_s(szKey, 255, tileName.c_str(), index);

			Vec2 vLeftTop((float)j * 32, (float)i * 32);

			// Sprite 생성
			CSprite* pSprite = AssetManager::GetInstance()->CreateSprite(szKey
				, m_TileTexture
				, vLeftTop
				, Vec2(32.f, 32.f)
				, Vec2(0.f, 0.f));
			
			// TODO : Sprite 저장

			CTile* pTile = AssetManager::GetInstance()->CreateTile(szKey, pSprite);

			// 상대 경로 설정
			wstring Path = L"Tile\\";
			Path = Path + szKey + L".tile";
			pTile->SetKey(szKey);
			pTile->SetRelativePath(Path);
			pTile->Save(Path);
		}
	}
}

void CTilemapEditorLevel::ChangeSubWindowSize(int _Width, int _Height)
{
	if (m_SubBackBuffer)
		m_SubBackBuffer->Resize(_Width, _Height);

	RECT rect = { 0, 0, _Width, _Height };

	// 설정한 해상도에 따른 윈도우의 크기 계산
	// GetMenu(m_hWnd) : 해당 윈도우에 메뉴가 없다면 nullptr, 있다면 1을 반환한다.
	// !! : 이중부정 연산자는 GetMenu(m_hWnd)의 반환값을 0 또는 1로 변환한다.
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, !!GetMenu(m_SubWnd));

	// 윈도우 크기 및 위치 설정
	SetWindowPos(m_SubWnd
		, nullptr
		, 1024
		, 0
		, rect.right - rect.left
		, rect.bottom - rect.top
		, 0);
}

int CTilemapEditorLevel::SaveMap(const wstring& _RelativePath)
{
	return S_OK;
}

int CTilemapEditorLevel::LoadMap(const wstring& _RelativePath)
{
	return S_OK;
}

void CTilemapEditorLevel::LoadTile()
{
	fs::path filePath = CONTENT_PATH;
	filePath /= L"Tile";

	if (fs::exists(filePath) && fs::is_directory(filePath))
	{
		int fileCount = 0;
		for (const auto& entry : fs::directory_iterator(filePath))
		{
			if (fs::is_regular_file(entry))
			{
				// TODO
				fileCount++;
				wstring fileName = entry.path().filename().wstring();
			}
		}
	}
}

void CTilemapEditorLevel::CreateSubWindow()
{
	// SetMenu(CEngine::GetInstance()->GetMainWnd(), m_hMenu);

	m_SubWnd = CreateWindow(
		L"TilePalette", L"Tile Palette",
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		256, 960, NULL, NULL, GetModuleHandle(NULL), NULL
	);

	if (m_SubWnd == NULL) {
		MessageBox(NULL, L"Failed to create subwindow", L"Error", MB_OK | MB_ICONERROR);
		return;
	}

	ShowWindow(m_SubWnd, SW_SHOW);
	UpdateWindow(m_SubWnd);

	RECT rect = { 0, 0, 256, 960 };

	// 설정한 해상도에 따른 윈도우의 크기 계산
	// GetMenu(m_hWnd) : 해당 윈도우에 메뉴가 없다면 nullptr, 있다면 1을 반환한다.
	// !! : 이중부정 연산자는 GetMenu(m_hWnd)의 반환값을 0 또는 1로 변환한다.
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, 0);

	// 윈도우 크기 및 위치 설정
	SetWindowPos(m_SubWnd
		, nullptr
		, 1024
		, 0
		, rect.right - rect.left
		, rect.bottom - rect.top
		, 0);

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
	case WM_LBUTTONDOWN:
	{
		POINT mousePos = { };
		GetCursorPos(&mousePos);
		ScreenToClient(hWnd, &mousePos);

		Vec2 mousePosition;
		mousePosition.x = mousePos.x;
		mousePosition.y = mousePos.y;

		int idxX = mousePosition.x / 32;
		int idxY = mousePosition.y / 32;

		vSelectedIndex = Vec2Int(idxX, idxY);
	}
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