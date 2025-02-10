#pragma once
#include "CAsset.h"

class CSprite;
class CFlipbookPlayer;

class CFlipbook :
    public CAsset
{
private:
    CFlipbookPlayer*    m_fbPlayer;
    vector<CSprite*>    m_Sprites;
    int                 m_Index;
    float               m_Time;
    bool                m_Completed;

public:
    CSprite* GetSprite() { return m_Sprites[m_Index]; }
    CSprite* GetSprite(UINT _Index) { return m_Sprites[_Index]; }
    UINT GetMaxCount() { return (UINT)m_Sprites.size(); }
    void SetAnimator(class CFlipbookPlayer* _fbPlayer) { m_fbPlayer = _fbPlayer; }
    bool IsCompleted() { return m_Completed; }
    void Reset();

public:
    virtual int Save(const wstring& _RelativePath) override;
    virtual int Load(const wstring& _RelativePath) override;
    void FinalTick();

    void AddSprite(CSprite* _Sprite) { m_Sprites.push_back(_Sprite); }

public:
    CFlipbook();
    ~CFlipbook();

    friend class CFlipbookPlayer;
};

