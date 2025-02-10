#pragma once

#define DECLARE_SINGLE(Name)						\
public:												\
	static Name*  GetInstance()						\
	{												\
		static Name instance;						\
		return &instance;							\
	}												\
private:											\
	Name();											\
	Name(const Name& _Origin) = delete;				\
	Name& operator = (const Name& _Other) = delete;	\
	~Name();

#define SAFE_DELETE(ptr)		\
	if (nullptr != ptr)			\
	{							\
		delete ptr;				\
		ptr = nullptr;			\
	}

#define CONTENT_PATH AssetManager::GetInstance()->GetContentPath()

#define DT TimeManager::GetInstance()->GetDeltaTime()

#define SELECT_PEN(dc, Pen)		CSelectGDI pen(dc, CEngine::GetInstance()->GetPen(Pen));
#define SELECT_BRUSH(dc, Brush) CSelectGDI brush(dc, CEngine::GetInstance()->GetBrush(Brush));