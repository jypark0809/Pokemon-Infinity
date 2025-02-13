#include "pch.h"
#include "Utils.h"

#include "CDebugRender.h"
#include "AssetManager.h"
#include "TaskManager.h"
#include "CGameObject.h"
#include "CTexture.h"
#include "CSprite.h"
#include "CFlipbook.h"
// #include "Sound.h"

#pragma region Debug Render
void DrawText(HDC _Hdc, Vec2 _Pos, const wstring& _Str)
{
	::TextOut(_Hdc, static_cast<__int32>(_Pos.x)
		, static_cast<__int32>(_Pos.y)
		, _Str.c_str()
		, static_cast<__int32>(_Str.size()));
}

void DrawDebugRect(Vec2 _Center, Vec2 _Scale, PEN_TYPE _Pen, BRUSH_TYPE _Brush, float _Duration)
{
	DebugShapeInfo info = {};
	info.Shape = RECTANGLE;
	info.Pos = _Center;
	info.Scale = _Scale;
	info.CurTime = 0.f;
	info.Duration = _Duration;
	info.Pen = _Pen;
	info.Brush = _Brush;
	CDebugRender::GetInstance()->AddDebugShapeInfo(info);
}

void DrawDebugRectLT(Vec2 _LeftTop, Vec2 _Scale, PEN_TYPE _Pen, BRUSH_TYPE _Brush, float _Duration)
{
	DebugShapeInfo info = {};
	info.Shape = RECTANGLE;
	info.Pos = _LeftTop + (_Scale / 2.f);
	info.Scale = _Scale;
	info.CurTime = 0.f;
	info.Duration = _Duration;
	info.Pen = _Pen;
	info.Brush = _Brush;
	CDebugRender::GetInstance()->AddDebugShapeInfo(info);
}

void DrawDebugCircle(Vec2 _Center, Vec2 _Scale, PEN_TYPE _Pen, BRUSH_TYPE _Brush, float _Duration)
{
	DebugShapeInfo info = {};
	info.Shape = CIRCLE;
	info.Pos = _Center;
	info.Scale = _Scale;
	info.CurTime = 0.f;
	info.Duration = _Duration;
	info.Pen = _Pen;
	info.Brush = _Brush;
	CDebugRender::GetInstance()->AddDebugShapeInfo(info);
}

void DrawDebugCircleLT(Vec2 _LeftTop, Vec2 _Scale, PEN_TYPE _Pen, BRUSH_TYPE _Brush, float _Duration)
{
	DebugShapeInfo info = {};
	info.Shape = CIRCLE;
	info.Pos = _LeftTop + (_Scale / 2.f);
	info.Scale = _Scale;
	info.CurTime = 0.f;
	info.Duration = _Duration;
	info.Pen = _Pen;
	info.Brush = _Brush;
	CDebugRender::GetInstance()->AddDebugShapeInfo(info);
}

void DrawDebugLine(Vec2 _Start, Vec2 _End, PEN_TYPE _Pen, float _Duration)
{
	DebugShapeInfo info = {};
	info.Shape = LINE;
	info.Pos = _Start;
	info.Scale = _End;
	info.CurTime = 0.f;
	info.Duration = _Duration;
	info.Pen = _Pen;
	info.Brush = BRUSH_TYPE::COUNT;
	CDebugRender::GetInstance()->AddDebugShapeInfo(info);
}
#pragma endregion

#pragma region File Save/Load
void SaveWString(FILE* _File, const wstring& _str)
{
	BYTE len = _str.length();
	fwrite(&len, sizeof(BYTE), 1, _File);
	fwrite(_str.c_str(), sizeof(wchar_t), _str.length(), _File);
}

void LoadWString(FILE* _File, wstring& _Str)
{
	BYTE len = 0;
	fread(&len, sizeof(BYTE), 1, _File);

	wchar_t szStr[255] = {};
	fread(szStr, sizeof(wchar_t), len, _File);

	_Str = szStr;
}

void SaveAssetInfo(FILE* _File, CAsset* _Asset)
{
	bool bAsset = _Asset;
	fwrite(&bAsset, sizeof(bool), 1, _File);

	if (!bAsset)
		return;

	SaveWString(_File, _Asset->GetKey());
	SaveWString(_File, _Asset->GetRelativePath());
}

CAsset* LoadAssetInfo(FILE* _File, AssetType _type)
{
	bool bAsset = false;
	fread(&bAsset, sizeof(bool), 1, _File);

	if (!bAsset)
		return nullptr;

	wstring key, path;
	LoadWString(_File, key);
	LoadWString(_File, path);

	switch (_type)
	{
	case AssetType::TEXTURE:
		return AssetManager::GetInstance()->LoadTexture(key, path);
		break;
	case AssetType::SPRITE:
		return AssetManager::GetInstance()->LoadSprite(key, path);
		break;
	case AssetType::FLIPBOOK:
		return AssetManager::GetInstance()->LoadFlipbook(key, path);
		break;
	case AssetType::SOUND:
		// return AssetManager::GetInstance()->LoadSound(key, path);
		break;
	}

	return nullptr;
}
#pragma endregion

bool IsValid(CGameObject*& _Object)
{
	if (nullptr == _Object)
		return false;

	if (_Object->IsDead())
	{
		_Object = nullptr;
		return false;
	}

	return true;
}

void DrawCheckeredPattern(HDC _Hdc, int _Width, int _Height, int _SquareSize)
{
	Vec2 vResolution = CEngine::GetInstance()->GetResolution(); // 화면 해상도

	// 중앙 좌표 계산
	int startX = (vResolution.x - _Width) / 2;
	int startY = (vResolution.y - _Height) / 2;

	// 미리 정의된 브러시 가져오기
	HBRUSH whiteBrush = CEngine::GetInstance()->GetBrush(BRUSH_TYPE::WHITE);
	HBRUSH grayBrush = CEngine::GetInstance()->GetBrush(BRUSH_TYPE::GRAY);

	// 기본 체크무늬 그리기
	for (int y = startY; y < startY + _Height; y += _SquareSize) {
		for (int x = startX; x < startX + _Width; x += _SquareSize) {
			// 색상 선택
			HBRUSH brush = ((x / _SquareSize) % 2 == (y / _SquareSize) % 2) ? whiteBrush : grayBrush;

			// 사각형 그리기
			RECT rect = { x, y, min(x + _SquareSize, startX + _Width), min(y + _SquareSize, startY + _Height) };
			FillRect(_Hdc, &rect, brush);
		}
	}

	// 나머지 부분 그리기 (가로)
	if (_Width % _SquareSize != 0) {
		for (int y = startY; y < startY + _Height; y += _SquareSize) {
			// 나머지 부분의 색상 결정
			HBRUSH brush = ((startX + (_Width - (_Width % _SquareSize))) / _SquareSize % 2 == (y / _SquareSize) % 2) ? whiteBrush : grayBrush;
			RECT rect = { startX + (_Width - (_Width % _SquareSize)), y, startX + _Width, min(y + _SquareSize, startY + _Height) };
			FillRect(_Hdc, &rect, brush); // 나머지 부분을 체크무늬로 채움
		}
	}

	// 나머지 부분 그리기 (세로)
	if (_Height % _SquareSize != 0) {
		for (int x = startX; x < startX + _Width; x += _SquareSize) {
			// 나머지 부분의 색상 결정
			HBRUSH brush = ((x / _SquareSize) % 2 == (startY + (_Height - (_Height % _SquareSize))) / _SquareSize % 2) ? whiteBrush : grayBrush;
			RECT rect = { x, startY + (_Height - (_Height % _SquareSize)), min(x + _SquareSize, startX + _Width), startY + _Height };
			FillRect(_Hdc, &rect, brush); // 나머지 부분을 체크무늬로 채움
		}
	}
}