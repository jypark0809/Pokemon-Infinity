#pragma once

class CTexture;

class CEngine
{
	DECLARE_SINGLE(CEngine);
private:
	HINSTANCE	m_hInst;						// 프로세스 핸들
	HWND		m_hMainWnd;						// 메인 윈도우 핸들
	HDC			m_hdc;							// DeviceContext (DC), 그리기(렌더링) 작업 관리자
	Vec2		m_Resolution;					// 윈도우 해상도
	CTexture*	m_BackBuffer;					// 백버퍼 텍스쳐

	HPEN		m_Pen[(UINT)PEN_TYPE::COUNT];		// Pen 핸들
	HBRUSH		m_Brush[(UINT)BRUSH_TYPE::COUNT];	// Brush 핸들

public:
	int Init(HWND _hWnd, int _Width, int _Height);
	void Progress();

public:
	void ChangeWindowSize(int _Width, int _Height);

	Vec2 GetResolution() { return m_Resolution; }
	void SetResolution(Vec2 _Resolution) { m_Resolution = _Resolution; }
	
	HINSTANCE GetHInst() { return m_hInst; }
	void SetHInst(HINSTANCE _hInst) { m_hInst = _hInst; }

	HWND GetMainWnd() { return m_hMainWnd; }
	HDC GetMainDC() { return m_hdc; }
	HPEN GetPen(PEN_TYPE _Type) { return m_Pen[(UINT)_Type]; }
	HBRUSH GetBrush(BRUSH_TYPE _Type) { return m_Brush[(UINT)_Type]; }
	HDC GetBackBufferDC();

private:
	void CreateGDIObject();
};

