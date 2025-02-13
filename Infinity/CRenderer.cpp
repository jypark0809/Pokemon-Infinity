#include "pch.h"
#include "CRenderer.h"

CRenderer::CRenderer(ComponentType _Type)
	: CComponent(_Type)
	, m_SortingLayer(SortingLayer::NONE)
	, m_OrderInLayer(0)
{
}

CRenderer::~CRenderer()
{
}

void CRenderer::BeginPlay()
{
}

void CRenderer::Tick()
{
}

void CRenderer::FinalTick()
{
}
