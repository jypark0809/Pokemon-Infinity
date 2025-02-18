#pragma once
#include "CComponent.h"
class CRenderer :
    public CComponent
{
private:
    SortingLayer    m_SortingLayer;
    int             m_OrderInLayer;

public:
    virtual void BeginPlay() override;
    virtual void Tick() override;
    virtual void FinalTick() override;
    virtual void Render(HDC _hdc) = 0;

    SortingLayer GetSortingLayer() { return m_SortingLayer; }
    void SetSortingLayer(SortingLayer _SortingLayer) { m_SortingLayer = _SortingLayer; }

    int GetOrderInLayer() { return m_OrderInLayer; }
    void SetOrderInLayer(int _OrderInLayer) { m_OrderInLayer = _OrderInLayer; }

    virtual int Save(FILE* _File) = 0;
    virtual int Load(FILE* _File) = 0;

public:
    CRenderer(ComponentType type);
    virtual ~CRenderer();
};

