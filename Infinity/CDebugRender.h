#pragma once

enum DEBUG_SHAPE
{
	RECTANGLE,
	CIRCLE,
	LINE,
};

struct DebugShapeInfo
{
	DEBUG_SHAPE		Shape;		// 모양
	Vec2			Pos;		// 위치, Line : 시작
	Vec2			Scale;		// 크기, Line : 끝점
	PEN_TYPE		Pen;		// 테두리 색상
	BRUSH_TYPE		Brush;		// 내부 색상
	float			CurTime;	// 총 노출된 시간
	float			Duration;	// 최대 노출 시간
};

class CDebugRender
{
	DECLARE_SINGLE(CDebugRender);
private:
	list<DebugShapeInfo>	m_ShapeInfo;
	bool					m_Show;

public:
	void Render(HDC _dc);
	void AddDebugShapeInfo(const DebugShapeInfo& _Info) { m_ShapeInfo.push_back(_Info); }

private:
	void DebugRender(HDC _dc, DebugShapeInfo& _Info);
};

