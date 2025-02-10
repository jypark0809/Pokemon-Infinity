#include "pch.h"
#include "CComponent.h"

CComponent::CComponent(ComponentType _Type)
	: m_Owner(nullptr)
	, m_Type(_Type)
{
}

CComponent::~CComponent()
{
}

void CComponent::BeginPlay()
{
}

void CComponent::Render(HDC _hdc)
{
}