#include "pch.h"
#include "CFlipbookEditorLevel.h"
#include "TimeManager.h"
#include "AssetManager.h"
#include "CTexture.h"
#include "CSprite.h"
#include "CFlipbook.h"

INT_PTR CALLBACK FlipbookEditorDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

CFlipbookEditorLevel::CFlipbookEditorLevel()
	: m_hDialog(nullptr)
    , m_hListBox(nullptr)
    , m_Sprites{}
    , m_Index(0)
    , m_Play(false)
{
}

CFlipbookEditorLevel::~CFlipbookEditorLevel()
{
}

void CFlipbookEditorLevel::BeginPlay()
{
	m_hDialog = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG_FlipbookEditor), NULL, FlipbookEditorDlgProc);
    m_hListBox = GetDlgItem(m_hDialog, IDC_FLIPBOOKEDITOR_LIST_SPRITES);
    ShowWindow(m_hDialog, SW_SHOW);
}

void CFlipbookEditorLevel::Tick()
{
    
}

void CFlipbookEditorLevel::FinalTick()
{
    if (!m_Play)
        return;

    m_Time += DT;

    if (m_Sprites[m_Index]->GetDuration() < m_Time)
    {
        m_Time -= m_Sprites[m_Index]->GetDuration(); // m_Duration(초)보다 더 지난 시간 보정
        if (m_Index < m_Sprites.size() - 1)
        {
            m_Index++;
            UpdateSpriteInfo(m_hDialog, m_Index);
        }
        else
            m_Index = 0;
    }
}

void CFlipbookEditorLevel::Render(HDC _hdc)
{
    if (m_Sprites.empty())
        return;

    CSprite* pSprite = m_Sprites[m_Index];
    Vec2 vResolution = CEngine::GetInstance()->GetResolution();
    Vec2 OriginDest = Vec2((vResolution.x - pSprite->GetSize().x) / 2, (vResolution.y - pSprite->GetSize().y) / 2);

    pSprite->Render(_hdc, OriginDest);
}

void CFlipbookEditorLevel::OnEnter()
{
	Vec2 vResolutionHD = Vec2(1280, 720);
	CEngine::GetInstance()->ChangeWindowSize(int(vResolutionHD.x), int(vResolutionHD.y));

    CLevel::OnEnter();
}

void CFlipbookEditorLevel::OnExit()
{
}

void CFlipbookEditorLevel::AddSprite()
{
    // 파일 경로 문자열
    wchar_t szFilePath[255] = {};
    wstring InitialDir = CONTENT_PATH.wstring() + L"\\Sprite";

    OPENFILENAME Desc = {};
    Desc.lStructSize = sizeof(OPENFILENAME);
    Desc.hwndOwner = nullptr;
    Desc.lpstrFile = szFilePath; // 최종적으로 고른 경로를 받아낼 목적지
    Desc.nMaxFile = 255;
    Desc.lpstrFilter = L"Sprite Files\0*.sprite\0All Files (*.*)\0*.*";
    Desc.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
    Desc.lpstrInitialDir = InitialDir.c_str();

    if (GetOpenFileName(&Desc))
    {
        fs::path filePath(szFilePath);
        wstring fullPath = filePath.wstring();
        wstring relativePath = fullPath.substr(fullPath.find(L"Sprite\\"));
        wstring fileName = filePath.stem().wstring(); // .sprite 제외

        CSprite* pSprite = AssetManager::GetInstance()->LoadSprite(fileName, relativePath);
        m_Sprites.push_back(pSprite);

        // Sprite Info 업데이트
        UpdateSpriteInfo(m_hDialog, m_Index);

        // List Box에 추가
        wstring key = pSprite->GetKey();
        SendMessage(m_hListBox, LB_ADDSTRING, 0, (LPARAM)key.c_str());
    }
}

void CFlipbookEditorLevel::DeleteSprite()
{
}

void CFlipbookEditorLevel::Play()
{
    m_Play = true;
}

void CFlipbookEditorLevel::Stop()
{
    m_Play = false;
}

void CFlipbookEditorLevel::NextFrame()
{
    if (m_Sprites.empty())
        return;

    if (m_Index < m_Sprites.size() - 1)
        ++m_Index;
    else
        m_Index = 0;
}

void CFlipbookEditorLevel::PrevFrame()
{
    if (m_Sprites.empty())
        return;

    if (m_Index <= 0)
        m_Index = m_Sprites.size() - 1;
    else
        --m_Index;
}

void CFlipbookEditorLevel::Apply()
{
    m_Sprites[m_Index]->Save(m_Sprites[m_Index]->GetRelativePath());
}

void CFlipbookEditorLevel::SaveFlipbook()
{
    // 파일 경로 문자열
    wchar_t szFilePath[255] = {};
    wstring InitialDir = CONTENT_PATH.wstring() + L"\\Flipbook";

    OPENFILENAME Desc = {};
    Desc.lStructSize = sizeof(OPENFILENAME);
    Desc.hwndOwner = nullptr;
    Desc.lpstrFile = szFilePath;	// 최종적으로 고른 경로를 받아낼 목적지
    Desc.nMaxFile = 255;
    Desc.lpstrFilter = L"Flipbook Files\0*.flip\0All Files (*.*)\0*.*";
    Desc.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
    Desc.lpstrInitialDir = InitialDir.c_str();

    if (GetSaveFileName(&Desc))
    {
        fs::path filePath(szFilePath);
        wstring fileName = filePath.stem().wstring();
        CFlipbook* pFlipbook = AssetManager::GetInstance()->CreateFlipbook(fileName, m_Sprites);
        wstring FlipBookPath = L"Flipbook\\" + fileName + L".flip";
        pFlipbook->SetRelativePath(FlipBookPath);
        pFlipbook->Save(FlipBookPath);
    }
}

void CFlipbookEditorLevel::UpdateSpriteInfo(HWND _hDlg, UINT _Index)
{
    CSprite* pSprite = m_Sprites[_Index];

    // Sprite Index
    HWND hEditControl = GetDlgItem(_hDlg, IDC_FLIPBOOKEDITOR_EDIT_INDEX);
    if (hEditControl)
    {
        UINT Index = _Index;
        wstring IndexStr = std::to_wstring(Index);
        SetWindowText(hEditControl, IndexStr.c_str());
    }

    // Sprite Name
    hEditControl = GetDlgItem(_hDlg, IDC_FLIPBOOKEDITOR_EDIT_NAME);
    if (hEditControl)
    {
        wstring Name = pSprite->GetName();
        SetWindowText(hEditControl, Name.c_str());
    }

    // Duration
    hEditControl = GetDlgItem(_hDlg, IDC_FLIPBOOKEDITOR_EDIT_DURATION);
    if (hEditControl)
    {
        float Duration = pSprite->GetDuration();
        wstring DurationStr = std::to_wstring(Duration);
        SetWindowText(hEditControl, DurationStr.c_str());
    }

    // Offset
    hEditControl = GetDlgItem(_hDlg, IDC_FLIPBOOKEDITOR_EDIT_OFFSET_X);
    if (hEditControl)
    {
        Vec2 Offset = pSprite->GetOffset();
        wstring OffsetXStr = std::to_wstring(Offset.x);
        SetWindowText(hEditControl, OffsetXStr.c_str());
    }

    hEditControl = GetDlgItem(_hDlg, IDC_FLIPBOOKEDITOR_EDIT_OFFSET_Y);
    if (hEditControl)
    {
        Vec2 Offset = pSprite->GetOffset();
        wstring OffsetYStr = std::to_wstring(Offset.y);
        SetWindowText(hEditControl, OffsetYStr.c_str());
    }
}