#include "pch.h"
#include "CSelectGDI.h"

CSelectGDI::CSelectGDI(HDC _dc, HGDIOBJ _GDIObj)
	: m_DC(_dc)
	, m_PrevObj(nullptr)
{
	m_PrevObj = SelectObject(m_DC, _GDIObj);
}

CSelectGDI::~CSelectGDI()
{
	SelectObject(m_DC, m_PrevObj);
}