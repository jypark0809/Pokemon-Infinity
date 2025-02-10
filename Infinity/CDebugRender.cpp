#include "pch.h"
#include "CDebugRender.h"
#include "KeyManager.h"
#include "TimeManager.h"

CDebugRender::CDebugRender()
	: m_Show(true)
{

}

CDebugRender::~CDebugRender()
{

}

void CDebugRender::Render(HDC _dc)
{
	if (KeyManager::GetInstance()->GetButtonDown(Key::Enter))
		m_Show = !m_Show;

	list<DebugShapeInfo>::iterator iter = m_ShapeInfo.begin();
	for (; iter != m_ShapeInfo.end(); )
	{
		// 디버그 렌더링
		DebugRender(_dc, *iter);

		// 시간체크
		(*iter).CurTime += DT;
		if ((*iter).Duration <= (*iter).CurTime)
		{
			iter = m_ShapeInfo.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void CDebugRender::DebugRender(HDC _dc, DebugShapeInfo& _Info)
{
	if (!m_Show)
		return;

	SELECT_PEN(_dc, _Info.Pen);

	// 렌더링
	switch (_Info.Shape)
	{
	case RECTANGLE:
	{
		SELECT_BRUSH(_dc, _Info.Brush);
		Rectangle(_dc
			, _Info.Pos.x - _Info.Scale.x / 2.f
			, _Info.Pos.y - _Info.Scale.y / 2.f
			, _Info.Pos.x + _Info.Scale.x / 2.f
			, _Info.Pos.y + _Info.Scale.y / 2.f);
	}
	break;
	case CIRCLE:
	{
		SELECT_BRUSH(_dc, _Info.Brush);
		Ellipse(_dc
			, _Info.Pos.x - _Info.Scale.x / 2.f
			, _Info.Pos.y - _Info.Scale.y / 2.f
			, _Info.Pos.x + _Info.Scale.x / 2.f
			, _Info.Pos.y + _Info.Scale.y / 2.f);
	}
	break;
	case LINE:
		MoveToEx(_dc, _Info.Pos.x, _Info.Pos.y, nullptr);
		LineTo(_dc, _Info.Scale.x, _Info.Scale.y);
		break;
	}
}