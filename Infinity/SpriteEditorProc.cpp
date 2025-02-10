#include "pch.h"
#include "CSpriteEditorLevel.h"
#include "KeyManager.h"
#include "LevelManager.h"
#include "CSprite.h"

INT_PTR CALLBACK GridByCellSizeProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == ID_Button_Slice)
        {
            // TODO : Slice Sprite
            int PixelSizeX = GetDlgItemInt(hDlg, IDC_EDIT_SizeX, nullptr, true);
            int PixelSizeY = GetDlgItemInt(hDlg, IDC_EDIT_SizeY, nullptr, true);

            CSpriteEditorLevel* pLevel = dynamic_cast<CSpriteEditorLevel*>(LevelManager::GetInstance()->GetCurrentLevel());
            assert(pLevel);

            pLevel->GridByCellSize(Vec2(PixelSizeX, PixelSizeY), Vec2(0.f, 0.f), Vec2(0.f, 0.f));
            // KeyManager::GetInstance()->PreventEvent(1);
            EndDialog(hDlg, LOWORD(wParam));

            return (INT_PTR)TRUE;
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

INT_PTR CALLBACK NineSlicingProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == ID_Button_9Slice)
        {
            // TODO : 9-Slice Sprite

            // KeyManager::GetInstance()->PreventEvent(1);
            EndDialog(hDlg, LOWORD(wParam));

            return (INT_PTR)TRUE;
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

INT_PTR CALLBACK SpriteInfoProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDC_SPRITEINFO_BUTTON_APPLY)
        {
            CSpriteEditorLevel* pLevel = dynamic_cast<CSpriteEditorLevel*>(LevelManager::GetInstance()->GetCurrentLevel());
            assert(pLevel);

            // 기존 Sprite 상대 경로
            CSprite* pSelectedSprite = pLevel->GetSelectedSpriteInfo();
            wstring prevSpritePath = pSelectedSprite->GetRelativePath();

            // 기존 파일 삭제
            /*if (std::filesystem::exists(prevSpritePath))
            {
                std::filesystem::remove(prevSpritePath);
            }*/

            HWND hEditControl = GetDlgItem(hDlg, IDC_SPRITEINFO_EDIT_NAME);
            if (hEditControl)
            {
                const int bufferSize = 256;
                wchar_t windowTitle[bufferSize];
                int length = GetWindowText(hEditControl, windowTitle, bufferSize);
                pSelectedSprite->SetName(windowTitle);
                pSelectedSprite->SetKey(windowTitle);
            }

            // TODO : LeftTop, Size

            hEditControl = GetDlgItem(hDlg, IDC_SPRITEINFO_EDIT_BORDER_L);
            if (hEditControl)
            {
                const int bufferSize = 256;
                wchar_t windowTitle[bufferSize];
                int length = GetWindowText(hEditControl, windowTitle, bufferSize);
                if (length > 0)
                {
                    UINT value = static_cast<UINT>(std::wcstoul(windowTitle, nullptr, 10));
                    pSelectedSprite->SetBorder(value
                        , pSelectedSprite->GetBorder().Right
                        , pSelectedSprite->GetBorder().Top
                        , pSelectedSprite->GetBorder().Bottom);
                }
            }

            hEditControl = GetDlgItem(hDlg, IDC_SPRITEINFO_EDIT_BORDER_R);
            if (hEditControl)
            {
                const int bufferSize = 256;
                wchar_t windowTitle[bufferSize];
                int length = GetWindowText(hEditControl, windowTitle, bufferSize);
                if (length > 0)
                {
                    UINT value = static_cast<UINT>(std::wcstoul(windowTitle, nullptr, 10));
                    pSelectedSprite->SetBorder(pSelectedSprite->GetBorder().Left
                        , value
                        , pSelectedSprite->GetBorder().Top
                        , pSelectedSprite->GetBorder().Bottom);
                }
            }

            hEditControl = GetDlgItem(hDlg, IDC_SPRITEINFO_EDIT_BORDER_T);
            if (hEditControl)
            {
                const int bufferSize = 256;
                wchar_t windowTitle[bufferSize];
                int length = GetWindowText(hEditControl, windowTitle, bufferSize);
                if (length > 0)
                {
                    UINT value = static_cast<UINT>(std::wcstoul(windowTitle, nullptr, 10));
                    pSelectedSprite->SetBorder(pSelectedSprite->GetBorder().Left
                        , pSelectedSprite->GetBorder().Right
                        , value
                        , pSelectedSprite->GetBorder().Bottom);
                }
            }

            hEditControl = GetDlgItem(hDlg, IDC_SPRITEINFO_EDIT_BORDER_B);
            if (hEditControl)
            {
                const int bufferSize = 256;
                wchar_t windowTitle[bufferSize];
                int length = GetWindowText(hEditControl, windowTitle, bufferSize);
                if (length > 0)
                {
                    UINT value = static_cast<UINT>(std::wcstoul(windowTitle, nullptr, 10));
                    pSelectedSprite->SetBorder(pSelectedSprite->GetBorder().Left
                        , pSelectedSprite->GetBorder().Right
                        , pSelectedSprite->GetBorder().Top
                        , value);
                }
            }

            // 상대 경로 재설정
            wstring Path = L"Sprite\\";
            Path = Path + pSelectedSprite->GetKey() + L".sprite";
            pSelectedSprite->SetRelativePath(Path);
            // pSelectedSprite->Save(Path);

            // KeyManager::GetInstance()->PreventEvent(1);
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}