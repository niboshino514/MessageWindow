#pragma once
#include "EvoLib.h"

namespace EvoLib
{
	class Draw
	{
	public:

		// ループの方向
		enum class LoopDirection
		{
			Up,		// 上方向にループする
			Down,	// 下方向にループする
			Left,	// 左方向にループする
			Right,	// 右方向にループする
		};


		struct Color
		{
			float r = 0.0f;
			float g = 0.0f;
			float b = 0.0f;
		};


	public:

		/// <summary>
		/// 簡易背景描画
		/// </summary>
		/// <param name="graphHandle">画像ハンドル</param>
		/// <param name="screenSize">画面サイズ</param>
		/// <param name="isFlipImage">画像を反転するかどうか</param>
		static void DrawSimpleBackground(const int& graphHandle, const Vec2& screenSize, bool isFlipImage = false);

		/// <summary>
		/// 簡易背景ループ
		/// </summary>
		/// <param name="graphHandle">グラフィックのハンドル</param>
		/// <param name="currentFrame">現在の移動量</param>
		/// <param name="moveSpeed">背景の移動スピード</param>
		/// <param name="screenSize">画面サイズ</param>
		/// <param name="isSupportedImageInLoop">使用する画像がループに対応しているかどうか</param>
		/// <param name="loopDirection">ループする方向</param>
		/// <returns>現在の移動量を返す</returns>
		static float SimpleLoopBackground(const int& graphHandle, const float currentMoveValue, float moveSpeed, const Vec2 screenSize, bool isSupportedImageInLoop = false, LoopDirection loopDirection = LoopDirection::Left);

		/// <summary>
		/// 2Dグラフィックを3D空間に描画する　※graphHandle で指定する画像は８以上の２のｎ乗のピクセルサイズである必要があります
		/// </summary>
		/// <param name="graphHandle">グラフィックのハンドル</param>
		/// <param name="graphScale">グラフィックのスケール</param>
		/// <param name="angle">角度</param>
		/// <param name="pos">座標</param>
		/// <param name="color">カラーの値(最大値:1.0f)</param>
		static void DrawGprah3D_EvoLib(const int& graphHandle, const float& graphScale, const VECTOR& angle, const VECTOR& pos, Color color = { 1.0f,1.0f,1.0f });

		/// <summary>
		/// 3D空間にキューブを描画する
		/// </summary>
		/// <param name="centerPos">中心座標</param>
		/// <param name="cubeScale">一辺の長さ</param>
		/// <param name="alphaValue">透明度</param>
		/// <param name="lineThickness">線の太さ</param>
		/// <param name="color">カラーの値(最大値:1.0f)</param>
		static void DrawCube3D_EvoLib(const VECTOR& centerPos, const VECTOR& oneSideLength, int alphaValue = 255, int lineThickness = 1, Color color = { 0.0f,1.0f, 0.0f });

	};
}
