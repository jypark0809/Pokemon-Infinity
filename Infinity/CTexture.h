#pragma once
#include "CAsset.h"
class CTexture :
    public CAsset
{
private:
    HBITMAP     m_hBitMap;
    HDC	        m_DC;
    BITMAP      m_Info;

public:
    HDC GetDC() { return m_DC; }
    int GetWidth() { return m_Info.bmWidth; }
    int GetHeight() { return m_Info.bmHeight; }
    void Resize(UINT _Width, UINT _Height);

private:
    virtual int Load(const wstring& _RelativePath) override;
    void Create(UINT _Width, UINT _Height);
    

public:
    CTexture();
    ~CTexture();

    friend class AssetManager;
};

