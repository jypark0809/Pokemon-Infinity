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

    // DC ����
    m_DC = CreateCompatibleDC(CEngine::GetInstance()->GetMainDC());

    // DC �� ���Ϸκ��� �ε��ؼ� ������� BitMap �� �������ش�.
    DeleteObject(SelectObject(m_DC, m_hBitMap));

    // �ε��� ��Ʈ���� ������ BITMAP ����ü�� ä���.
    GetObject(m_hBitMap, sizeof(BITMAP), &m_Info);

    return S_OK;
}

void CTexture::Create(UINT _Width, UINT _Height)
{
    // �߰� ��Ʈ�� ����
    m_hBitMap = CreateCompatibleBitmap(CEngine::GetInstance()->GetMainDC(), _Width, _Height);

    // �߰� DC ����
    m_DC = CreateCompatibleDC(CEngine::GetInstance()->GetMainDC());

    // ���� ������ DC �� ���� ������ Bitmap �� �������� ����
    // DC �� �����ɶ� ���� ������ �ִ� Bitmap �� ����
    DeleteObject(SelectObject(m_DC, m_hBitMap));

    // �ε��� ��Ʈ���� ������ BITMAP ����ü�� ä���.
    GetObject(m_hBitMap, sizeof(BITMAP), &m_Info);
}

void CTexture::Render(HDC _hdc, Vec2 _OriginDest)
{
    BLENDFUNCTION blend = {};
    blend.BlendOp = AC_SRC_OVER;
    blend.BlendFlags = 0;
    blend.SourceConstantAlpha = 255; // �߰� ���İ�
    blend.AlphaFormat = AC_SRC_ALPHA; // ���� ä���� ���İ��� ������ ���

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
    // ���� �� ���� ����
    if (m_hBitMap) {
        DeleteObject(m_hBitMap);
        m_hBitMap = nullptr;
    }

    // ���ο� �� ���� ����
    Create(_Width, _Height);
}
