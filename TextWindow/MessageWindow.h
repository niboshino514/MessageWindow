#pragma once
#include <string>
#include "Vec2.h"
#include <vector>
#include <memory>

class MessageTextLoader;

class MessageWindow
{
public:

	// メッセージ要素
	struct MessageElement
	{
		// 話す文章
		std::string talkText = "";

		// 話すキャラクター番号
		int talkCharacterNo = 0;

		// キャラクターの表情番号
		int talkFaceNo = 0;

		// 右端に表示するかどうか
		bool isRight = false;

		// 反転描画するかどうか
		bool isFlip = false;

		// テキストのフォントカラー
		int fontColor = 0xffffff;

		// 文字を震わせるかどうか
		bool isShake = false;

		// テキストスピード
		int drawCharFrame = 0;

		// フォントタイプ
		int fontType = 0;

		// テキストの文字幅
		int charInterval = 0;

		// テキストサイズからの行間
		float lineInterval = 0.4f;

		// キャラクター名カラー
		int characterNameColor = 0;

		// キャラクター名
		std::string characterName = "";
	};

public:
	MessageWindow();
	virtual ~MessageWindow();

	void Init();
	void Update();
	void Draw();

	// テキスト表示情報
	struct TextDisplayInfo
	{
		// テキストの座標
		Vec2 textPos = Vec2(0, 0);

		// テキスト番号
		int currentNumber = 0;

		// 文章の表示が終わったかどうか
		bool isEndText = false;

		// 文字列を早く描画するかどうか
		bool isFastDraw = false;

		// 文字列格納
		std::string m_temp = "";

		// 段落切り替えフラグ
		bool isParagraph = false;

		// フレームをカウント
		int frameCount = 0;

		// 表示する文字数
		int dispCharCount = 0;

		// フォントサイズ
		int fontSize = 0;

		// フォントハンドル
		std::vector<int> fontHandle;

	

		// キャラクター名のフォントハンドル
		int nameFontHandle = 0;

		// キャラクター名の文字横間隔
		int characterNameCharInterval = 0;

	};

	// メッセージウィンドウ情報
	struct MessageWindowInfo
	{
		// ウィンドウの左上座標
		Vec2 leftTop = Vec2();

		// ウィンドウの右下座標
		Vec2 rightBottom = Vec2();

		// キャラクター名を表示するウィンドウの左上座標
		Vec2 nameLeftTop = Vec2();

		// キャラクター名を表示するウィンドウの右下座標
		Vec2 nameRightBottom = Vec2();

		// キャラクター名を表示するウィンドウの横幅
		int nameWindowWidth = 0;
	};

	// キャラクター表示情報
	struct CharacterDisplayInfo
	{
		// キャラクターグラフィックハンドル
		std::vector<int> graphicHandle;

		// キャラクター名
		std::string name = "";

		// キャラクター拡大率
		float scale = 1.0f;

		// 画像を右向きにするかどうか
		bool isGraphRight = false;


		// 右側に表示されているかどうか
		bool isRightDraw = false;

		// キャラクターの座標
		Vec2 pos = Vec2();

		// キャラクターのオフセット値
		Vec2 centerPosOffset = Vec2();

		// ターゲット座標
		Vec2 targetPos = Vec2();

		// 移動量
		Vec2 vec = Vec2();
	};


private:





	/// <summary>
	/// テキスト表示進行
	/// </summary>
	void UpdateTextDisplay();

	/// <summary>
	/// 入力時にテキストの更新
	/// </summary>
	void UpdateTextOnInput();

	/// <summary>
	/// テキスト描画
	/// </summary>
	void DrawMessageText();

	void DrawCharacterNameText();

	/// <summary>
	/// 文字列のサイズを取得
	/// </summary>
	/// <param name="str">文字列</param>
	/// <param name="length">調べる文字</param>
	/// <param name="fontHandle">フォントハンドル</param>
	/// <returns>文字列のサイズ</returns>
	int GetDrawStringWidth(const char* str, const int& length, const int& fontHandle);

	// 文字列がメッセージウィンドウに収まるかどうか
	bool IsTextInWindow(const Vec2 textPos, const int fontHandle);



	/// <summary>
	/// メッセージウィンドウの描画
	/// </summary>
	void DrawMessageWindow();

	

	/// <summary>
	/// キャラクターの初期位置設定
	/// </summary>
	/// <param name="isRightDraw">右に表示するかどうか</param>
	void InitCharacterPos(const bool& isRightDraw);

	/// <summary>
	/// キャラクターの位置設定
	/// </summary>
	/// <param name="isRightDraw">右に表示するかどうか</param>
	/// <param name="characterNumber">キャラクター番号</param>
	/// <param name="isBeforeNumber">前のキャラクター番号かどうか</param>
	void SetUpCharacterPos(const bool& isRightDraw, const int& characterNumber, const bool isBeforeNumber);


	void UpdateCharacter();

	void DrawCharacter();

	/// <summary>
	/// キャラクターを反転させるかどうか
	/// </summary>
	/// <param name="characterNumber">キャラクターナンバー</param>
	/// <param name="textNumber">テキストナンバー</param>
	/// <returns>反転フラグを返す</returns>
	bool IsFlipCharacter(const int& characterNumber, const int& textNumber);

private:

	// テキスト情報
	TextDisplayInfo m_textInfo;

	// ウィンドウ情報
	MessageWindowInfo m_windowInfo;


	// キャラクター情報
	std::vector<CharacterDisplayInfo> m_characterInfo;

	// キャラクターの移動速度
	float m_moveSpeed;

	// キャラクターが話していない時の透明度
	int m_graphNotSpeakAlpha;

	// メッセージ要素
	std::vector<MessageElement> m_messageElement;

	
	std::shared_ptr<MessageTextLoader> m_pMessageTextLoader;
};

