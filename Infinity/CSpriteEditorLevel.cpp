#include "pch.h"
#include "CSpriteEditorLevel.h"
#include "KeyManager.h"
#include "AssetManager.h"
#include "TaskManager.h"

#include "CGameObject.h"
#include "CTransform.h"
#include "CCamera.h"

#include "CTexture.h"
#include "CSprite.h"

#include "CGrid.h"
#include "CTilemap.h"
#include "CTile.h"

CSpriteEditorLevel::CSpriteEditorLevel()
	: m_hMenu(nullptr)
    , m_hDialog(nullptr)
    , m_Texture(nullptr)
    , m_Sprites{}
    , m_SelectedSpriteIndex(-1)
    , m_Camera(nullptr)
{
	m_hMenu = LoadMenu(nullptr, (LPCWSTR)IDR_Menu_SpriteEditor);
	assert(m_hMenu);
}

CSpriteEditorLevel::~CSpriteEditorLevel()
{
}

void CSpriteEditorLevel::BeginPlay()
{
    CLevel::BeginPlay();

    CGameObject* pCamera = new CGameObject;
    m_Camera = pCamera->AddComponent<CCamera>();
    m_Camera->SetTarget(pCamera);
    AddObject(pCamera, LayerType::CAMERA);


    if (!m_Texture)
        return;
}

void CSpriteEditorLevel::Tick()
{
    Vec2 vResolution = CEngine::GetInstance()->GetResolution();
    Vec2 vMousePos = KeyManager::GetInstance()->GetMousePos();
    int previousSelectedSpriteIndex = m_SelectedSpriteIndex; // 이전 선택된 스프라이트 인덱스 저장

    for (size_t i = 0; i < m_Sprites.size(); i++)
    {
        if (nullptr != m_Sprites[i])
        {
            Vec2 vOrigin = Vec2((vResolution.x - m_Texture->GetWidth()) / 2, (vResolution.y - m_Texture->GetHeight()) / 2);
            Vec2 vLeftTop = m_Sprites[i]->GetLeftTop();     // 스프라이트의 위치
            Vec2 vSize = m_Sprites[i]->GetSize();           // 스프라이트의 크기

            // 마우스가 해당 스프라이트 위에 있는지 확인
            bool IsMouseOnSprite = (vMousePos.x >= vOrigin.x + vLeftTop.x &&
                vMousePos.x <= vOrigin.x + vLeftTop.x + vSize.x &&
                vMousePos.y >= vOrigin.y + vLeftTop.y &&
                vMousePos.y <= vOrigin.y + vLeftTop.y + vSize.y);

            // 마우스 클릭 여부와 OnMouse 상태에 따라 색상 결정
            if (KeyManager::GetInstance()->GetButtonDown(Key::LBUTTON) && IsMouseOnSprite)
            {
                m_SelectedSpriteIndex = i; // 클릭 시 선택된 스프라이트 인덱스 저장
            }

            // 선택 상태에 따라 색상 결정
            if (m_SelectedSpriteIndex == static_cast<int>(i))
            {
                DrawDebugRectLT(vOrigin + vLeftTop, vSize, PEN_TYPE::BLUE); // 선택된 경우 파란색

                // 선택된 스프라이트가 변경된 경우에만 다이얼로그 표시
                if (previousSelectedSpriteIndex != m_SelectedSpriteIndex)
                {
                    ShowSpriteInfoDialog(m_Sprites[i]);
                }
            }
            else
            {
                DrawDebugRectLT(vOrigin + vLeftTop, vSize, PEN_TYPE::GREEN); // 선택되지 않은 경우 녹색
            }
        }
    }
}

void CSpriteEditorLevel::Render(HDC _Hdc)
{
    if (!m_Texture)
        return;

    Vec2 vResolution = CEngine::GetInstance()->GetResolution();
    Vec2 vOrigin((vResolution.x - m_Texture->GetWidth()) / 2, (vResolution.y - m_Texture->GetHeight()) / 2);
    Vec2 vLeftTop = m_Camera->GetViewPos(vOrigin);
    DrawCheckeredPattern(_Hdc, m_Texture->GetWidth(), m_Texture->GetHeight());

    BLENDFUNCTION blend = {};
    blend.BlendOp = AC_SRC_OVER;
    blend.BlendFlags = 0;
    blend.SourceConstantAlpha = 255; // 추가 알파값
    blend.AlphaFormat = AC_SRC_ALPHA; // 알파 채널의 알파값을 투명도로 사용

    AlphaBlend(_Hdc
        , vLeftTop.x
        , vLeftTop.y
        , m_Texture->GetWidth()
        , m_Texture->GetHeight()
        , m_Texture->GetDC()
        , 0, 0
        , m_Texture->GetWidth(), m_Texture->GetHeight()
        , blend);
}

void CSpriteEditorLevel::OnEnter()
{
	// 메뉴바를 윈도우에 부착
	SetMenu(CEngine::GetInstance()->GetMainWnd(), m_hMenu);
	Vec2 vResolutionHD = Vec2(1280, 720);
	CEngine::GetInstance()->ChangeWindowSize(int(vResolutionHD.x), int(vResolutionHD.y));

	BeginPlay();
}

void CSpriteEditorLevel::OnExit()
{
}

void CSpriteEditorLevel::LoadFile()
{
    Revert();
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
        SetTexture(pTex);
    }
}

void CSpriteEditorLevel::GridByCellSize(Vec2 _Size, Vec2 _LeftTop, Vec2 _Padding)
{
    wstring strName = m_Texture->GetName() + L"_%d";

    // 아틀라스의 높이와 너비를 가져옵니다.
    int atlasWidth = m_Texture->GetWidth();
    int atlasHeight = m_Texture->GetHeight();

    // 최대 행과 열 수를 계산합니다.
    m_Rows = atlasHeight / (_Size.y + _Padding.y);
    m_Columns = atlasWidth / (_Size.x + _Padding.x);

    for (int i = 0; i < m_Rows; ++i)
    {
        for (int j = 0; j < m_Columns; ++j)
        {
            wchar_t szKey[255] = {};
            int index = i * m_Columns + j;
            swprintf_s(szKey, 255, strName.c_str(), index);

            Vec2 vLeftTop((float)j * (_Size.x + _Padding.x) + _LeftTop.x, (float)i * (_Size.y + _Padding.y) + _LeftTop.y);

            // 스프라이트 생성
            CSprite* pSprite = AssetManager::GetInstance()->CreateSprite(szKey
                , m_Texture
                , vLeftTop
                , _Size
                , Vec2(0.f, 0.f));

            // 상대 경로 설정
            wstring Path = L"Sprite\\";
            Path = Path + szKey + L".sprite";
            pSprite->SetRelativePath(Path);

            // Sprite Mode 설정
            // pSprite->SetSpriteMode(SpriteMode::SINGLE);

            m_Sprites.push_back(pSprite);
        }
    }
}


#include "CPrefab.h"
void CSpriteEditorLevel::CreateTilePalette()
{
    CGameObject* pMap = new CGameObject;
    pMap->SetName(L"Map_01");
    CGrid* pGird = pMap->AddComponent<CGrid>();
    pGird->SetTileSize(32);
    pGird->SetColumn(m_Columns);
    pGird->SetRow(m_Rows);

    CGameObject* pLayer = new CGameObject;
    pLayer->SetName(L"Layer");
    CTilemap* pTilemap = pLayer->AddComponent<CTilemap>();
    pMap->AddChild(pLayer);

    // Tile 저장
    wstring textureName = m_Texture->GetName();
    wstring tileName = textureName + L"_%d";
    for (size_t i = 0; i < m_Sprites.size(); ++i)
    {
        // Tile
        wchar_t szKey[255] = {};
        swprintf_s(szKey, 255, tileName.c_str(), i);
        CTile* pTile = AssetManager::GetInstance()->CreateTile(szKey, m_Sprites[i]);

        wstring Path = L"Tile\\";
        Path = Path + szKey + L".tile";
        pTile->SetRelativePath(Path);
        pTile->Save(Path);

        int Col = i / m_Columns;
        int Row = i % m_Columns;
        pTilemap->AddTile(Col, Row, pTile->GetKey());
    }

    // Prefab 생성
    CPrefab* pPrefab = new CPrefab;
    pPrefab->SetObject(pMap);
    wstring relativePath = L"Prefab\\" + pMap->GetName();


    pPrefab->SetName(pMap->GetName());
    pPrefab->SetKey(pMap->GetName());
    pPrefab->SetRelativePath(relativePath);
    pPrefab->Save(relativePath);

    // delete pTilemap?
}

void CSpriteEditorLevel::Revert()
{
    m_Texture = nullptr;
    Delete_Vec(m_Sprites); // TODO : ~AssetManager() 에서 오류 발생
    m_SelectedSpriteIndex = -1;
    m_PixelSize = Vec2(0.f, 0.f);
    m_Offset = Vec2(0.f, 0.f);
    m_Padding = Vec2(0.f, 0.f);

    if (m_hDialog)
        EndDialog(m_hDialog, IDOK);
}

void CSpriteEditorLevel::Apply()
{
    if (m_Sprites.size() > 0)
    {
        for (int i = 0; i < m_Sprites.size(); ++i)
        {
            m_Sprites[i]->Save(m_Sprites[i]->GetRelativePath());
        }
    }
}

LRESULT CALLBACK SpriteInfoProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
void CSpriteEditorLevel::ShowSpriteInfoDialog(CSprite* _Sprite)
{
    if (!_Sprite)
        return;

    HINSTANCE hInstance = CEngine::GetInstance()->GetHInst();
    HWND hWnd = CEngine::GetInstance()->GetMainWnd();

    if (!m_hDialog)
    {
        m_hDialog = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_DIALOG_SpriteInfo), hWnd, SpriteInfoProc);

        // 대화 상자의 크기를 가져옴
        RECT dialogRect;
        GetWindowRect(m_hDialog, &dialogRect);
        int dialogWidth = dialogRect.right - dialogRect.left;
        int dialogHeight = dialogRect.bottom - dialogRect.top;

        // 화면의 크기를 가져옴
        RECT windowRect;
        GetWindowRect(hWnd, &windowRect);
        int windowWidth = windowRect.right - windowRect.left;
        int windowHeight = windowRect.bottom - windowRect.top;

        // 대화 상자의 위치 계산 (우측 하단에 30px 패딩)
        int posX = windowWidth - dialogWidth - 30;
        int posY = windowHeight - dialogHeight - 30;

        // 대화 상자의 위치 설정
        SetWindowPos(m_hDialog, NULL, posX, posY, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
    }

    // 스프라이트 정보를 Dialog에 설정
    HWND hEditControl = GetDlgItem(m_hDialog, IDC_SPRITEINFO_EDIT_NAME);
    if (hEditControl && _Sprite)
    {
        wstring spriteName = _Sprite->GetName();
        SetWindowText(hEditControl, spriteName.c_str());
    }

    hEditControl = GetDlgItem(m_hDialog, IDC_SPRITEINFO_EDIT_LEFTTOP_X);
    if (hEditControl && _Sprite)
    {
        int LeftTopX = _Sprite->GetLeftTop().x;
        wstring LeftTopXStr = std::to_wstring(LeftTopX);
        SetWindowText(hEditControl, LeftTopXStr.c_str());
    }

    hEditControl = GetDlgItem(m_hDialog, IDC_SPRITEINFO_EDIT_LEFTTOP_Y);
    if (hEditControl && _Sprite)
    {
        int LeftTopY = _Sprite->GetLeftTop().y;
        wstring LeftTopYStr = std::to_wstring(LeftTopY);
        SetWindowText(hEditControl, LeftTopYStr.c_str());
    }

    hEditControl = GetDlgItem(m_hDialog, IDC_SPRITEINFO_EDIT_SIZE_X);
    if (hEditControl && _Sprite)
    {
        int Width = _Sprite->GetSize().x;
        wstring WidthStr = std::to_wstring(Width);
        SetWindowText(hEditControl, WidthStr.c_str());
    }

    hEditControl = GetDlgItem(m_hDialog, IDC_SPRITEINFO_EDIT_SIZE_Y);
    if (hEditControl && _Sprite)
    {
        int Height = _Sprite->GetSize().x;
        wstring HeightStr = std::to_wstring(Height);
        SetWindowText(hEditControl, HeightStr.c_str());
    }

    hEditControl = GetDlgItem(m_hDialog, IDC_SPRITEINFO_EDIT_BORDER_L);
    if (hEditControl && _Sprite)
    {
        int BorderL = _Sprite->GetBorder().Left;
        wstring BorderLStr = std::to_wstring(BorderL);
        SetWindowText(hEditControl, BorderLStr.c_str());
    }

    hEditControl = GetDlgItem(m_hDialog, IDC_SPRITEINFO_EDIT_BORDER_T);
    if (hEditControl && _Sprite)
    {
        int BorderT = _Sprite->GetBorder().Left;
        wstring BorderTStr = std::to_wstring(BorderT);
        SetWindowText(hEditControl, BorderTStr.c_str());
    }

    hEditControl = GetDlgItem(m_hDialog, IDC_SPRITEINFO_EDIT_BORDER_R);
    if (hEditControl && _Sprite)
    {
        int BorderR = _Sprite->GetBorder().Left;
        wstring BorderRStr = std::to_wstring(BorderR);
        SetWindowText(hEditControl, BorderRStr.c_str());
    }
    
    hEditControl = GetDlgItem(m_hDialog, IDC_SPRITEINFO_EDIT_BORDER_B);
    if (hEditControl && _Sprite)
    {
        int BorderB = _Sprite->GetBorder().Left;
        wstring BorderBStr = std::to_wstring(BorderB);
        SetWindowText(hEditControl, BorderBStr.c_str());
    }

    ShowWindow(m_hDialog, SW_SHOW);
}