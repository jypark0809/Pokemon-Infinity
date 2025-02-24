#include "pch.h"
#include "CTexture.h"

#include "AssetManager.h"

CTexture::CTexture()
    : CAsset(AssetType::TEXTURE)
    , m_hBitMap(nullptr)
    , m_DC(nullptr)
    , m_Info{}
{
}

CTexture::~CTexture()
{
}

int CTexture::Load(const wstring& _RelativePath)
{
    fs::path fullPath = CONTENT_PATH / _RelativePath;

    if (fullPath.extension() == L".png" || fullPath.extension() == L".PNG")
    {
        ULONG_PTR gdiplusToken = 0;
        GdiplusStartupInput gdostartupInput = {};
        GdiplusStartup(&gdiplusToken, &gdostartupInput, nullptr);
        Image* pImge = Image::FromFile(fullPath.c_str(), false);
        Bitmap* pBitmap = (Bitmap*)pImge->Clone();
        if (S_OK != pBitmap->GetHBITMAP(Color(0, 0, 0, 0), &m_hBitMap))
            assert(nullptr);

        delete pImge;
    }
    else if (fullPath.extension() == L".bmp" || fullPath.extension() == L".BMP")
    {
        m_hBitMap = (HBITMAP)LoadImage(nullptr, fullPath.c_str()
            , IMAGE_BITMAP, 0, 0
            , LR_CREATEDIBSECTION | LR_LOADFROMFILE);

        if (nullptr == m_hBitMap)
            return E_FAIL;
    }
    else
    {
        assert(nullptr);
    }

    // DC 생성
    m_DC = CreateCompatibleDC(CEngine::GetInstance()->GetMainDC());

    // DC 와 파일로부터 로딩해서 만들어진 BitMap 을 연결해준다.
    DeleteObject(SelectObject(m_DC, m_hBitMap));

    // 로딩된 비트맵의 정보를 BITMAP 구조체에 채운다.
    GetObject(m_hBitMap, sizeof(BITMAP), &m_Info);

    return S_OK;
}

void CTexture::Create(UINT _Width, UINT _Height)
{
    // 추가 비트맵 생성
    m_hBitMap = CreateCompatibleBitmap(CEngine::GetInstance()->GetMainDC(), _Width, _Height);

    // 추가 DC 생성
    m_DC = CreateCompatibleDC(CEngine::GetInstance()->GetMainDC());

    // 새로 생성한 DC 가 새로 생성한 Bitmap 을 목적지로 지정
    // DC 가 생성될때 원래 가지고 있던 Bitmap 은 삭제
    DeleteObject(SelectObject(m_DC, m_hBitMap));

    // 로딩된 비트맵의 정보를 BITMAP 구조체에 채운다.
    GetObject(m_hBitMap, sizeof(BITMAP), &m_Info);
}

void CTexture::Render(HDC _hdc, Vec2 _OriginDest)
{
    BLENDFUNCTION blend = {};
    blend.BlendOp = AC_SRC_OVER;
    blend.BlendFlags = 0;
    blend.SourceConstantAlpha = 255; // 추가 알파값
    blend.AlphaFormat = AC_SRC_ALPHA; // 알파 채널의 알파값을 투명도로 사용

    AlphaBlend(_hdc
        , _OriginDest.x
        , _OriginDest.y
        , m_Info.bmWidth
        , m_Info.bmHeight
        , m_DC
        , 0, 0
        , m_Info.bmWidth
        , m_Info.bmHeight
        , blend);
}

void CTexture::Resize(UINT _Width, UINT _Height)
{
    // 기존 백 버퍼 해제
    if (m_hBitMap) {
        DeleteObject(m_hBitMap);
        m_hBitMap = nullptr;
    }

    // 새로운 백 버퍼 생성
    Create(_Width, _Height);
}
