#pragma once
class CSelectGDI
{
private:
	HDC			m_DC;
	HGDIOBJ		m_PrevObj;

public:
	CSelectGDI(HDC _dc, HGDIOBJ _GDIObj);
	~CSelectGDI();
};

