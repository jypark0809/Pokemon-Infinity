#pragma once
#include "CComponent.h"
class CRenderer :
    public CComponent
{
private:
    SortingLayer    m_SortingLayer;
    int             m_OrderInLayer;

public:
    SortingLayer GetSortingLayer() { return m_SortingLayer; }
    void SetSortingLayer(SortingLayer _SortingLayer) { m_SortingLayer = _SortingLayer; }

    int GetOrderInLayer() { return m_OrderInLayer; }
    void SetOrderInLayer(int _OrderInLayer) { m_OrderInLayer = _OrderInLayer; }

    virtual void BeginPlay() override;
    virtual void Tick() override;
    virtual void FinalTick() override;
    virtual void Render(HDC _hdc) = 0;

public:
    CRenderer(ComponentType type);
    virtual ~CRenderer();
};

