#pragma once
#include "EvoLib.h"


namespace EvoLib
{
	// 変換クラス
	class Convert
	{
	public:

		// 向きに対応した角度
		static constexpr float TopAngle = 270.0f;	// 上
		static constexpr float BottomAngle = 90.0f;	// 下
		static constexpr float LeftAngle = 180.0f;	// 左
		static constexpr float RightAngle = 0.0f;	// 右

	public:

		/// <summary>
		/// カラーを255に変換
		/// </summary>
		/// <param name="color"></param>
		/// <returns>255変換されたカラー値を返す</returns>
		static VECTOR ConvertColorInto255(const VECTOR& color);

		/// <summary>
		/// 最大値と変換値を使い、パーセントを求める
		/// </summary>
		/// <param name="maxValue">最大値</param>
		/// <param name="convertValue">変換値</param>
		/// <returns>パーセンテージ</returns>
		static int PercentageRate(const float& maxValue, const float& convertValue);


		/// <summary>
		/// 値をパーセント変換
		/// </summary>
		/// <param name="maxValue">最大値</param>
		/// <param name="percentage">パーセント</param>
		/// <returns>パーセンテージ</returns>
		static int ConvertValueToPercent(const int& maxValue, const float& percentage);


		/// <summary>
		/// パーセントから値に変換
		/// </summary>
		/// <param name="maxValue">最大値</param>
		/// <param name="percentage">パーセント</param>
		/// <returns>変換された値</returns>
		static int ConvertFromPercentToValue(const int& maxValue, const float& percentage);


		/// <summary>
		/// 角度をラジアンに変換
		/// </summary>
		/// <param name="angle">角度</param>
		/// <returns>変換したラジアンを返す</returns>
		static float ConvertAngleToRadian(const float& angle);


		/// <summary>
		/// ラジアンを角度に変換
		/// </summary>
		/// <param name="radian">ラジアン</param>
		/// <returns>変換した角度を返す</returns>
		static float ConvertRadianToAngle(const float& radian);


		/// <summary>
		/// 向き情報を角度に変換
		/// </summary>
		/// <param name="direction">向き</param>
		/// <returns>角度</returns>
		static float ConvertDirectionToAngle(const Direction& direction);


		/// <summary>
		/// 角度情報を方向情報に変換
		/// </summary>
		/// <param name="angle">角度</param>
		/// <param name="addSubValue">増減値</param>
		/// <returns>方向情報</returns>
		static Direction ConvertAngleToDirection(const float& angle, const float addSubValue = 0.0f);


		/// <summary>
		/// フレームを秒に変換
		/// </summary>
		/// <param name="frame">フレーム</param>
		/// <param name="fps">FPS</param>
		/// <returns>秒</returns>
		static int ConvertFrameToSeconds(const int& frame, const int& fps = 0);

		/// <summary>
		/// フレームを秒に変換(改訂版)
		/// </summary>
		/// <param name="frame">フレーム</param>
		/// <param name="isInteger">整数値を返すかどうか</param>
		/// <param name="fps">FPS</param>
		/// <returns>変換された秒数を返す</returns>
		static float ConvertFrameToSeconds_Revision(const int& frame, bool isInteger = true, int fps = 0);


		/// <summary>
		/// 球情報へ変換
		/// </summary>
		/// <param name="pos">座標</param>
		/// <param name="radius">半径</param>
		/// <returns>球情報</returns>
		static Sphere ConvertSphereInfo(const VECTOR& pos, const float& radius);


		/// <summary>
		/// string型からfloat型に変換
		/// </summary>
		/// <param name="num">string型の数字</param>
		/// <returns>float型の数字</returns>
		static float ConvertingStringToFloat(const std::string& stringNum);

		/// <summary>
		/// float型からstring型に変換
		/// </summary>
		/// <param name="num">float型の数字</param>
		/// <returns>string型の数字</returns>
		static std::string ConvertingFloatToString(const float& num);

		/// <summary>
		/// フレームをミリ秒単位に変換
		/// </summary>
		/// <param name="frame">フレーム</param>
		/// <returns>ミリ秒単位を返す</returns>
		static int ConvertFrameCountToMillisecondUnit(const int& frame);


		/// <summary>
		/// 座標をセルに変換
		/// </summary>
		/// <param name="pos">座標</param>
		/// <param name="cellSize">セルサイズ</param>
		/// <returns>セル情報</returns>
		static Cell PosToCell(const Vec2& pos, const float& cellSize);

		/// <summary>
		/// セルを座標に変換
		/// </summary>
		/// <param name="cell">セル</param>
		/// <param name="cellSize">セルサイズ</param>
		/// <returns></returns>
		static Vec2 CellToPos(const Cell& cell, const float& cellSize);

		/// <summary>
		/// 2点の座標から直線の傾きとY軸の交点を求める
		/// </summary>
		/// <param name="pos1">座標1</param>
		/// <param name="pos2">座標2</param>
		/// <returns>直線情報</returns>
		static Line CalculateLine(const Vec2& pos1, const Vec2& pos2);

		/// <summary>
		/// 2つの直線交点を計算する
		/// </summary>
		/// <param name="line1">直線1</param>
		/// <param name="line2">直線2</param>
		/// <returns>交差情報(重なっているかどうかのフラグ,重なっている座標)</returns>
		static Intersection CalculateIntersection(const Line& line1, const Line& line2);

		/// <summary>
		/// 四角形情報から中心座標を求める
		/// </summary>
		/// <param name="square">四角形座標</param>
		/// <returns>四角形情報</returns>
		static Vec2 QuadrangularCenter(const Square& square);

		/// <summary>
		/// 四角形の中心点および、中心点からの各頂点距離の最大値を半径とした円の情報を返す
		/// </summary>
		/// <param name="square">四角形情報</param>
		/// <returns>円情報</returns>
		static Circle SquareToCircle(const Square& square);

		/// <summary>
		/// 矩形情報を四角形情報に変換する
		/// </summary>
		/// <param name="rect">矩形情報</param>
		/// <returns>四角形情報</returns>
		static Square RectToSquare(const Rect& rect);


		/// <summary>
		/// 座標を中心とした矩形情報に変換
		/// </summary>
		/// <param name="pos">中心座標</param>
		/// <param name="size">サイズ</param>
		/// <returns>矩形情報</returns>
		static Rect PosToRect(const Vec2& pos, const Vec2& size);
	};
}




