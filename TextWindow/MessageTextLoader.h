#pragma once
#include <string>
#include <vector>


class MessageTextLoader
{
public:

	// ロードしたフォントデータ
	struct CSVFontData
	{
		// フォントファイルパス
		std::vector<std::string> fontFilePath;
		// フォント名
		std::vector<std::string> fontName;
		// フォントサイズ
		int fontSize = 0;


		// キャラクター名を描画する際のフォントサイズ
		int characterNameFontSize = 0;
		// キャラクターの最大文字数
		int characterNameMaxCharCount = 0;
		// キャラクター名の文字横間隔
		int characterNameCharInterval = 0;
		// キャラクター名のフォントタイプ
		int characterNameFontType = 0;
	};


	// ロードしたキャラクターデータ
	struct CSVCharacterData
	{
		// キャラクターファイルパス
		std::vector<std::string> characterFilePath;
		// キャラクター名
		std::vector<std::string> characterName;
		// 画像拡大率
		std::vector<double> characterScale;
		// 画像の縦分割数
		std::vector<int> characterSplitY;
		// 画像の横分割数
		std::vector<int> characterSplitX;
		

		// 画像が右向きかどうか
		std::vector<bool> characterIsRight;
		// 画像の上下調整値
		std::vector<float> characterAdjustY;
		// 画像の左右調整値
		std::vector<float> characterAdjustX;


		// キャラクターが話す時のボイスファイルパス
		std::vector<std::string> characterVoiceFilePath;
		// キャラクターが話す際のボイス音量
		std::vector<int> characterVoiceVolume;

		// 画面下から画像の中心までの距離
		float characterCenterPosOffsetY = 0.0f;
		// 画面端から画像の中心までの距離
		float characterCenterPosOffsetX = 0.0f;

		// キャラクターが話していない時の画像の透明度パーセンテージ
		int characterNotSpeakAlphaPercentage = 0;
		// キャラクターが話していない時の画像中心からの距離
		float characterNotSpeakCenterPosOffsetY = 0.0f;
		// 画像移動速度
		float characterMoveSpeed = 0.0f;
	};

	// ロードしたメッセージウィンドウデータ
	struct CSVMessageWindowData
	{
		// メッセージウィンドウの横幅
		float messageWindowWidth = 0.0f;

		// 画面端からメッセージウィンドウまでの距離
		float messageWindowMargin = 0.0f;

		// 画面下からメッセージウィンドウまでの距離
		float messageWindowPosOffsetY = 0.0f;
	};

	// ロードしたトークデータ
	struct CSVTakeData
	{
		// 話す文章
		std::string talkText;

		// 話すキャラクター番号
		int talkCharacterNo = 0;

		// キャラクター表情番号
		int talkFaceNo = 0;

		// 右端に表示するかどうか
		bool isRight = false;

		// 反転描画するかどうか
		bool isFlip = false;

		// フォントカラー
		int fontColor = 0xffffff;

		// 文字を震わせるかどうか
		bool isShake = false;

		// 一文字を表示するのにかかるフレーム数
		int drawCharFrame = 0;

		// フォントタイプ
		int fontType = 0;

		// 文字横間隔
		int charInterval = 0;

		// 文字縦間隔
		float lineInterval = 0.0f;

		// キャラクター名カラー
		int characterNameColor = 0;

		// キャラクター名
		std::string characterName = "";
	}; 

	// ロードしたデータ
	struct LoadData
	{
		CSVFontData fontData = CSVFontData();
		CSVCharacterData characterData = CSVCharacterData();
		CSVMessageWindowData messageWindowData = CSVMessageWindowData();
		std::vector<CSVTakeData> talkData;
	};


public:

	MessageTextLoader();
	virtual ~MessageTextLoader();



	/// <summary>
	/// データをロードする
	/// </summary>
	/// <returns></returns>
	LoadData LoadTextData();




private:

	/// <summary>
	/// テキスト設定データをロード
	/// </summary>
	void LoadTextSettingData();

	/// <summary>
	/// 会話データをロード
	/// </summary>
	void LoadTalkData();

	/// <summary>
	/// データが空かどうか
	/// </summary>
	/// <param name="str">string型の文章</param>
	/// <returns>データが空かどうかのフラグ</returns>
	bool IsEmptyData(const std::string& str);

private:

	// ロードしたデータ
	LoadData m_loadData;


	

};