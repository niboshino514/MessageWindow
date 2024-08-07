#pragma once
#include "EvoLib.h"

namespace EvoLib
{
	class File
	{

	public:

		// 読み取るタイプ
		enum class LoadType
		{
			Noramal,// 通常
			SkipFirstLine,	// 一行目をスキップする
			SkipOneColumn,	// 各一列目をスキップする
			DoubleSkip,		// 一行目と各一列目をスキップする
		};


	private:

		/// <summary>
		/// 文字列を分割して返す
		static std::vector<std::string> Split(const std::string& input, const char& delimiter);
	public:

		/// <summary>
		/// ファイルが存在するかどうかを確認
		/// </summary>
		/// <param name="name">ファイル名</param>
		/// <returns>そのファイルが存在するかどうかを返す</returns>
		static bool IsFileExist(const std::string& name);


		/// <summary>
		/// CSVファイルを読み込む
		/// </summary>
		/// <param name="filePath">ファイルパス</param>
		/// <param name="isLoadFirstLine">最初の一行を読み込むかどうか</param>
		/// <returns>読み込んだ文字列を返す</returns>
		static std::vector<std::vector<std::string>> CsvFileLoading(const std::string& filePath, bool isLoadFirstLine = true);

		/// <summary>
		/// CSVファイルを読み込む(改訂版)
		/// </summary>
		/// <param name="filePath">ファイルパス</param>
		/// <param name="isLoadFirstLine">最初の一行を読み込むかどうか</param>
		/// <param name="isLoadOneColumn">最初の一列を読み込むかどうか</param>
		/// <returns>読み込んだ文字列を返す</returns>
		static std::vector<std::vector<std::string>> CsvFileLoading_Revision(const std::string& filePath, LoadType loadType = LoadType::Noramal);

		/// <summary>
		/// 簡易CSVファイル書き込み
		/// </summary>
		/// <param name="fileName">ファイル名</param>
		/// <param name="writingText">書き込むテキスト</param>
		static void SimpleCsvFileWriting(const std::string& fileName, const std::string& writingText);
	};
}