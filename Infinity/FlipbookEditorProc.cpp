#include "pch.h"
#include "AssetManager.h"
#include "LevelManager.h"
#include "CFlipbookEditorLevel.h"
#include "CSprite.h"

INT_PTR CALLBACK FlipbookEditorDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDC_FLIPBOOKEDITOR_BUTTON_ADD)
        {
            CFlipbookEditorLevel* pFlipbookEditor = dynamic_cast<CFlipbookEditorLevel*>(LevelManager::GetInstance()->GetCurrentLevel());
            assert(pFlipbookEditor);
            pFlipbookEditor->AddSprite();

            return (INT_PTR)TRUE;
        }
        else if (LOWORD(wParam) == IDC_FLIPBOOKEDITOR_BUTTON_NEXT)
        {
            CFlipbookEditorLevel* pFlipbookEditor = dynamic_cast<CFlipbookEditorLevel*>(LevelManager::GetInstance()->GetCurrentLevel());
            assert(pFlipbookEditor);
            pFlipbookEditor->NextFrame();
            CSprite* pSprite = pFlipbookEditor->GetSprite();
            pFlipbookEditor->UpdateSpriteInfo(hDlg, pFlipbookEditor->GetIndex());

            return (INT_PTR)TRUE;
        }
        else if (LOWORD(wParam) == IDC_FLIPBOOKEDITOR_BUTTON_PREV)
        {
            CFlipbookEditorLevel* pFlipbookEditor = dynamic_cast<CFlipbookEditorLevel*>(LevelManager::GetInstance()->GetCurrentLevel());
            assert(pFlipbookEditor);
            pFlipbookEditor->PrevFrame();
            CSprite* pSprite = pFlipbookEditor->GetSprite();
            pFlipbookEditor->UpdateSpriteInfo(hDlg, pFlipbookEditor->GetIndex());

            return (INT_PTR)TRUE;
        }
        else if (LOWORD(wParam) == IDC_FLIPBOOKEDITOR_BUTTON_APPLY)
        {
            CFlipbookEditorLevel* pLevel = dynamic_cast<CFlipbookEditorLevel*>(LevelManager::GetInstance()->GetCurrentLevel());
            assert(pLevel);

            CSprite* pSprite = pLevel->GetSprite();

            HWND hEditControl = GetDlgItem(hDlg, IDC_FLIPBOOKEDITOR_EDIT_DURATION);
            if (hEditControl)
            {
                const int bufferSize = 256;
                wchar_t Duration[bufferSize];
                int length = GetWindowText(hEditControl, Duration, bufferSize);
                if (length > 0)
                {
                    float value = std::wcstof(Duration, nullptr);
                    pSprite->SetDuration(value);
                }
            }

            Vec2 Offset;
            hEditControl = GetDlgItem(hDlg, IDC_FLIPBOOKEDITOR_EDIT_OFFSET_X);
            if (hEditControl)
            {
                const int bufferSize = 256;
                wchar_t OffsetX[bufferSize];
                int length = GetWindowText(hEditControl, OffsetX, bufferSize);
                if (length > 0)
                {
                    UINT value = static_cast<UINT>(std::wcstoul(OffsetX, nullptr, 10));
                    Offset.x = value;
                }
            }

            hEditControl = GetDlgItem(hDlg, IDC_FLIPBOOKEDITOR_EDIT_OFFSET_Y);
            if (hEditControl)
            {
                const int bufferSize = 256;
                wchar_t OffsetY[bufferSize];
                int length = GetWindowText(hEditControl, OffsetY, bufferSize);
                if (length > 0)
                {
                    UINT value = static_cast<UINT>(std::wcstoul(OffsetY, nullptr, 10));
                    Offset.y = value;
                }
            }
            pSprite->SetOffset(Offset);

            pLevel->Apply();

            return (INT_PTR)TRUE;
        }
        else if (HIWORD(wParam) == LBN_DBLCLK)
        {
            CFlipbookEditorLevel* pFlipbookEditor = dynamic_cast<CFlipbookEditorLevel*>(LevelManager::GetInstance()->GetCurrentLevel());
            assert(pFlipbookEditor);

            // 더블클릭 시 ListBox의 항목 선택 확인
            HWND hListBox = GetDlgItem(hDlg, IDC_FLIPBOOKEDITOR_LIST_SPRITES);
            int index = SendMessage(hListBox, LB_GETCURSEL, 0, 0); // 현재 선택된 항목의 인덱스 가져오기
            pFlipbookEditor->SetIndex(index);

            // 유효한 인덱스인지 확인
            if (index != LB_ERR)
            {
                wchar_t key[256];
                SendMessage(hListBox, LB_GETTEXT, index, (LPARAM)key); // 선택된 항목의 텍스트 가져오기
                CSprite* pSprite = AssetManager::GetInstance()->GetSprite(key);
                pFlipbookEditor->UpdateSpriteInfo(hDlg, index);
            }
            return (INT_PTR)TRUE;
        }
        else if (LOWORD(wParam) == IDC_FLIPBOOKEDITOR_BUTTON_PLAY)
        {
            CFlipbookEditorLevel* pFlipbookEditor = dynamic_cast<CFlipbookEditorLevel*>(LevelManager::GetInstance()->GetCurrentLevel());
            assert(pFlipbookEditor);
            pFlipbookEditor->Play();

            return (INT_PTR)TRUE;
        }
        else if (LOWORD(wParam) == IDC_FLIPBOOKEDITOR_BUTTON_STOP)
        {
            CFlipbookEditorLevel* pFlipbookEditor = dynamic_cast<CFlipbookEditorLevel*>(LevelManager::GetInstance()->GetCurrentLevel());
            assert(pFlipbookEditor);
            pFlipbookEditor->PrevFrame();
            pFlipbookEditor->Stop();

            return (INT_PTR)TRUE;
        }
        else if (LOWORD(wParam) == IDC_FLIPBOOKEDITOR_BUTTON_SAVE)
        {
            CFlipbookEditorLevel* pFlipbookEditor = dynamic_cast<CFlipbookEditorLevel*>(LevelManager::GetInstance()->GetCurrentLevel());
            assert(pFlipbookEditor);
            pFlipbookEditor->SaveFlipbook();

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