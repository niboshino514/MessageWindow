#pragma once
#include <string>
#include "Vec2.h"
#include <vector>


class MessageWindow
{
public:
	MessageWindow();
	virtual ~MessageWindow();

	void Init();
	void Update();
	void Draw();


	

	// テキスト情報
	struct TextInfo
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

		// フォントハンドル
		std::vector<int> fontHandle;
	};

	// ウィンドウ情報
	struct WindowInfo
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

	// キャラクター情報
	struct CharacterInfo
	{
		// キャラクターグラフィックハンドル
		int graphicHandle = -1;

		// キャラクター名
		std::string name = "";

		// キャラクター拡大率
		float scale = 1.0f;

		// キャラクターの座標
		Vec2 pos = Vec2();

		// ターゲット座標
		Vec2 targetPos = Vec2();

		// 移動量
		Vec2 vec = Vec2();

		// 右側に表示されているかどうか
		bool isRightDraw = false;
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

private:

	// テキスト情報
	TextInfo m_textInfo;

	// ウィンドウ情報
	WindowInfo m_windowInfo;


	// キャラクター情報
	std::vector<CharacterInfo> m_characterInfo;





	// キャラクターの移動速度
	float m_characterMoveSpeed = 0.0f;


};

