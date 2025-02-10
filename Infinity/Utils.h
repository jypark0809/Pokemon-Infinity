#pragma once

// Text
void DrawText(HDC _Hdc, Vec2 _Pos, const wstring& _Str);

// Debug Render
void DrawDebugRect(Vec2 _Center, Vec2 _Scale, PEN_TYPE _Pen, BRUSH_TYPE _Brush = BRUSH_TYPE::HOLLOW, float _Duration = 0.f);
void DrawDebugRectLT(Vec2 _LeftTop, Vec2 _Scale, PEN_TYPE _Pen, BRUSH_TYPE _Brush = BRUSH_TYPE::HOLLOW, float _Duration = 0.f);
void DrawDebugCircle(Vec2 _Center, Vec2 _Scale, PEN_TYPE _Pen, BRUSH_TYPE _Brush = BRUSH_TYPE::HOLLOW, float _Duration = 0.f);
void DrawDebugCircleLT(Vec2 _LeftTop, Vec2 _Scale, PEN_TYPE _Pen, BRUSH_TYPE _Brush = BRUSH_TYPE::HOLLOW, float _Duration = 0.f);
void DrawDebugLine(Vec2 _Start, Vec2 _End, PEN_TYPE _Pen, float _Duration = 0.f);

// File Save/Load
void SaveWString(FILE* _File, const wstring& _str);
void LoadWString(FILE* _File, wstring& _Str);
void SaveAssetInfo(FILE* _File, class CAsset* _Asset);
class CAsset* LoadAssetInfo(FILE* _File, AssetType _type);

// Create Tile Sprite from Atlas
// TODO : 파일명에 L"TileSprite_%d"가 강제로 추가되는 부분 수정
void CreateTileSprite(const wstring _SpriteName, class CTexture* _AltasTex, int _Row, int _Col, Vec2 _TileSize, vector<class CSprite*>& _vecSprite);

// Object 유효성 체크
bool IsValid(class CObject*& _Object);

// 체크 패턴
void DrawCheckeredPattern(HDC _Hdc, int _Width, int _Height, int _SquareSize = 20);


#pragma region Delete Array, Vector, Map
template<typename T, int Size>
void Delete_Arr(T* (&_Arr)[Size])
{
	for (int i = 0; i < Size; ++i)
	{
		if (nullptr != _Arr[i])
			delete _Arr[i];
	}
}

template<typename T>
void Delete_Vec(vector<T*>& _vec)
{
	for (size_t i = 0; i < _vec.size(); ++i)
	{
		SAFE_DELETE(_vec[i]);
	}
	_vec.clear();
}

template<typename T1, typename T2>
void Delete_Map(map<T1, T2>& _map)
{
	typename map<T1, T2>::iterator iter = _map.begin();
	for (; iter != _map.end(); ++iter)
	{
		delete iter->second;
	}
	_map.clear();
}
#pragma endregion