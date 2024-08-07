#pragma once
#include "EvoLib.h"

namespace EvoLib
{
	// 衝突クラス
	class Collision
	{
	public:

		/// <summary>
		/// 球の衝突判定
		/// </summary>
		/// <param name="sphere1">球情報1</param>
		/// <param name="sphere2">球情報2</param>
		/// <returns>衝突したかどうかを返す</returns>
		static bool SphereCollision(const Sphere& sphere1, const Sphere& sphere2);


		/// <summary>
		/// 円と四角形との当たり判定
		/// </summary>
		/// <param name="circle">円情報</param>
		/// <param name="square">四角形情報</param>
		/// <returns>円と四角形が当たったかどうかを返す</returns>
		static bool IsAABBCollisionDetection(const Circle& circle, const Square& square);

		/// <summary>
		/// 円同士の当たり判定
		/// </summary>
		/// <param name="circle1">円情報1</param>
		/// <param name="circle2">円情報2</param>
		/// <returns>円同士の衝突判定フラグ</returns>
		static bool IsCircleToCircle(const Circle& circle1, const Circle& circle2);

		/// <summary>
		/// 三角形と四角形の当たり判定
		/// </summary>
		/// <param name="triangle">三角形情報</param>
		/// <param name="square">四角形情報</param>
		/// <returns>三角形と四角形の衝突判定フラグ</returns>
		static bool IsTriangleToSquare(const Triangle& triangle, const Square& square);

		/// <summary>
		/// 四角形同士の当たり判定
		/// </summary>
		/// <param name="square1">四角形1</param>
		/// <param name="square2">四角形2</param>
		/// <returns>四角形同士の衝突判定フラグ</returns>
		static bool IsSquareToSquare(const Square& square1, const Square& square2);

		/// <summary>
		/// 線分同士が当たっているかどうかを調べる
		/// </summary>
		/// <param name="line1">線分1</param>
		/// <param name="line2">線分２</param>
		/// <returns>線分同士の衝突判定フラグ</returns>
		static bool IsLineToLine(const Line& line1, const Line& line2);

		/// <summary>
		/// ポリゴンの中にポイント座標が入っているかどうかを調べる
		/// </summary>
		/// <param name="point">座標</param>
		/// <param name="polygon">ポリゴン</param>
		/// <returns>ポリゴンの中にポイント座標が入っているかどうか</returns>
		static bool PointInPolygon(const Vec2& point, const std::vector<Vec2>& polygon);


	};
}