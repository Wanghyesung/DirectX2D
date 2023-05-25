#pragma once

#include "Engine.h"
#include "WGraphicDevice_Dx11.h"
namespace W
{
	using namespace W::math;

	enum class eKeyCode
	{
		Q, W, E, R, T, Y, U, I, O, P,
		A, S, D, F, G, H, J, K, L,
		Z, X, C, V, B, N, M,

		UP, DOWN, LEFT, RIGHT, SPACE,
		LBUTTON, RBUTTON,
		END = 33,
	};

	enum class eKeyState
	{
		Down,
		Pressed,
		Up,
		None,
	};

	class Input
	{
	public:
		struct Key
		{
			eKeyCode key;
			eKeyState state;
			bool bPressed;
		};

		static void Initialize();
		static void Update();
		static void Render(HDC hdc);

		inline static eKeyState GetKeyState(eKeyCode keyCode)
		{
			return m_vecKeys[(UINT)keyCode].state;
		};

		//GetKey()		키를 누르는 시간만큼 true를 반환
		//GetKeyDown()	키를 눌렀을 때, 딱 한번 true를 반환
		//GetKeyUp()	키를 누르다 땠을 때, 딱 한번 true를 반환

		static __forceinline bool GetKey(eKeyCode keyCode)
		{
			return m_vecKeys[static_cast<UINT>(keyCode)].state == eKeyState::Pressed;
		}

		static __forceinline bool GetKeyDown(eKeyCode keyCode)
		{
			return m_vecKeys[static_cast<UINT>(keyCode)].state == eKeyState::Down;
		}

		static __forceinline bool GetKeyUp(eKeyCode keyCode)
		{
			return m_vecKeys[static_cast<UINT>(keyCode)].state == eKeyState::Up;
		}

		static __forceinline Vector2 GetMousePos() { return m_vMousePos; }

	private:
		static std::vector<Key> m_vecKeys;
		static Vector2 m_vMousePos;
	};

}


