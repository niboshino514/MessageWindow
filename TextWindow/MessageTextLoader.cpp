#include "MessageTextLoader.h"
#include "EvoLib.h"
#include <iostream>

namespace
{
	// ファイルPath
	const char* const kTextSettingDataFilePath = "Data/CSV/TextSetting.csv";

	const char* const kTalkDataFilePath = "Data/CSV/TalkData_0.csv";
}

MessageTextLoader::MessageTextLoader():
	m_loadData()
{
}

MessageTextLoader::~MessageTextLoader()
{
}


MessageTextLoader::LoadData MessageTextLoader::LoadTextData()
{
	// テキスト設定データの読み込み
	LoadTextSettingData();
	
	// 会話データの読み込み
	LoadTalkData();

	// データを返す
	return m_loadData;
}

void MessageTextLoader::LoadTextSettingData()
{
	// テキスト設定データファイルパス
	const char* textSettingDataFilePath = kTextSettingDataFilePath;


	// テキスト設定データの読み込み
	std::vector<std::vector<std::string>> csvFileData =
		EvoLib::File::CsvFileLoading_Revision(textSettingDataFilePath, true, 2);


	// フォントデータの読み込み
	CSVFontData fontData = CSVFontData();

	// フォントデータ関連
	{
		// フォントファイルパス
		fontData.fontFilePath = csvFileData[0];
		// フォント名
		fontData.fontName = csvFileData[1];
		// 通常フォントサイズ
		fontData.normalFontSize = std::stoi(csvFileData[2][0]);
		// 小さいフォントサイズ
		fontData.smallFontSize = std::stoi(csvFileData[3][0]);
		// 大きいフォントサイズ
		fontData.bigFontSize = std::stoi(csvFileData[4][0]);


		// キャラクター名を描画する際のフォントサイズ
		fontData.characterNameFontSize = std::stoi(csvFileData[5][0]);
		// キャラクターの最大文字数
		fontData.characterNameMaxCharCount = std::stoi(csvFileData[6][0]);
		// キャラクター名の文字横間隔
		fontData.characterNameCharInterval = std::stoi(csvFileData[7][0]);
		// キャラクター名のフォントタイプ
		fontData.characterNameFontType = std::stoi(csvFileData[8][0]);
	}






	// キャラクターデータの読み込み
	CSVCharacterData characterData = CSVCharacterData();

	// キャラクターデータ関連
	{
		// キャラクターファイルパス
		characterData.characterFilePath = csvFileData[9];
		// キャラクター名
		characterData.characterName = csvFileData[10];
		// 画像拡大率
		for (int i = 0; i < static_cast<int>(csvFileData[11].size()); i++)
		{
			characterData.characterScale.push_back(std::stod(csvFileData[11][i]));
		}
		// 画像の縦分割数
		for (int i = 0; i < static_cast<int>(csvFileData[12].size()); i++)
		{
			characterData.characterSplitY.push_back(std::stoi(csvFileData[12][i]));
		}
		// 画像の横分割数
		for (int i = 0; i < static_cast<int>(csvFileData[13].size()); i++)
		{
			characterData.characterSplitX.push_back(std::stoi(csvFileData[13][i]));
		}
		// 画像が右向きかどうか
		for (int i = 0; i < static_cast<int>(csvFileData[14].size()); i++)
		{
			characterData.characterIsRight.push_back(EvoLib::Convert::ConvertStringToBool(csvFileData[14][i]));
		}
		// 画像の上下調整値
		for (int i = 0; i < static_cast<int>(csvFileData[15].size()); i++)
		{
			characterData.characterAdjustY.push_back(std::stof(csvFileData[15][i]));
		}
		// 画像の左右調整値
		for (int i = 0; i < static_cast<int>(csvFileData[16].size()); i++)
		{
			characterData.characterAdjustX.push_back(std::stof(csvFileData[16][i]));
		}


		// キャラクターが話す時のボイスファイルパス
		characterData.characterVoiceFilePath = csvFileData[17];
		// キャラクターが話す際のボイス音量
		for (int i = 0; i < static_cast<int>(csvFileData[18].size()); i++)
		{
			characterData.characterVoiceVolume.push_back(std::stoi(csvFileData[18][i]));
		}

		// 画面下から画像の中心までの距離
		characterData.characterCenterPosOffsetY = std::stof(csvFileData[19][0]);
		// 画面端から画像の中心までの距離
		characterData.characterCenterPosOffsetX = std::stof(csvFileData[20][0]);

		// キャラクターが話していない時の画像の透明度パーセンテージ
		characterData.characterNotSpeakAlphaPercentage = std::stoi(csvFileData[21][0]);
		// キャラクターが話していない時の画像中心からの距離
		characterData.characterNotSpeakCenterPosOffsetY = std::stof(csvFileData[22][0]);
		// 画像移動速度
		characterData.characterMoveSpeed = std::stof(csvFileData[23][0]);

	}

	// メッセージウィンドウデータの読み込み
	CSVMessageWindowData messageWindowData = CSVMessageWindowData();

	// メッセージウィンドウ関連
	{
		// メッセージウィンドウの横幅
		messageWindowData.messageWindowWidth = std::stof(csvFileData[24][0]);

		// 画面端からのメッセージウィンドウの距離
		messageWindowData.messageWindowMargin = std::stof(csvFileData[25][0]);

		// 画面下からのメッセージウィンドウの距離
		messageWindowData.messageWindowPosOffsetY = std::stof(csvFileData[26][0]);
	}


	// エラー確認
	{
		// ファイルパス
		const std::string filePath = textSettingDataFilePath;
		// エラーメッセージ
		std::string errorMsg = "[" + filePath + "] ";


		// フォントデータ
		{
			// フォントファイルパスのサイズ
			const int fontFilePathSize = static_cast<int>(fontData.fontFilePath.size());
			// フォント名のサイズ
			const int fontNameSize = static_cast<int>(fontData.fontName.size());

			// サイズが違う場合、エラーメッセージを表示
			if (fontFilePathSize != fontNameSize)
			{
				// エラーメッセージを表示
				EvoLib::Assert::ErrorMessageBox(errorMsg + "テキスト設定のフォント関連での数が一致しないようです。");
			}
		}

		// キャラクターデータ
		{
			// キャラクターデータのサイズ
			const int characterGraphFilePathSize = 
				static_cast<int>(characterData.characterFilePath.size());
			// キャラクターデータのサイズ
			const int characterNameSize = 
				static_cast<int>(characterData.characterName.size());
			// 画像拡大率のサイズ
			const int characterScaleSize = 
				static_cast<int>(characterData.characterScale.size());
			// キャラクターの横分割数のサイズ
			const int characterSplitXSize = 
				static_cast<int>(characterData.characterSplitX.size());
			// キャラクターが右向きかどうかのサイズ
			const int characterIsRightSize = 
				static_cast<int>(characterData.characterIsRight.size());
			// 画像の上下調整値のサイズ
			const int characterAdjustYSize = 
				static_cast<int>(characterData.characterAdjustY.size());
			// 画像の左右調整値のサイズ
			const int characterAdjustXSize = 
				static_cast<int>(characterData.characterAdjustX.size());

			// サイズが違う場合、エラーメッセージを表示
			if (characterGraphFilePathSize != characterNameSize ||
				characterGraphFilePathSize != characterScaleSize ||
				characterGraphFilePathSize != characterSplitXSize ||
				characterGraphFilePathSize != characterIsRightSize ||
				characterGraphFilePathSize != characterAdjustYSize ||
				characterGraphFilePathSize != characterAdjustXSize)
			{
				// エラーメッセージを表示
				EvoLib::Assert::ErrorMessageBox(errorMsg + "テキスト設定のキャラクター関連での数が一致しないようです。");	
			}
		}
	}




	// データを格納
	m_loadData.fontData = fontData;
	m_loadData.characterData = characterData;
	m_loadData.messageWindowData = messageWindowData;
}

void MessageTextLoader::LoadTalkData()
{
	std::string filePath = kTalkDataFilePath;


	// テキスト設定データの読み込み
	std::vector<std::vector<std::string>> csvFileData =
		EvoLib::File::CsvFileLoading_Revision(kTalkDataFilePath, true, 0);



	// ファイルサイズが1以下の場合、エラーメッセージを表示
	if (static_cast<int>(csvFileData.size()) <= 1)
	{
		EvoLib::Assert::ErrorMessageBox("[" + filePath + "] " + "にはデータがないか、デフォルトのデータしか存在しないようです。");
	}


	// デフォルトのテキストデータ
	CSVTakeData defaultTakeData = CSVTakeData();
	{
		// 話す文章
		defaultTakeData.talkText = csvFileData[0][0];

		// 話すキャラクター番号
		defaultTakeData.talkCharacterNo = std::stoi(csvFileData[0][1]);

		// キャラクターの表情番号
		defaultTakeData.talkFaceNo = std::stoi(csvFileData[0][2]);

		// 右端に表示するかどうか
		defaultTakeData.isRight = EvoLib::Convert::ConvertStringToBool(csvFileData[0][3]);

		// 反転描画するかどうか
		defaultTakeData.isFlip = EvoLib::Convert::ConvertStringToBool(csvFileData[0][4]);

		// フォントカラー
		{
			// カラーコードに変換
			const std::string color = "0x" + csvFileData[0][5];
			// フォントカラー
			defaultTakeData.fontColor = std::stoi(color, nullptr, 16);
		}

		// フォントの透明度
		defaultTakeData.fontAlpha = std::stoi(csvFileData[0][6]);

		// フォントの文字サイズタイプ
		defaultTakeData.fontSizeType = std::stoi(csvFileData[0][7]);

		// 文字を震わせるかどうか
		defaultTakeData.isShake = EvoLib::Convert::ConvertStringToBool(csvFileData[0][8]);

		// 一文字を表示するのにかかるフレーム数
		defaultTakeData.drawCharFrame = std::stoi(csvFileData[0][9]);

		// フォントタイプ
		defaultTakeData.fontType = std::stoi(csvFileData[0][10]);

		// 文字横間隔
		defaultTakeData.charInterval = std::stoi(csvFileData[0][11]);

		// 文字縦間隔
		defaultTakeData.lineInterval = std::stof(csvFileData[0][12]);

		// キャラクター名カラー
		{
			// カラーコードに変換
			const std::string color = "0x" + csvFileData[0][13];

			// キャラクター名カラー
			defaultTakeData.characterNameColor = std::stoi(color, nullptr, 16);
		}
		// キャラクター名
		defaultTakeData.characterName = csvFileData[0][14].c_str();
	}

	std::vector<CSVTakeData> talkData;

	for (int i = 1; i < static_cast<int>(csvFileData.size()); i++)
	{
		// テキストデータ
		CSVTakeData tempTakeData = CSVTakeData();

		tempTakeData = defaultTakeData;

		// ファイルサイズを調べる
		const int size = static_cast<int>(csvFileData[i].size());

		
		// 話す文章
		if (!IsEmptyData(csvFileData[i][0]))
		{
			tempTakeData.talkText = csvFileData[i][0];
		}

		// 話すキャラクター番号
		if (!IsEmptyData(csvFileData[i][1]))
		{
			tempTakeData.talkCharacterNo = std::stoi(csvFileData[i][1]);
		}

		// キャラクターの表情番号
		if (!IsEmptyData(csvFileData[i][2]))
		{
			tempTakeData.talkFaceNo = std::stoi(csvFileData[i][2]);
		}

		// 右端に表示するかどうか
		if (!IsEmptyData(csvFileData[i][3]))
		{
			tempTakeData.isRight = EvoLib::Convert::ConvertStringToBool(csvFileData[i][3]);
		}

		// 反転描画するかどうか
		if (!IsEmptyData(csvFileData[i][4]))
		{
			tempTakeData.isFlip = EvoLib::Convert::ConvertStringToBool(csvFileData[i][4]);
		}

		// フォントカラー
		if (!IsEmptyData(csvFileData[i][5]))
		{
			// カラーコードに変換
			const std::string color = "0x" + csvFileData[i][5];

			tempTakeData.fontColor = std::stoi(color, nullptr, 16);
		}

		// フォントの透明度
		if (!IsEmptyData(csvFileData[i][6]))
		{
			tempTakeData.fontAlpha = std::stoi(csvFileData[i][6]);
		}

		// フォントの文字サイズタイプ
		if (!IsEmptyData(csvFileData[i][7]))
		{
			tempTakeData.fontSizeType = std::stoi(csvFileData[i][7]);
		}

		// 文字を震わせるかどうか
		if (!IsEmptyData(csvFileData[i][8]))
		{
			tempTakeData.isShake = EvoLib::Convert::ConvertStringToBool(csvFileData[i][8]);
		}

		// 一文字を表示するのにかかるフレーム数
		if (!IsEmptyData(csvFileData[i][9]))
		{
			tempTakeData.drawCharFrame = std::stoi(csvFileData[i][9]);
		}

		// フォントタイプ
		if (!IsEmptyData(csvFileData[i][10]))
		{
			tempTakeData.fontType = std::stoi(csvFileData[i][10]);
		}

		// 文字横間隔
		if (!IsEmptyData(csvFileData[i][11]))
		{
			tempTakeData.charInterval = std::stoi(csvFileData[i][11]);
		}

		// 文字縦間隔
		if (!IsEmptyData(csvFileData[i][12]))
		{
			tempTakeData.lineInterval = std::stof(csvFileData[i][12]);
		}

		// キャラクター名カラー
		if (!IsEmptyData(csvFileData[i][13]))
		{
			// カラーコードに変換
			const std::string color = "0x" + csvFileData[i][13];

			tempTakeData.characterNameColor = std::stoi(color, nullptr, 16);
		}

		if (14 >= size)
		{
			// キャラクター名
			tempTakeData.characterName = m_loadData.characterData.characterName[tempTakeData.talkCharacterNo];
		}
		else
		{
			// キャラクター名
			if (!IsEmptyData(csvFileData[i][14]))
			{
				tempTakeData.characterName = csvFileData[i][14].c_str();
			}
			else
			{
				tempTakeData.characterName = m_loadData.characterData.characterName[tempTakeData.talkCharacterNo];
			}
		}

		// データを格納
		talkData.push_back(tempTakeData);
	}


	// データを格納
	m_loadData.talkData = talkData;
}

bool MessageTextLoader::IsEmptyData(const std::string& str)
{
	// 文字列が空文字の場合、trueを返す
	if (str == "")
	{
		return true;
	}

	// 文字列が空文字でない場合、falseを返す
	return false;
}
