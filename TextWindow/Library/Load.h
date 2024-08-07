#pragma once
#include "EvoLib.h"


namespace EvoLib
{
	class Load
	{

	public:
		// 分割数
		struct DivNum
		{
			// 横の分割数
			const int x = 1;
			// 縦の分割数
			const int y = 1;
		};


		// グラフィック情報
		struct GraphicInfo
		{
			// ファイルパス
			const char* filePath = "";

			// 座標
			Vec2 pos = Vec2(0.0f, 0.0f);

			// グラフィックスケール
			float scale = 1.0f;

			// グラフィックの分割数
			DivNum div = DivNum();
		};


		// グラフィック分割情報
		struct DivGraphInfo
		{
			// ハンドル
			std::vector<int>handle;

			// グラフィックのスケール
			Vec2 scale = Vec2(0.0f, 0.0f);
		};

	public:

		/// <summary>
		/// グラフィックの分割
		/// </summary>
		/// <param name="filePath">グラフィックのファイルパス</param>
		/// <param name="div_x">横向きに対する分割数</param>
		/// <param name="div_y">縦向きに対する分割数</param>
		/// <returns></returns>
		static DivGraphInfo LoadDivGraph_EvoLib(const char* filePath, const int& div_x, const int& div_y);

		/// <summary>
		/// グラフィックの分割　改定版
		/// </summary>
		/// <param name="filePath">グラフィックのファイルパス</param>
		/// <param name="div">縦横の分割数</param>
		/// <returns>分割されたグラフィックハンドルを返す</returns>
		static std::vector<int> LoadDivGraph_EvoLib_Revision(const char* filePath, const DivNum& div);


		/// <summary>
		/// フォントの読み込み
		/// </summary>
		/// <param name="filePath">フォントファイルパス</param>
		/// <param name="fontName">フォント名</param>
		/// <param name="fontSize">フォントサイズ</param>
		/// <returns>フォント情報</returns>
		static int LoadFont(const char* filePath, const char* fontName, const int& fontSize);


	};
}