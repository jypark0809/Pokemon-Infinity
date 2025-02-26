#include "pch.h"
#include "Infinity.h"
#include <crtdbg.h>
#include "LevelManager.h"
#include "CSpriteEditorLevel.h"
#include "CTilemapEditorLevel.h"

// 전역 변수
HINSTANCE   g_hInst = nullptr;
HWND        g_hWnd = nullptr;

// 전방 선언
ATOM                MyRegisterClass(HINSTANCE hInstance, const wchar_t* name, WNDPROC proc);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{

    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    // 1) 윈도우 창 정보 등록
    MyRegisterClass(hInstance, L"Infinity", WndProc);
    MyRegisterClass(hInstance, L"TilePalette", TilePaletteProc);

    // 2) 윈도우 창 생성
    if (!InitInstance (hInstance, nCmdShow))
        return FALSE;

    // 3) CEngine 초기화
    if (FAILED(CEngine::GetInstance()->Init(g_hWnd, 512, 384)))
    {
        MessageBox(nullptr, L"CEngine Init Failed", L"Error", MB_OK);
        return 0;
    }

    // 단축키 테이블
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_INFINITY));

    MSG msg;

    // 3) 메인 루프
    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                break;

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }

        else
        {
            // 게임
            CEngine::GetInstance()->Progress(); // 1 Frame
        }
    }

    return (int) msg.wParam;
}

//  용도: 창 클래스를 등록합니다.
ATOM MyRegisterClass(HINSTANCE hInstance, const wchar_t* name, WNDPROC proc)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = proc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_INFINITY));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = nullptr;
    wcex.lpszClassName  = name;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//   함수: InitInstance(HINSTANCE, int)
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    g_hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.
    CEngine::GetInstance()->SetHInst(hInstance);

   HWND hWnd = CreateWindowW(L"Infinity", L"Pokémon Infinity", WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   g_hWnd = hWnd;

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case ID_FILE_OPENFILE:
            {
                // [Sprite Editor] - [File] - [Open File]
                CSpriteEditorLevel* pSpriteEditor = dynamic_cast<CSpriteEditorLevel*>(LevelManager::GetInstance()->GetCurrentLevel());
                assert(pSpriteEditor);
                pSpriteEditor->LoadFile();
            }
                break;
            case ID_SLICE_GRIDBYCELLSIZE:
                // [Sprite Editor] - [Slice] - [Grid By Cell Size]
                DialogBox(g_hInst, MAKEINTRESOURCE(IDD_Dialog_GridByCellSize), hWnd, GridByCellSizeProc);
                break;
            case ID_SLICE_9Slicing:
                // [Sprite Editor] - [Slice] - [9-Slicing Sprite]
                DialogBox(g_hInst, MAKEINTRESOURCE(IDD_Dialog_9Slice), hWnd, NineSlicingProc);
                break;
            case ID_APPLY_REVERT:
            {
                // [Sprite Editor] - [Apply] - [Revert]
                CSpriteEditorLevel* pSpriteEditor = dynamic_cast<CSpriteEditorLevel*>(LevelManager::GetInstance()->GetCurrentLevel());
                assert(pSpriteEditor);
                pSpriteEditor->Revert();
            }
                break;
            case ID_APPLY_APPLY:
            {
                // [Sprite Editor] - [Apply] - [Apply]
                CSpriteEditorLevel* pSpriteEditor = dynamic_cast<CSpriteEditorLevel*>(LevelManager::GetInstance()->GetCurrentLevel());
                assert(pSpriteEditor);
                pSpriteEditor->Apply();
            }
                break;
            case ID_TILE_CREATETILEPALETTE:
            {
                // [Sprite Editor] - [Tile] - [Create Tile Palette]
                CSpriteEditorLevel* pSpriteEditor = dynamic_cast<CSpriteEditorLevel*>(LevelManager::GetInstance()->GetCurrentLevel());
                assert(pSpriteEditor);
                pSpriteEditor->CreateTilePalette();
            }
                break;
            case ID_FILE_SAVE:
            {
                // [Tilemap Editor] - [File] - [Save]
                CTilemapEditorLevel* pTimemapEditor = dynamic_cast<CTilemapEditorLevel*>(LevelManager::GetInstance()->GetCurrentLevel());
                assert(pTimemapEditor);
                pTimemapEditor->SaveMap();
            }
                break;
            case ID_FILE_LOAD:
            {
                // [Tilemap Editor] - [File] - [LOAD]
                CTilemapEditorLevel* pTimemapEditor = dynamic_cast<CTilemapEditorLevel*>(LevelManager::GetInstance()->GetCurrentLevel());
                assert(pTimemapEditor);
                pTimemapEditor->LoadMap();
            }
                break;
            case ID_GRID_CREATEGRID:
            {
                // [Tilemap Editor] - [Grid] - [Create Grid]
                DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG_CREATEGRID), hWnd, CreateGirdProc);
                break;
            }
            break;
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
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
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