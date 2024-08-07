#pragma once
#include "EvoLib.h"

namespace EvoLib
{
	// 計算クラス
	class Calculation
	{

	public:

		// 計算(足し算、引き算)
		enum class CalculationType
		{
			Addition,	// 足し算
			Subtraction,// 引き算
		};


	public:

		/// <summary>
		/// サインカーブ値を求める
		/// </summary>
		/// <param name="currentFrame">現在のフレーム</param>
		/// <param name="maxFrame">最大フレーム</param>
		/// <param name="maxValue">サインカーブの最大値</param>
		/// <param name="isAbs">absを使用するかどうか</param>
		/// <returns>サインカーブ値</returns>
		static int SineCurve(int currentFrame, int maxFrame, int maxValue, bool isAbs = false);


		/// <summary>
		/// 2Dの振動
		/// </summary>
		/// <param name="currentFrame">現在のフレーム</param>
		/// <param name="maxFrame">振動させる最大フレーム</param>
		/// <param name="vibrationWidth">振動幅</param>
		/// <returns>2Dの振動値</returns>
		static Vec2 VibrationValue(int currentFrame, const int& maxFrame, const int& vibrationWidth);


		/// <summary>
		/// ループ番号
		/// </summary>
		/// <param name="minNumber">最小値</param>
		/// <param name="maxNumber">最大値</param>
		/// <param name="currentNumber">現在の値</param>
		/// <param name="isInverseLoop">逆ループするかどうか</param>
		/// <returns>変換された番号</returns>
		static int SelectLoopNumber(const int& minNumber, const int& maxNumber, const int& currentNumber, bool isInverseLoop = false);


		/// <summary>
		/// ある位置を基準とし、幅を考慮したグラフィックの座標を返す
		/// </summary>
		/// <param name="handle">グラフィックハンドル</param>
		/// <param name="num">グラフィックの個数</param>
		/// <param name="graphScale">グラフィックスケール</param>
		/// <param name="centerPos">基準とする座標</param>
		/// <param name="distancePos">幅とする座標</param>
		/// <param name="isSide">横かどうか</param>
		/// <returns>幅を考慮したグラフィック座標を返す</returns>
		static std::vector<Vec2> GraphicWidthCoordinate(const int& handle, const int& num, const float& graphScale, const Vec2& centerPos, const Vec2& distancePos, bool isSide = true);


		/// <summary>
		/// 座標を均等に並べる
		/// </summary>
		/// <param name="num">均等に並べる数</param>
		/// <param name="centerPos">基準とする位置</param>
		/// <param name="distancePos">幅とする座標</param>
		/// <param name="isSide">横に並べるかどうか</param>
		/// <returns>均等に並べた座標</returns>
		static std::vector<Vec2> SortCoordinateEqually(const int& num, const Vec2& centerPos, const Vec2& distancePos, bool isSide = true);


		/// <summary>
		/// ターゲットの範囲内かどうかの判定
		/// </summary>
		/// <param name="currentValue">現在の値</param>
		/// <param name="targetValue">ターゲットの値</param>
		/// <param name="addSubValue">加減算値</param>
		/// <returns>ターゲットの範囲内かどうか</returns>
		static bool IsTargetRangeValue(const float& currentValue, const float& targetValue, const float& addSubValue);


		/// <summary>
		/// 角度を加減算して、360度を超えたり、0度以下にならないように計算を行う
		/// </summary>
		/// <param name="currentAngle">現在の角度</param>
		/// <param name="addSubValue">加減算値</param>
		/// <param name="calculation">足し算か引き算かどうか</param>
		/// <param name="isInteger">整数値かどうか</param>
		/// <param name="isAdjustment">調整値を加えるかどうか</param>
		/// <returns>加減算を終えた角度を返す</returns>
		static float AngleLimitValueNotExceedToCalculate(const float& currentAngle, const float& addSubValue, EvoLib::Calculation::CalculationType calculation, bool isInteger = true, bool isAdjustment = true);


		/// <summary>
		/// 三平方の定理
		/// </summary>
		/// <param name="poa1">座標1</param>
		/// <param name="pos2">座標2</param>
		/// <returns>直角三角形の一辺の長さ</returns>
		static float ThreeSquareTheorem(const Vec2& poa1, const Vec2& pos2);

		/// <summary>
		/// 値が負の数かどうかを調べる
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <param name="value">調べる値</param>
		/// <returns>値が負の数かどうかのフラグ</returns>
		template <typename T>
		static bool IsValueNegativeCount(T& value);

		/// <summary>
		/// 線形補間数を求める
		/// </summary>
		/// <param name="pos">座標</param>
		/// <param name="vec">移動量</param>
		/// <param name="size">縦横幅</param>
		/// <returns>線形補間数</returns>
		static int InearInterpolationCount(const Vec2& pos, const Vec2& vec, const Vec2& size);

		/// <summary>
		/// 線形補間座標を求める
		/// </summary>
		/// <param name="pos">座標</param>
		/// <param name="vec">移動量</param>
		/// <param name="iinearInterpolationCount">線形補間数</param>
		/// <returns>線形補間座標</returns>
		static std::vector<Vec2> InearInterpolationPos(const Vec2& pos, const Vec2& vec, const int& iinearInterpolationCount);

		/// <summary>
		/// 矩形の移動範囲を計算
		/// </summary>
		/// <param name="rect">自身の矩形情報</param>
		/// <param name="maxCell">セルの最大数</param>
		/// <param name="cellSize">セルサイズ</param>
		/// <param name="cellData">二次元セルデータ</param>
		/// <param name="unusedCellNumber">地面セル番号</param>
		/// <returns>移動範囲</returns>
		static Rect CalculateRectangleMovementRange(const Rect& rect, const Cell& maxCell, const float& cellSize, const std::vector<std::vector<int>>& cellData, const std::vector<int> groundCellNumber);


		/// <summary>
		/// セルが範囲内かどうか
		/// </summary>
		/// <param name="cell">調べるセル</param>
		/// <param name="maxCell">最大セル</param>
		/// <param name="minCell">最小セル</param>
		/// <returns>セルが範囲内かどうかを返す</returns>
		static bool IsCellRange(const Cell& cell, const Cell& maxCell, const Cell& minCell);

		/// <summary>
		/// 上限下限値を設定
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <param name="x">数値</param>
		/// <param name="low">下限</param>
		/// <param name="high">上限</param>
		/// <returns></returns>
		template<typename T>
		static T Clamp(T x, T low, T high);


		// ターゲットに向かう移動量を求める
		static Vec2 TargetMoveValue(const Vec2& pos, const Vec2& targetPos, const float& moveSpeed);


	};
	template<typename T>
	inline bool Calculation::IsValueNegativeCount(T& value)
	{
		// 値が0以下ならば、false
		if (value > 0.0f)
		{
			return false;
		}

		return true;
	}
	template<typename T>
	inline T Calculation::Clamp(T x, T low, T high)
	{
		if (low >= x)
		{
			return low;
		}
		else if (x >= high)
		{
			return high;
		}

		return x;
	}
}