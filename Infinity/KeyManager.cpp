#include "pch.h"
#include "KeyManager.h"

// UINT8_MAX = 0xffui8
// 0xff : 16���� ���ͷ���, 255�� ��Ÿ��
// ui8 : unsinged int 8
#define KEY_TYPE_COUNT static_cast<UINT>(UINT8_MAX) + 1

KeyManager::KeyManager()
{

}

KeyManager::~KeyManager()
{

}

void KeyManager::Init()
{
	m_KeyStates.resize(KEY_TYPE_COUNT, KeyState::NONE);
}

void KeyManager::Tick()
{
	BYTE asciiKeys[KEY_TYPE_COUNT] = {};
	if (::GetKeyboardState(asciiKeys) == false)
		return;

	if (CEngine::GetInstance()->GetMainWnd() == GetFocus())
	{
		for (UINT i = 0; i < KEY_TYPE_COUNT; ++i)
		{
			// �̹� �����ӿ��� �����ִ�.
			if (asciiKeys[i] & 0x80)
			{
				// ���� �����ӿ� Ű�� ���� ���¶�� PRESSED
				if (KeyState::TAP == m_KeyStates[i] || KeyState::PRESSED == m_KeyStates[i])
				{
					m_KeyStates[i] = KeyState::PRESSED;
				}
				// ������ �����ִµ�, �������� �ȴ����־���.
				else
				{
					m_KeyStates[i] = KeyState::TAP;
				}
			}
			// ���� �ȴ����ִ�.
			else
			{
				// ������ �����־��ٸ�
				if (KeyState::TAP == m_KeyStates[i] || KeyState::PRESSED == m_KeyStates[i])
				{
					m_KeyStates[i] = KeyState::RELEASED;
				}
				// ������ �ȴ��� �־��ٸ�
				else
				{
					m_KeyStates[i] = KeyState::NONE;
				}
			}
		}

		// Mouse
		POINT point = {};
		::GetCursorPos(&point);
		::ScreenToClient(CEngine::GetInstance()->GetMainWnd(), &point);
		m_MousePos = point;
	}
	else
	{
		for (UINT i = 0; i < KEY_TYPE_COUNT; ++i)
		{
			if (m_KeyStates[i] == KeyState::PRESSED || m_KeyStates[i] == KeyState::TAP)
				m_KeyStates[i] = KeyState::RELEASED;
			if (m_KeyStates[i] == KeyState::RELEASED)
				m_KeyStates[i] = KeyState::NONE;
		}
	}
}
