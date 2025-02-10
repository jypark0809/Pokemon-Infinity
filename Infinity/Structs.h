#pragma once

struct Vec2
{
public:
	float x;
	float y;

public:
	float Distance(Vec2 _Other) { return sqrtf((x - _Other.x) * (x - _Other.x) + (y - _Other.y) * (y - _Other.y)); }
	float Length() { return sqrt(x * x + y * y); }
	bool IsZero() { return (x == 0.f && y == 0.f); }

public:
	Vec2 operator + (const Vec2& _Other) { return Vec2(x + _Other.x, y + _Other.y); }
	Vec2 operator + (float _f) { return Vec2(x + _f, y + _f); }
	void operator += (const Vec2& _Other) { x += _Other.x; y += _Other.y; }
	void operator += (float _f) { x += _f; y += _f; }

	Vec2 operator - (const Vec2& _Other) { return Vec2(x - _Other.x, y - _Other.y); }
	Vec2 operator - (float _f) { return Vec2(x - _f, y - _f); }
	void operator -= (const Vec2& _Other) { x -= _Other.x; y -= _Other.y; }
	void operator -= (float _f) { x -= _f; y -= _f; }

	Vec2 operator * (const Vec2& _Other) { return Vec2(x * _Other.x, y * _Other.y); }
	Vec2 operator * (float _f) { return Vec2(x * _f, y * _f); }
	void operator *= (const Vec2& _Other) { x *= _Other.x; y *= _Other.y; }
	void operator *= (float _f) { x *= _f; y *= _f; }


	Vec2 operator / (const Vec2& _Other) { assert(_Other.x != 0.f && _Other.y != 0.f); return Vec2(x / _Other.x, y / _Other.y); }
	Vec2 operator / (float _f) { assert(_f != 0.f); return Vec2(x / _f, y / _f); }
	void operator /= (const Vec2& _Other) { assert(_Other.x != 0.f && _Other.y != 0.f); x /= _Other.x; y /= _Other.y; }
	void operator /= (float _f) { assert(_f != 0.f); x /= _f; y /= _f; }

	Vec2 operator = (POINT _pt)
	{
		x = (float)_pt.x;
		y = (float)_pt.y;

		return *this;
	}

	Vec2() : x(0.f)	, y(0.f) {}
	Vec2(float _x, float _y) : x(_x), y(_y)	{}
};

struct Vec2Int
{
public:
	int x = 0;
	int y = 0;

public:
	int LengthSquared() { return x * x + y * y; }
	float Length() { return (float)::sqrt(LengthSquared()); }

	Vec2Int operator + (const Vec2Int& _Other) { return Vec2Int(x + _Other.x, y + _Other.y); }
	Vec2Int operator + (int _i) { return Vec2Int(x + _i, y + _i); }
	void	operator += (const Vec2Int& _Other) { x += _Other.x; y += _Other.y; }
	void	operator += (int _i) { x += _i; y += _i; }

	Vec2Int operator - (const Vec2Int& _Other) { return Vec2Int(x - _Other.x, y - _Other.y); }
	Vec2Int operator - (int _i) { return Vec2Int(x - _i, y - _i); }
	void	operator -= (const Vec2Int& _Other) { x -= _Other.x; y -= _Other.y; }
	void	operator -= (int _i) { x -= _i; y -= _i; }

	Vec2Int operator * (const Vec2Int& _Other) { return Vec2Int(x * _Other.x, y * _Other.y); }
	Vec2Int operator * (int _i) { return Vec2Int(x * _i, y * _i); }
	void	operator *= (const Vec2Int& _Other) { x *= _Other.x; y *= _Other.y; }
	void	operator *= (int _i) { x *= _i; y *= _i; }

	Vec2Int operator / (const Vec2Int& _Other) { assert(_Other.x != 0 && _Other.y != 0); return Vec2Int(x / _Other.x, y / _Other.y); }
	Vec2Int operator / (int _i) { assert(_i != 0); return Vec2Int(x / _i, y / _i); }
	void	operator /= (const Vec2Int& _Other) { assert(_Other.x != 0 && _Other.y != 0); x /= _Other.x; y /= _Other.y; }
	void	operator /= (int _i) { assert(_i != 0); x /= _i; y /= _i; }

	/*int Dot(VectorInt other)
	{
		return x * other.x + y * other.y;
	}

	int Cross(VectorInt other)
	{
		return x * other.y - y * other.x;
	}*/

public:
	Vec2Int() {}
	Vec2Int(int _x, int _y) : x(_x), y(_y) {}
	Vec2Int(POINT _pt) : x(_pt.x), y(_pt.y) {}
};

// CREATE_OBJECT - Param0 : Object狼 林家 / Param1 : Layer
// DELETE_OBJECT - Param0 : Object狼 林家
// CHANGE_LEVEL  - Param0 : LevelType
struct Task
{
	TASK_TYPE	Type;
	DWORD_PTR	Param0;
	DWORD_PTR	Param1;
};