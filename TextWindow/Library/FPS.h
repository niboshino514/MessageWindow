#pragma once
#include "EvoLib.h"

namespace EvoLib
{
	class FPS
	{
	public:

		// DXLib‚ð60FPS‚Å“®‚©‚·
		static constexpr int Dxlib_60FPS = 16667;
		// FPS
		static constexpr int Fps = 60;


		// FPS‚ÌŽæ“¾
		static int GetFPS_EvoLib();
	};
}