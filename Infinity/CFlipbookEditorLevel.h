#pragma once
#include "CLevel.h"

class CFlipbook;

class CFlipbookEditorLevel :
    public CLevel
{
private:
    HWND                m_hDialog;              // Modeless Dialog
    HWND                m_hListBox;             // List Box
    vector<CSprite*>    m_Sprites;
    UINT                m_Index;
    float               m_Time;
    bool                m_Play;                 // Àç»ý Áß

public:
    
    UINT GetIndex() { return m_Index; }
    void SetIndex(UINT _Index) { m_Index = _Index; }
    CSprite* GetSprite() { return m_Sprites[m_Index]; }
    void NextFrame();
    void PrevFrame();
    void Apply();
    void Play();
    void Stop();
    void AddSprite();
    void DeleteSprite();
    void SaveFlipbook();
    void UpdateSpriteInfo(HWND _hDlg, UINT _Index);
    

    virtual void BeginPlay() override;
    virtual void Tick() override;
    virtual void FinalTick() override;
    virtual void Render(HDC _Hdc) override;

    virtual void OnEnter() override;
    virtual void OnExit() override;

public:
    CFlipbookEditorLevel();
    ~CFlipbookEditorLevel();
};

