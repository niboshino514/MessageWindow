#pragma once
#include <DxLib.h>
#include <vector>
#include <string>
#include "Vec2.h"

/// <summary>
/// 向き
/// </summary>
enum class Direction
{
	Top,	// 上
	Bottom,	// 下
	Left,	// 左
	Right,	// 右
	DirectionNum,// 方向数
};

/// <summary>
/// 球体情報
/// </summary>
struct Sphere
{
	// 座標
	VECTOR pos = { 0.0f,0.0f,0.0f };
	// 半径
	float radius = 0.0f;
};

/// <summary>
/// セル情報
/// </summary>
struct Cell
{
	int x = 0;	// セルX
	int y = 0;	// セルY
};

// 円構造体
struct Circle
{
	// 中心座標
	Vec2 centerPos = Vec2();

	// 円の半径
	float radius = 0.0f;
};

/// <summary>
/// 矩形情報
/// </summary>
struct Rect
{
	float top = 0.0f;	// 上
	float bottom = 0.0f;// 下
	float left = 0.0f;	// 左
	float right = 0.0f;	// 右
};

/// <summary>
/// 四角形情報
/// </summary>
struct Square
{
	// 左上座標
	Vec2 A = Vec2();

	// 右上座標
	Vec2 B = Vec2();

	// 右下座標
	Vec2 C = Vec2();

	// 左下座標
	Vec2 D = Vec2();
};


/// <summary>
/// 交差の構造体
/// </summary>
struct Intersection
{
	// 交差したかどうかのフラグ
	bool isFrag = false;

	// 交差座標
	Vec2 pos = Vec2(0.0f, 0.0f);
};

/// <summary>
/// 直線情報
/// </summary>
struct Line
{
	// 傾き
	float a = 0.0f; 
	// y軸との交点
	float b = 0.0f; 

	// 始点
	Vec2 start = Vec2();
	// 終点
	Vec2 end = Vec2();
};

/// <summary>
/// 三角形情報
/// </summary>
struct Triangle
{
	// 座標1
	Vec2 pos_1 = Vec2();

	// 座標2
	Vec2 pos_2 = Vec2();

	// 座標3
	Vec2 pos_3 = Vec2();
};

namespace EvoLib
{

	// アサートクラス
	class Assert
	{
	public:

		/// <summary>
		/// エラーメッセージ
		/// </summary>
		/// <param name="errorMessage">エラーメッセージ</param>
		static void ErrorMessage(const std::string& errorMessage);



		
		/// <summary>
		/// メッセージボックス
		/// </summary>
		/// <param name="errorMessage">エラーメッセージ</param>
		static void ErrorMessageBox(const std::string& errorMessage);
	};

	


	

}



#include "FPS.h"
#include "Convert.h"
#include "Collision.h"
#include "Calculation.h"
#include "Load.h"
#include "Draw.h"
#include "File.h"