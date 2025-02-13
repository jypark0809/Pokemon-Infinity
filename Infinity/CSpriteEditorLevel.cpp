#include "pch.h"
#include "CSpriteEditorLevel.h"
#include "KeyManager.h"
#include "AssetManager.h"
#include "TaskManager.h"
#include "CTexture.h"
#include "CSprite.h"


CSpriteEditorLevel::CSpriteEditorLevel()
	: m_hMenu(nullptr)
    , m_hDialog(nullptr)
    , m_Texture(nullptr)
    , m_Sprites{}
    , m_SelectedSpriteIndex(-1)
{
	m_hMenu = LoadMenu(nullptr, (LPCWSTR)IDR_Menu_SpriteEditor);
	assert(m_hMenu);
}

CSpriteEditorLevel::~CSpriteEditorLevel()
{
}

void CSpriteEditorLevel::BeginPlay()
{
    if (!m_Texture)
        return;
}

void CSpriteEditorLevel::Tick()
{
    Vec2 vResolution = CEngine::GetInstance()->GetResolution();
    Vec2 vMousePos = KeyManager::GetInstance()->GetMousePos();
    int previousSelectedSpriteIndex = m_SelectedSpriteIndex; // ���� ���õ� ��������Ʈ �ε��� ����

    for (size_t i = 0; i < m_Sprites.size(); i++)
    {
        if (nullptr != m_Sprites[i])
        {
            Vec2 vOrigin = Vec2((vResolution.x - m_Texture->GetWidth()) / 2, (vResolution.y - m_Texture->GetHeight()) / 2);
            Vec2 vLeftTop = m_Sprites[i]->GetLeftTop();     // ��������Ʈ�� ��ġ
            Vec2 vSize = m_Sprites[i]->GetSize();           // ��������Ʈ�� ũ��

            // ���콺�� �ش� ��������Ʈ ���� �ִ��� Ȯ��
            bool OnMouse = (vMousePos.x >= vOrigin.x + vLeftTop.x &&
                vMousePos.x <= vOrigin.x + vLeftTop.x + vSize.x &&
                vMousePos.y >= vOrigin.y + vLeftTop.y &&
                vMousePos.y <= vOrigin.y + vLeftTop.y + vSize.y);

            // ���콺 Ŭ�� ���ο� OnMouse ���¿� ���� ���� ����
            if (KeyManager::GetInstance()->GetButtonDown(Key::LBUTTON) && OnMouse)
            {
                m_SelectedSpriteIndex = i; // Ŭ�� �� ���õ� ��������Ʈ �ε��� ����
            }

            // ���� ���¿� ���� ���� ����
            if (m_SelectedSpriteIndex == static_cast<int>(i))
            {
                DrawDebugRectLT(vOrigin + vLeftTop, vSize, PEN_TYPE::BLUE); // ���õ� ��� �Ķ���

                // ���õ� ��������Ʈ�� ����� ��쿡�� ���̾�α� ǥ��
                if (previousSelectedSpriteIndex != m_SelectedSpriteIndex)
                {
                    ShowSpriteInfoDialog(m_Sprites[i]);
                }
            }
            else
            {
                DrawDebugRectLT(vOrigin + vLeftTop, vSize, PEN_TYPE::GREEN); // ���õ��� ���� ��� ���
            }
        }
    }
}

void CSpriteEditorLevel::Render(HDC _Hdc)
{
    if (!m_Texture)
        return;

    Vec2 vResolution = CEngine::GetInstance()->GetResolution();
    DrawCheckeredPattern(_Hdc, m_Texture->GetWidth(), m_Texture->GetHeight());

    BLENDFUNCTION blend = {};
    blend.BlendOp = AC_SRC_OVER;
    blend.BlendFlags = 0;
    blend.SourceConstantAlpha = 255; // �߰� ���İ�
    blend.AlphaFormat = AC_SRC_ALPHA; // ���� ä���� ���İ��� ������ ���

    AlphaBlend(_Hdc
        , (vResolution.x - m_Texture->GetWidth()) / 2
        , (vResolution.y - m_Texture->GetHeight()) / 2
        , m_Texture->GetWidth()
        , m_Texture->GetHeight()
        , m_Texture->GetDC()
        , 0, 0
        , m_Texture->GetWidth(), m_Texture->GetHeight()
        , blend);
}

void CSpriteEditorLevel::OnEnter()
{
	// �޴��ٸ� �����쿡 ����
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
    wstring InitialDir = CONTENT_PATH.wstring() + L"\\Texture\\Characters";

    // ���� ��� ���ڿ�
    wchar_t szFilePath[255] = {};
    OPENFILENAME Desc = {};
    Desc.lStructSize = sizeof(OPENFILENAME);
    Desc.hwndOwner = nullptr;
    Desc.lpstrFile = szFilePath; // ���������� �� ��θ� �޾Ƴ� ������
    Desc.nMaxFile = 255;
    Desc.lpstrFilter = L"�׸� ����\0*.png;*.bmp\0��� ����(*.*)\0*.*";
    Desc.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
    Desc.lpstrInitialDir = InitialDir.c_str();

    if (GetOpenFileName(&Desc))
    {
        fs::path filePath(szFilePath);
        wstring fileName = filePath.stem().wstring(); // .png ����
        CTexture* pTex = AssetManager::GetInstance()->LoadTexture(fileName, szFilePath);
        pTex->SetName(fileName);
        SetTexture(pTex);
    }
}

void CSpriteEditorLevel::GridByCellSize(Vec2 _Size, Vec2 _LeftTop, Vec2 _Padding)
{
    wstring strName = m_Texture->GetName() + L"_%d";

    // ��Ʋ���� ���̿� �ʺ� �����ɴϴ�.
    int atlasWidth = m_Texture->GetWidth();
    int atlasHeight = m_Texture->GetHeight();

    // �ִ� ��� �� ���� ����մϴ�.
    int maxRows = atlasHeight / (_Size.y + _Padding.y);
    int maxCols = atlasWidth / (_Size.x + _Padding.x);

    for (int i = 0; i < maxRows; ++i)
    {
        for (int j = 0; j < maxCols; ++j)
        {
            wchar_t szKey[255] = {};
            int index = i * maxCols + j;
            swprintf_s(szKey, 255, strName.c_str(), index);

            Vec2 vLeftTop((float)j * (_Size.x + _Padding.x) + _LeftTop.x, (float)i * (_Size.y + _Padding.y) + _LeftTop.y);

            // ��������Ʈ ����
            CSprite* pSprite = AssetManager::GetInstance()->CreateSprite(szKey
                , m_Texture
                , vLeftTop
                , _Size
                , Vec2(0.f, 0.f));

            // ��� ��� ����
            wstring Path = L"Sprite\\";
            Path = Path + szKey + L".sprite";
            pSprite->SetRelativePath(Path);

            // Sprite Mode ����
            // pSprite->SetSpriteMode(SpriteMode::SINGLE);

            m_Sprites.push_back(pSprite);
        }
    }
}

void CSpriteEditorLevel::Revert()
{
    m_Texture = nullptr;
    Delete_Vec(m_Sprites); // TODO : ~AssetManager() ���� ���� �߻�
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

        // ��ȭ ������ ũ�⸦ ������
        RECT dialogRect;
        GetWindowRect(m_hDialog, &dialogRect);
        int dialogWidth = dialogRect.right - dialogRect.left;
        int dialogHeight = dialogRect.bottom - dialogRect.top;

        // ȭ���� ũ�⸦ ������
        RECT windowRect;
        GetWindowRect(hWnd, &windowRect);
        int windowWidth = windowRect.right - windowRect.left;
        int windowHeight = windowRect.bottom - windowRect.top;

        // ��ȭ ������ ��ġ ��� (���� �ϴܿ� 30px �е�)
        int posX = windowWidth - dialogWidth - 30;
        int posY = windowHeight - dialogHeight - 30;

        // ��ȭ ������ ��ġ ����
        SetWindowPos(m_hDialog, NULL, posX, posY, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
    }

    // ��������Ʈ ������ Dialog�� ����
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