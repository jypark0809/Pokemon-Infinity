#pragma once

enum class Key
{
	LBUTTON	= VK_LBUTTON,
	RBUTTON	= VK_RBUTTON,

	UP			= VK_UP,
	DOWN		= VK_DOWN,
	LEFT		= VK_LEFT,
	RIGHT		= VK_RIGHT,

	CTRL		= VK_CONTROL,		// ctrl
	LSHIFT		= VK_LSHIFT,		// shift
	Enter		= VK_RETURN,		// OEnter
	ESC			= VK_ESCAPE,		// esc
	SPACE		= VK_SPACE,			// space

	COUNT
};

enum class KeyState
{
	NONE,
	TAP,
	PRESSED,
	RELEASED,

	COUNT
};

class KeyManager
{
	DECLARE_SINGLE(KeyManager);

private:
	Vec2				m_MousePos;
	vector<KeyState>	m_KeyStates;

public:
	void Init();
	void Tick();

	Vec2 GetMousePos() { return m_MousePos; }
	bool GetButton(Key _key) { return GetKeyState(_key) == KeyState::PRESSED; }		// 누르고 있을 때	
	bool GetButtonDown(Key _key) { return GetKeyState(_key) == KeyState::TAP; }		// 맨 처음 눌렀을 때
	bool GetButtonUp(Key _key) { return GetKeyState(_key) == KeyState::RELEASED; }	// 누른 상테에서 땠을 때

private:
	KeyState GetKeyState(Key _key) { return m_KeyStates[static_cast<BYTE>(_key)]; }
};

