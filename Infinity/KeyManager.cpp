#include "pch.h"
#include "KeyManager.h"

// UINT8_MAX = 0xffui8
// 0xff : 16진수 리터럴로, 255를 나타냄
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
			// 이번 프레임에서 눌려있다.
			if (asciiKeys[i] & 0x80)
			{
				// 이전 프레임에 키를 누른 상태라면 PRESSED
				if (KeyState::TAP == m_KeyStates[i] || KeyState::PRESSED == m_KeyStates[i])
				{
					m_KeyStates[i] = KeyState::PRESSED;
				}
				// 지금은 눌려있는데, 이전에는 안눌려있었다.
				else
				{
					m_KeyStates[i] = KeyState::TAP;
				}
			}
			// 지금 안눌려있다.
			else
			{
				// 이전에 눌려있었다면
				if (KeyState::TAP == m_KeyStates[i] || KeyState::PRESSED == m_KeyStates[i])
				{
					m_KeyStates[i] = KeyState::RELEASED;
				}
				// 이전에 안눌려 있었다면
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
