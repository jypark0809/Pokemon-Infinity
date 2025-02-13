#include "pch.h"
#include "CEngine.h"

#include "AssetManager.h"
#include "KeyManager.h"
#include "TimeManager.h"
#include "LevelManager.h"
#include "TaskManager.h"
#include "CDebugRender.h"

#include "CTexture.h"

CEngine::CEngine()
	: m_hMainWnd(nullptr)
	, m_Resolution{}
	, m_hdc(nullptr)
	, m_BackBuffer(nullptr)
	, m_Pen{}
	, m_Brush{}
{
}

CEngine::~CEngine()
{
	ReleaseDC(m_hMainWnd, m_hdc);

	// Delete GDI OBject
	for (UINT i = 0; i < (UINT)PEN_TYPE::COUNT; ++i)
	{
		DeleteObject(m_Pen[i]);
	}

	for (UINT i = 0; i < (UINT)BRUSH_TYPE::HOLLOW; ++i)
	{
		DeleteObject(m_Brush[i]);
	}
}

int CEngine::Init(HWND _hWnd, int _Width, int _Height)
{
	m_hMainWnd = _hWnd;
	m_hdc = GetDC(m_hMainWnd);

	// 윈도우 크기 변경
	ChangeWindowSize(_Width, _Height);

	// BackBuffer 텍스쳐 생성
	m_BackBuffer = AssetManager::GetInstance()->CreateTexture(L"BackBuffer", _Width, _Height);

	// GDI Object(Graphic Device Interface Object) 생성 (Pen, Brush...)
	CreateGDIObject();

	// Manager 초기화
	// CCamera::GetInst()->Init();

	// Manager 초기화
	AssetManager::GetInstance()->Init();
	KeyManager::GetInstance()->Init();
	TimeManager::GetInstance()->Init();
	LevelManager::GetInstance()->Init();
	// CCamera::GetInst()->Init();
	
	return S_OK;
}

void CEngine::Progress()
{
	// Tick
	KeyManager::GetInstance()->Tick();
	TimeManager::GetInstance()->Tick();
	// UIManager::GetInst()->Tick();
	LevelManager::GetInstance()->Tick();
	// CCollisionMgr::GetInst()->Tick();
	// CCamera::GetInst()->Tick();

	// FinalTick
	LevelManager::GetInstance()->FinalTick();

	// Render
	{
		// Clear 
		SELECT_BRUSH(m_BackBuffer->GetDC(), BRUSH_TYPE::DARKGRAY);
		Rectangle(m_BackBuffer->GetDC(), -1, -1, m_Resolution.x + 1, m_Resolution.y + 1);
	}

	// 비트맵, 더블 버퍼링, 이미지 개념, 로딩
	LevelManager::GetInstance()->Render(m_BackBuffer->GetDC());

	// Camera PostProcess
	// CCamera::GetInst()->Render(m_BackBuffer->GetDC());

	// Debug Render
	CDebugRender::GetInstance()->Render(m_BackBuffer->GetDC());

	// BackBuffer 에 그려진 최종 그림을 MainBuffer 로 복사
	BitBlt(m_hdc, 0, 0, m_Resolution.x, m_Resolution.y, m_BackBuffer->GetDC(), 0, 0, SRCCOPY);

	// TaskManager
	TaskManager::GetInstance()->Tick();
}

void CEngine::ChangeWindowSize(int _Width, int _Height)
{
	SetResolution(Vec2(static_cast<float>(_Width), static_cast<float>(_Height)));

	if (m_BackBuffer)
		m_BackBuffer->Resize(_Width, _Height);

	RECT rect = { 0, 0, _Width, _Height };

	// 설정한 해상도에 따른 윈도우의 크기 계산
	// GetMenu(m_hWnd) : 해당 윈도우에 메뉴가 없다면 nullptr, 있다면 1을 반환한다.
	// !! : 이중부정 연산자는 GetMenu(m_hWnd)의 반환값을 0 또는 1로 변환한다.
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, !!GetMenu(m_hMainWnd));

	// 윈도우 크기 및 위치 설정
	SetWindowPos(m_hMainWnd
		, nullptr
		, 0
		, 0
		, rect.right - rect.left
		, rect.bottom - rect.top
		, 0);
}

HDC CEngine::GetBackBufferDC()
{
	return m_BackBuffer->GetDC();
}

void CEngine::CreateGDIObject()
{
	// Pen 생성
	m_Pen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_Pen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_Pen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	m_Pen[(UINT)PEN_TYPE::GRAY] = CreatePen(PS_SOLID, 1, RGB(120, 120, 120));
	m_Pen[(UINT)PEN_TYPE::YELLOW] = CreatePen(PS_SOLID, 1, RGB(0, 255, 255));

	// Brush
	m_Brush[(UINT)BRUSH_TYPE::RED] = CreateSolidBrush(RGB(255, 0, 0));
	m_Brush[(UINT)BRUSH_TYPE::GREEN] = CreateSolidBrush(RGB(0, 255, 0));
	m_Brush[(UINT)BRUSH_TYPE::BLUE] = CreateSolidBrush(RGB(0, 0, 255));
	m_Brush[(UINT)BRUSH_TYPE::WHITE] = CreateSolidBrush(RGB(255, 255, 255));
	m_Brush[(UINT)BRUSH_TYPE::GRAY] = CreateSolidBrush(RGB(200, 200, 200));
	m_Brush[(UINT)BRUSH_TYPE::DARKGRAY] = CreateSolidBrush(RGB(49, 49, 49));
	m_Brush[(UINT)BRUSH_TYPE::EMERALD] = CreateSolidBrush(RGB(0, 255, 255));
	m_Brush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
}

