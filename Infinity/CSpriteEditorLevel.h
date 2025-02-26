#pragma once
#include "CLevel.h"

class CTexture;
class CCamera;
class CTilemap;

class CSpriteEditorLevel :
    public CLevel
{
private:
    HMENU               m_hMenu;
    HWND                m_hDialog;              // Modeless Dialog

    CTexture*           m_Texture;
    
    Vec2                m_Offset;               // Grid By Cell Size 시작점
    Vec2                m_Padding;              // Grid By Cell 사이 간격
    int                 m_Rows;                  
    int                 m_Columns;               
    Vec2                m_PixelSize;            // Grid By Cell Size
    vector<CSprite*>    m_Sprites;              // Grid By Cell Size의 결과로 잘라진 Sprite 저장
    int                 m_SelectedSpriteIndex;  // 선택된 스프라이트의 인덱스


    CTilemap*           m_Tilemap;

    CCamera*            m_Camera;

private:
    void ShowSpriteInfoDialog(CSprite* _Sprite);

public:
    void LoadFile();
    void SetTexture(CTexture* _Texture) { m_Texture = _Texture; }
    void GridByCellSize(Vec2 _Size, Vec2 _LeftTop, Vec2 _Padding);
    CSprite* GetSelectedSpriteInfo() { return m_Sprites[m_SelectedSpriteIndex]; }
    void CreateTilePalette();
    void Revert();
    void Apply();

    virtual void BeginPlay() override;
    virtual void Tick() override;
    virtual void Render(HDC _Hdc) override;

    virtual void OnEnter() override;
    virtual void OnExit() override;

public:
    CSpriteEditorLevel();
    ~CSpriteEditorLevel();
};

LRESULT CALLBACK    GridByCellSizeProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    NineSlicingProc(HWND, UINT, WPARAM, LPARAM);