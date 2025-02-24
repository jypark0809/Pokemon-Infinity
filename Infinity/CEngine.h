#pragma once

class CTexture;

class CEngine
{
	DECLARE_SINGLE(CEngine);
private:
	HINSTANCE	m_hInst;						// ���μ��� �ڵ�
	HWND		m_hMainWnd;						// ���� ������ �ڵ�
	HDC			m_hdc;							// DeviceContext (DC), �׸���(������) �۾� ������
	Vec2		m_Resolution;					// ������ �ػ�
	CTexture*	m_BackBuffer;					// ����� �ؽ���

	HPEN		m_Pen[(UINT)PEN_TYPE::COUNT];		// Pen �ڵ�
	HBRUSH		m_Brush[(UINT)BRUSH_TYPE::COUNT];	// Brush �ڵ�

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

