#pragma once

enum DEBUG_SHAPE
{
	RECTANGLE,
	CIRCLE,
	LINE,
};

struct DebugShapeInfo
{
	DEBUG_SHAPE		Shape;		// ���
	Vec2			Pos;		// ��ġ, Line : ����
	Vec2			Scale;		// ũ��, Line : ����
	PEN_TYPE		Pen;		// �׵θ� ����
	BRUSH_TYPE		Brush;		// ���� ����
	float			CurTime;	// �� ����� �ð�
	float			Duration;	// �ִ� ���� �ð�
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

