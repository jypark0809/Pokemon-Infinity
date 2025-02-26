#include "pch.h"
#include "CTilemapEditorLevel.h"
#include "KeyManager.h"
#include "TimeManager.h"
#include "AssetManager.h"
#include "CGameObject.h"
#include "CTransform.h"
#include "CGrid.h"
#include "CTilemap.h"
#include "CTilemapRenderer.h"
#include "CCamera.h"
#include "CTexture.h"
#include "CSprite.h"
#include "CTile.h"

Vec2 vResolutionHD = Vec2(256, 960);
Vec2Int vSelectedIndex;
int m_Speed = 200;

CTilemapEditorLevel::CTilemapEditorLevel()
	: m_SubWnd(nullptr)
	, m_hSubDC(nullptr)
	, m_SubBackBuffer(nullptr)
	, m_TileTexture(nullptr)
	, m_PaintingTool(PaintingTool::PaintBrush)
{
	{
		m_hMenu = LoadMenu(nullptr, (LPCWSTR)IDR_MENU_TILEMAPEDITOR);
		assert(m_hMenu);

		m_hSubMenu = LoadMenu(nullptr, (LPCWSTR)IDR_MENU_TILEPALETTE);
		assert(m_hSubMenu);

		CGameObject* pMap = new CGameObject;
		pMap->SetName(L"Map");
		m_Grid = pMap->AddComponent<CGrid>();
		m_Grid->SetTileSize(32);
		m_Grid->SetColumn(50);
		m_Grid->SetRow(50);
		AddObject(pMap, LayerType::MAP);

		// CGameObject* pGround = new CGameObject;
		// pGround->SetName(L"Ground");
		// m_Tilemap = pGround->AddComponent<CTilemap>();
		// m_Tilemap->SetGrid(m_Grid);
		// CTilemapRenderer* tmRenderer = pGround->AddComponent<CTilemapRenderer>();
		// tmRenderer->SetTilemap(m_Tilemap);
		// pMap->AddChild(pGround);

		AddObject(GetCamera()->GetOwner(), LayerType::CAMERA);
	}
}

CTilemapEditorLevel::~CTilemapEditorLevel()
{
}

void CTilemapEditorLevel::BeginPlay()
{
	// LoadTile(); // AssetManager 에서?


	CLevel::BeginPlay();
}


void CTilemapEditorLevel::Tick()
{
	CLevel::Tick();

	// TEMP
	if (KeyManager::GetInstance()->GetButton(Key::LEFT))
		GetCamera()->GetOwner()->GetComponent<CTransform>()->Translate(Vec2(-m_Speed * DT, 0));
	if (KeyManager::GetInstance()->GetButton(Key::UP))
		GetCamera()->GetOwner()->GetComponent<CTransform>()->Translate(Vec2(0, -m_Speed * DT));
	if (KeyManager::GetInstance()->GetButton(Key::DOWN))
		GetCamera()->GetOwner()->GetComponent<CTransform>()->Translate(Vec2(0, m_Speed * DT));
	if (KeyManager::GetInstance()->GetButton(Key::RIGHT))
		GetCamera()->GetOwner()->GetComponent<CTransform>()->Translate(Vec2(m_Speed * DT, 0));

	if (!m_Tilemap)
		return;

	if (KeyManager::GetInstance()->GetButtonDown(Key::LBUTTON))
	{
		Vec2Int vClickedPos = m_Grid->WorldToCell(KeyManager::GetInstance()->GetMousePos());

		if (m_PaintingTool == PaintingTool::PaintBrush)
		{
			wstring textureName = m_TileTexture->GetName() + L"_%d";

			wchar_t szKey[255] = {};
			int index = vSelectedIndex.y * (m_TileTexture->GetWidth() / 32) + vSelectedIndex.x;
			swprintf_s(szKey, 255, textureName.c_str(), index);

			wstring Path = L"Tile\\";
			Path = Path + szKey + L".tile";
			CTile* pTile = AssetManager::GetInstance()->LoadTile(szKey, Path);

			// TODO

			m_Tilemap->AddTile(vClickedPos.x, vClickedPos.y, szKey);
		}
		else if (m_PaintingTool == PaintingTool::Eraser)
		{
			m_Tilemap->DeleteTile(vClickedPos.x, vClickedPos.y);
		}
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
		grid->RenderWorldScale(m_SubBackBuffer->GetDC());
	}

	// BackBuffer 에 그려진 최종 그림을 MainBuffer 로 복사
	BitBlt(m_hSubDC, 0, 0, vResolutionHD.x, vResolutionHD.y, m_SubBackBuffer->GetDC(), 0, 0, SRCCOPY);

	CLevel::Render(_hdc);
}

void CTilemapEditorLevel::OnEnter()
{
	CEngine::GetInstance()->ChangeWindowSize(1024, 960);
	
	CreateSubWindow();
	ChangeSubWindowSize(vResolutionHD.x, vResolutionHD.y);

	SetMenu(CEngine::GetInstance()->GetMainWnd(), m_hMenu);
	SetMenu(m_SubWnd, m_hSubMenu);


	CLevel::OnEnter();
}

void CTilemapEditorLevel::OnExit()
{
	CLevel::OnExit();
}

void CTilemapEditorLevel::AddTilemap(const wstring& _TilemapName)
{
	CGameObject* tilemapObj = new CGameObject;
	tilemapObj->SetName(_TilemapName);

	CTilemap* tilemap = tilemapObj->AddComponent<CTilemap>();
	tilemap->SetGrid(m_Grid);

	CTilemapRenderer* tmRenderer = tilemapObj->AddComponent<CTilemapRenderer>();
	tmRenderer->SetTilemap(tilemap);

	CGameObject* owner = m_Grid->GetOwner();
	owner->AddChild(tilemapObj);

	m_Tilemap = tilemap;
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
		pTex->SetKey(fileName);
		pTex->SetRelativePath(relativePath);
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
			pTile->SetName(szKey);
			pTile->SetKey(szKey);
			pTile->SetRelativePath(Path);
			pTile->Save(Path);
		}
	}

	ChangeSubWindowSize(m_TileTexture->GetWidth(), m_TileTexture->GetHeight());
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

int CTilemapEditorLevel::SaveMap()
{
	// 파일 경로 문자열
	wchar_t szFilePath[255] = {};
	wstring InitialDir = CONTENT_PATH.wstring() + L"\\Map";

	OPENFILENAME Desc = {};
	Desc.lStructSize = sizeof(OPENFILENAME);
	Desc.hwndOwner = nullptr;
	Desc.lpstrFile = szFilePath;	// 최종적으로 고른 경로를 받아낼 목적지
	Desc.nMaxFile = 255;
	Desc.lpstrFilter = L"Map Files\0*.map\0All Files (*.*)\0*.*";
	Desc.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	Desc.lpstrInitialDir = InitialDir.c_str();

	if (GetSaveFileName(&Desc))
	{
		fs::path filePath(szFilePath);
		wstring fullPath = filePath.wstring();
		// wstring relativePath = fullPath.substr(fullPath.find(L"Map\\"));
		// wstring fileName = filePath.stem().wstring(); // .map 제외

		FILE* pFile = nullptr;
		_wfopen_s(&pFile, fullPath.c_str(), L"wb");

		int tileSize = m_Grid->GetTileSize();
		int columns = m_Grid->GetColumn();
		int rows = m_Grid->GetRow();
		int tilemapCount = m_Grid->GetTilemapVector().size();

		fwrite(&tileSize, sizeof(int), 1, pFile);
		fwrite(&columns, sizeof(int), 1, pFile);
		fwrite(&rows, sizeof(int), 1, pFile);
		fwrite(&tilemapCount, sizeof(int), 1, pFile);

		for (size_t i = 0; i < tilemapCount; ++i)
		{
			CTilemap* pTilemap = m_Grid->GetTilemapVector()[i];
			wstring tilemapName = pTilemap->GetOwner()->GetName();

			// tilemapName fwrite();

			for (size_t j = 0; j < pTilemap->GetTileVector().size(); ++j)
			{
				CTile* pTile = pTilemap->GetTileVector()[j];
				SaveAssetInfo(pFile, pTile);
			}
		}

		fclose(pFile);
	}

	return S_OK;
}

int CTilemapEditorLevel::LoadMap()
{
	// REVERT

	// 파일 경로 문자열
	wchar_t szFilePath[255] = {};
	wstring InitialDir = CONTENT_PATH.wstring() + L"\\Texture";

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
		// wstring relativePath = fullPath.substr(fullPath.find(L"Texture\\"));
		// wstring fileName = filePath.stem().wstring(); // .png 제외

		FILE* pFile = nullptr;
		_wfopen_s(&pFile, fullPath.c_str(), L"rb");

		int tileSize;
		int columns;
		int rows;
		int tilemapCount;

		fread(&tileSize, sizeof(int), 1, pFile);
		fread(&columns, sizeof(int), 1, pFile);
		fread(&rows, sizeof(int), 1, pFile);
		fread(&tilemapCount, sizeof(int), 1, pFile);

		m_Grid->SetTileSize(tileSize);
		m_Grid->SetColumn(columns);
		m_Grid->SetRow(rows);

		for (size_t i = 0; i < tilemapCount; ++i)
		{
			CTilemap* pTilemap = m_Grid->GetTilemapVector()[i];
			for (size_t j = 0; j < pTilemap->GetTileVector().size(); ++j)
			{
				CTile* pTile = pTilemap->GetTileVector()[j];
				SaveAssetInfo(pFile, pTile);
			}
		}

		fclose(pFile);
	}

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


#include "LevelManager.h"
LRESULT CALLBACK TilePaletteProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// 메뉴 선택을 구문 분석합니다:
		switch (wmId)
		{
		case ID_TILEPALETTE_OPENFILE:
		{
			CTilemapEditorLevel* pLevel = dynamic_cast<CTilemapEditorLevel*>(LevelManager::GetInstance()->GetCurrentLevel());
			assert(pLevel);
			pLevel->LoadFile();
			break;
		}
		case ID_HELPER_TILEPALETTEHELPER:
		{
			// [Tilemap Editor] - [Helper] - [Tile Palette Helper]
			HWND hDlg = CreateDialog(CEngine::GetInstance()->GetHInst(), MAKEINTRESOURCE(IDD_DIALOG_TILEPALETTE_HELPER), hWnd, TilePaletteHelperProc);
			ShowWindow(hDlg, SW_SHOW);
			break;
		}
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
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

HWND hComboBox;
HWND hEditControl;
INT_PTR CALLBACK TilePaletteHelperProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{
		// ComboBox의 핸들 가져오기
		hComboBox = GetDlgItem(hDlg, IDC_TILEPALETTE_COMBO);
		hEditControl = GetDlgItem(hDlg, IDC_TILEPALETTE_EDIT_ADDTILEMAP);
		
		// ComboBox에 항목 추가
		// SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)L"Ground");

		// 첫 번째 항목을 선택
		// SendMessage(hComboBox, CB_SETCURSEL, 0, 0);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		if (HIWORD(wParam) == CBN_SELCHANGE && LOWORD(wParam) == IDC_TILEPALETTE_COMBO)
		{
			CTilemapEditorLevel* pLevel = dynamic_cast<CTilemapEditorLevel*>(LevelManager::GetInstance()->GetCurrentLevel());
			assert(pLevel);

			// 유효한 인덱스인지 확인
			int index = SendMessage(hComboBox, CB_GETCURSEL, 0, 0);
			if (index == CB_ERR)
				break;

			wchar_t buffer[256];
			SendMessage(hComboBox, CB_GETLBTEXT, index, (LPARAM)buffer);

			CGameObject* RootObj = pLevel->GetTilemap()->GetOwner()->GetParent();
			for (size_t i = 0; i < RootObj->GetChildren().size(); ++i)
			{
				CTilemap* pTilemap = RootObj->GetChildren()[i]->GetComponent<CTilemap>();
				if (pTilemap && pTilemap->GetOwner()->GetName() == buffer)
				{
					pLevel->SetTilemap(pTilemap);
					break;
				}
			}
		}
		else if (LOWORD(wParam) == IDC_BUTTON_ADDTILEMAP)
		{
			// Edit Control에서 텍스트 가져오기
			wchar_t editText[256];
			GetWindowText(hEditControl, editText, ARRAYSIZE(editText));

			// 빈 문자열인 경우 아무 일도 하지 않음
			if (wcslen(editText) == 0) 
				break;

			// Edit Control의 텍스트를 ComboBox에 추가
			SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)editText);

			CTilemapEditorLevel* pLevel = dynamic_cast<CTilemapEditorLevel*>(LevelManager::GetInstance()->GetCurrentLevel());
			assert(pLevel);
			pLevel->AddTilemap(editText);

			// 방금 추가한 항목 선택
			SendMessage(hComboBox, CB_SETCURSEL, SendMessage(hComboBox, CB_GETCOUNT, 0, 0) - 1, 0); 

			// // Edit Control을 빈 문자열로 설정
			SetWindowText(hEditControl, L"");
		}
		else if (LOWORD(wParam) == IDC_TILEPALETTE_BUTTON_PAINT)
		{
			CTilemapEditorLevel* pLevel = dynamic_cast<CTilemapEditorLevel*>(LevelManager::GetInstance()->GetCurrentLevel());
			assert(pLevel);
			pLevel->SetPaintingTool(PaintingTool::PaintBrush);
		}
		else if (LOWORD(wParam) == IDC_TILEPALETTE_BUTTON_ERASE)
		{
			CTilemapEditorLevel* pLevel = dynamic_cast<CTilemapEditorLevel*>(LevelManager::GetInstance()->GetCurrentLevel());
			assert(pLevel);
			pLevel->SetPaintingTool(PaintingTool::Eraser);
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			// KeyManager::GetInstance()->PreventEvent(1);
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}