#include "MessageWindow.h"
#include "Pad.h"
#include <DxLib.h>
#include "Vec2.h"
#include "game.h"
#include <cassert>
#include "EvoLib.h"



namespace
{
	// キャラクター名サイズ
	constexpr int kCharacterNameFontSize = 30;

	// キャラクター名の最大文字数
	constexpr int kCharacterNameMax = 7;

	// キャラクター名の文字幅
	constexpr int kCharacterNameWidth = 5;

	// キャラクター名フォントタイプ
	constexpr int kCharacterNameFontType = 1;

	// キャラクター名のフォントカラー
	constexpr int kCharacterNameColor = 0xffffff;


	// テキストスピード
	constexpr int kTextSpeed = 5;

	// 文字の大きさ
	constexpr int kFontScale = 30;



	// フォント
	struct FontData
	{
		// ファイルパス
		const char* FilePath = "";

		// フォント名
		const char* FontName = "";
	};

	// フォント
	const std::vector<FontData> kFontData =
	{
		{"Data/Font/font1.ttf","DotGothic16"},
		{"Data/Font/font2.otf","07やさしさアンチック"},
	};

	// テキスト要素
	struct TextElement
	{
		// テキスト
		const char* text = "";

		// キャラクター番号
		int characterNumber = 0;

		// 右端に表示するかどうか
		bool isRightDraw = false;

		// テキストのフォントカラー
		int color = 0xffffff;

		// キャラクター名
		const char* characterName = "";

		// テキストの文字幅
		int textWidth = 0;

		// テキストスピード
		int textSpeed = kTextSpeed;

		// テキストサイズからの行間
		float lineSpace = 0.4f;

		// テキストサイズ
		float textSize = kFontScale;

		// フォントタイプ
		int fontType = 1;

		// 文字を震わせるかどうか
		bool isVibration = false;
	};

	// テキスト要素
	const std::vector<TextElement> kTextElement =
	{

		{ "気持ちいいわね。\n毎回、昼間に出発して悪霊が少ないから、夜に出てみたんだけど……どこに行っていいかわからないわ。暗くて。", 0},
		{ "そうなのよね～。お化けも出るし、たまんないわ。", 1 ,true,0xffffff,"???"},
		{ "って、あんた誰？", 0 },
		{ "さっき会ったじゃない。あんた、もしかして鳥目？", 1,true},
		{ "人は暗いところでは物が良く見えないのよ。", 0 },
		{ "あら？　夜しか活動しない人も見たことある気がするわ。", 1,true },
		{ "それは取って食べたりしてもいいのよ。", 0 },
		{ "そーなのかー。", 1,true },
		{ "で、邪魔なんですけど。", 0},
		{ "目の前が取って食べれる人類？", 1,true },
		{ "良薬は口に苦しって言葉知ってる？", 0},
		{ "良薬っていっても、飲んでみなけりゃわかんないけどね。", 0},
	};
}

// メッセージウィンドウ
namespace Window
{
	// メッセージウィンドウの縦幅
	constexpr float kMessageWindowHeight = 200.0f;

	// 画面端からメッセージウィンドウの横幅
	constexpr float kMessageWindowEdge = 300.0f;
	
	// 画面下からメッセージウィンドウまでの高さ
	constexpr float kMessageWindowHeightFromBottom = 100.0f;
}

// キャラクター
namespace Character
{
	// キャラクターの縦幅
	constexpr float kCharacterHeight = 600.0f;

	// キャラクターの横幅
	constexpr float kCharacterWidth = 400.0f;


	// 画面端からキャラクターの横幅
	constexpr float kCharacterEdge = 300.0f;

	// 画面下からキャラクターまでの高さ
	constexpr float kCharacterHeightFromBottom = 50.0f;

	// 非表示時の中心座標からの距離
	constexpr float kHideDistance = 40.0f;


	// 左端のキャラクター中心座標
	Vec2 kLeftCenterPos = Vec2();

	// 右端のキャラクター中心座標
	Vec2 kRightCenterPos = Vec2();

	// 左端の非表示キャラクター中心座標
	Vec2 kLeftCenterPosHide = Vec2();

	// 右端の非表示キャラクター中心座標
	Vec2 kRightCenterPosHide = Vec2();


	// キャラクターの情報
	struct CharacterData
	{
		// キャラクターのグラフィックハンドル
		const char* graphFilePath = "";

		// キャラクター名
		const char* name = "";

		// キャラクターの拡大率
		float scale = 1.0f;

		// キャラクターの横分割数
		int divX = 1;
	};
	


	// キャラクターデータ
	const std::vector<CharacterData> kCharacterData =
	{
		{"Data/Character/Character1.png","霊夢"},

		{"Data/Character/Character2.png","ルーミア"},

		{"Data/Character/Character3.png"},

	};




}


MessageWindow::MessageWindow():
	m_textInfo(),
	m_windowInfo(),
	m_characterInfo()
{
}

MessageWindow::~MessageWindow()
{
	// フォントの削除
	for(auto&font:m_textInfo.fontHandle)
	{
		DeleteFontToHandle(font);
	}


}

void MessageWindow::Init()
{

	// ウィンドウ情報の初期化
	{

		// ウィンドウの中心座標を設定
		Vec2 windowCenterPos = Vec2();

		windowCenterPos.x = Game::kScreenWidth * 0.5f;
		windowCenterPos.y = (Game::kScreenHeight - Window::kMessageWindowHeightFromBottom) - (Window::kMessageWindowHeight * 0.5f);


		// ウィンドウの左上座標を設定
		m_windowInfo.leftTop.x = Window::kMessageWindowEdge;
		m_windowInfo.leftTop.y = windowCenterPos.y - (Window::kMessageWindowHeight * 0.5f);

		// ウィンドウの右下座標を設定
		m_windowInfo.rightBottom.x = Game::kScreenWidth - Window::kMessageWindowEdge;
		m_windowInfo.rightBottom.y = windowCenterPos.y + (Window::kMessageWindowHeight * 0.5f);

		// キャラクター名の幅を設定
		const float characterNameFontSize = kCharacterNameFontSize * 1.2f;

		// キャラクター名を表示するウィンドウの左上座標を設定
		m_windowInfo.nameLeftTop.x = m_windowInfo.leftTop.x;
		m_windowInfo.nameLeftTop.y = m_windowInfo.leftTop.y - characterNameFontSize;

		
		m_windowInfo.nameWindowWidth = (kCharacterNameWidth + characterNameFontSize) * (kCharacterNameMax + 1);

		m_windowInfo.nameRightBottom.x = m_windowInfo.nameLeftTop.x + m_windowInfo.nameWindowWidth;
		m_windowInfo.nameRightBottom.y = m_windowInfo.nameLeftTop.y + characterNameFontSize;
	}


	// テキスト情報の初期化
	{
		// テキストスピードをフレームカウントに代入
		m_textInfo.frameCount = kTextElement[0].textSpeed;

		// テキスト番号を0にする
		m_textInfo.currentNumber = 0;

		// 文章の表示終了フラグをfalseにする
		m_textInfo.isEndText = false;

		// 文字列を早く描画するフラグをfalseにする
		m_textInfo.isFastDraw = false;

		// 何文字表示するかを指定する
		m_textInfo.dispCharCount = 0;

		// 文字列を挿入する
		m_textInfo.m_temp = kTextElement[0].text;


		// フォント関連
		{

			for (auto& font : kFontData)
			{
				// フォントの保存
				m_textInfo.fontHandle.push_back(EvoLib::Load::LoadFont(font.FilePath, font.FontName, kFontScale));
			}


			// フォントサイズを取得
			int fontSize = GetDrawStringWidthToHandle("L", 1, m_textInfo.fontHandle[0]);
			
			// テキストの座標を設定
			m_textInfo.textPos = Vec2(m_windowInfo.leftTop.x + fontSize, m_windowInfo.leftTop.y + fontSize);
		}
	}

	// キャラクター情報の初期化
	{
		// 座標関連
		{
			// キャラクターの中心座標を設定
			Vec2 characterCenterPos = Vec2();

			characterCenterPos.x = Game::kScreenWidth * 0.5f;
			characterCenterPos.y = (Game::kScreenHeight - Character::kCharacterHeightFromBottom) - (Character::kCharacterHeight * 0.5f);

			// キャラクターの左端座標を設定
			Character::kLeftCenterPos.x = Character::kCharacterEdge;
			Character::kLeftCenterPos.y = characterCenterPos.y;

			// キャラクターの右端座標を設定
			Character::kRightCenterPos.x = Game::kScreenWidth - Character::kCharacterEdge;
			Character::kRightCenterPos.y = characterCenterPos.y;

			// キャラクターの左端非表示座標を設定
			Character::kLeftCenterPosHide.x = Character::kLeftCenterPos.x - Character::kHideDistance;
			Character::kLeftCenterPosHide.y = Character::kLeftCenterPos.y + Character::kHideDistance;

			// キャラクターの右端非表示座標を設定
			Character::kRightCenterPosHide.x = Character::kRightCenterPos.x + Character::kHideDistance;
			Character::kRightCenterPosHide.y = Character::kRightCenterPos.y + Character::kHideDistance;
		}
		
		// キャラクターのグラフィックハンドルの取得
		{
			m_characterInfo.resize(static_cast<int>(Character::kCharacterData.size()));

			for (int i = 0; i < static_cast<int>(m_characterInfo.size()); i++)
			{
				m_characterInfo[i].graphicHandle = LoadGraph(Character::kCharacterData[i].graphFilePath);

				// キャラクターの拡大率を設定
				m_characterInfo[i].scale = Character::kCharacterData[i].scale;

				// キャラクター名を設定
				m_characterInfo[i].name = kTextElement[i].characterName;
			}
		}

		// 一番はじめに表示するキャラクターの座標を設定
		InitCharacterPos(kTextElement[m_textInfo.currentNumber].isRightDraw);
	}
}

void MessageWindow::Update()
{
	// テキスト処理の呼び出し
	UpdateTextDisplay();

	// テキストを切り替える処理
	UpdateTextOnInput();

	// キャラクターの更新処理
	UpdateCharacter();
}

void MessageWindow::Draw()
{
	// キャラクターの描画
	DrawCharacter();

	// メッセージウィンドウの描画
	DrawMessageWindow();


	DrawMessageText();

	DrawCharacterNameText();
}

void MessageWindow::UpdateTextDisplay()
{
	// 文章の表示が終わっていた場合、処理を終了する
	if (m_textInfo.isEndText)
	{
		return;
	}

	if (!m_textInfo.isFastDraw)
	{
		// フレームカウントを減らす
		m_textInfo.frameCount--;

		// フレームカウントが0になった時、テキストスピードをフレームカウントに代入し、表示する文字数を増やす
		if (m_textInfo.frameCount <= 0)
		{
			// テキストスピードをフレームカウントに代入
			m_textInfo.frameCount = kTextSpeed;

			// 表示する文字数を増やす
			m_textInfo.dispCharCount++;
		}
	}
	else
	{
		// 表示する文字数を増やす
		m_textInfo.dispCharCount++;
	}

	// バイト数をカウント
	int currentByte = 0;

	for (int i = 0; i < m_textInfo.dispCharCount; i++)
	{
		if (currentByte >= m_textInfo.m_temp.size())
		{
			m_textInfo.isEndText = true;

			// 表示する文字列を全て表示したら、表示する文字数を文字列の長さにする
			m_textInfo.dispCharCount = static_cast<int>(m_textInfo.m_temp.size());

			break;
		}

		unsigned char charData = m_textInfo.m_temp[currentByte];    // チェックする文字
		if (charData == '\n') {
			// 改行文字の場合
			currentByte += 1; // 改行文字をスキップ
			continue;
		}
		else if (charData < 0x80)
		{
			currentByte += 1;
		}
		else
		{
			currentByte += 2;
		}
	}
}


void MessageWindow::UpdateTextOnInput()
{
	if (Pad::isTrigger(PAD_INPUT_10))
	{
		if (m_textInfo.isEndText)
		{
			// 初期化
			{
				// 表示する文字数を初期化
				m_textInfo.dispCharCount = 0;

				// 文章の表示終了フラグをfalseにする
				m_textInfo.isEndText = false;

				// 文字列を早く描画するフラグをfalseにする
				m_textInfo.isFastDraw = false;

				// フレームカウントをテキストスピードに代入
				m_textInfo.frameCount = kTextElement[m_textInfo.currentNumber].textSpeed;
			}

			// 現在の選択項目を一つ下にずらす(ループする)
			m_textInfo.currentNumber = EvoLib::Calculation::SelectLoopNumber(0, static_cast<int>(kTextElement.size()), m_textInfo.currentNumber);

			// 文字列を挿入する
			m_textInfo.m_temp = kTextElement[m_textInfo.currentNumber].text;

			// キャラクター座標初期化
			InitCharacterPos(kTextElement[m_textInfo.currentNumber].isRightDraw);
		}
		else
		{
			// 文字列を早く描画するフラグをtrueにする
			m_textInfo.isFastDraw = true;
		}
	}
}

void MessageWindow::DrawMessageText()
{

	// テキストの座標
	Vec2 textPos = m_textInfo.textPos;

	int currentByte = 0;

	// フォント番号
	const int fontNumber = kTextElement[m_textInfo.currentNumber].fontType;

	// フォントハンドルの決定（例：特定の文字位置でフォントを変更する）
	const int fontHandle = m_textInfo.fontHandle[fontNumber];

	// テキストの色
	const int color = kTextElement[m_textInfo.currentNumber].color;

	// 行間
	const float lineSpace = kTextElement[m_textInfo.currentNumber].textSize * kTextElement[m_textInfo.currentNumber].lineSpace; // 行間

	// 改行したかどうか
	bool isLineBreak = false;

	for (int i = 0; i < m_textInfo.dispCharCount; i++)
	{
		if (currentByte >= m_textInfo.m_temp.size()) break;
		unsigned char charData = m_textInfo.m_temp[currentByte];
		int size = 0;

	

		if (charData == '\n') 
		{
			// 改行文字の場合
			textPos.x = m_textInfo.textPos.x; // 行の先頭に戻る
			textPos.y += GetFontSizeToHandle(fontHandle); // 行の高さを加算
			textPos.y += lineSpace; // 行間を加算

			currentByte += 1; // 改行文字をスキップ

			isLineBreak = true;

			continue;
		}
		else if (IsTextInWindow(textPos, fontHandle))
		{
			textPos.x = m_textInfo.textPos.x; // 行の先頭に戻る
			textPos.y += GetFontSizeToHandle(fontHandle); // 行の高さを加算
			textPos.y += lineSpace; // 行間を加算

			isLineBreak = true;

			continue;
		}
		else
		{
			if (i != 0 && !isLineBreak)
			{
				// テキストの横幅を追加
				textPos.x += kTextElement[m_textInfo.currentNumber].textWidth;
			}

		
		}
		


		if (charData < 0x80) 
		{
			size = 1;
		}
		else {
			size = 2;
		}

		int shakeX = GetRand(2) - 1;
		int shakeY = GetRand(2) - 1;

		// テキストの揺れを設定
		if (!kTextElement[m_textInfo.currentNumber].isVibration)
		{
			shakeX = 0;
			shakeY = 0;
		}

		Vec2 shakePos = textPos;
		shakePos.x += shakeX;
		shakePos.y += shakeY;

		// 文字列の描画
		DrawStringFToHandle(shakePos.x, shakePos.y, m_textInfo.m_temp.substr(currentByte, size).c_str(), color, fontHandle);

		
		textPos.x += GetDrawStringWidth(m_textInfo.m_temp.substr(currentByte, size).c_str(), size, fontHandle);

		currentByte += size;

		isLineBreak = false;
	}
}

void MessageWindow::DrawCharacterNameText()
{
	

	int currentByte = 0;

	// フォントハンドルの決定（例：特定の文字位置でフォントを変更する）
	const int fontHandle = m_textInfo.fontHandle[kCharacterNameFontType];

	// テキストの色
	const int color = kCharacterNameColor;


	// 文字列を挿入する
	std::string temp = kTextElement[m_textInfo.currentNumber].characterName;

	// 文字列が空の場合、キャラクター名を代入する
	if (temp == "")
	{
		temp = Character::kCharacterData[kTextElement[m_textInfo.currentNumber].characterNumber].name;
	}



	// 表示する文字列を全て表示したら、表示する文字数を文字列の長さにする
	const int dispCharCount = static_cast<int>(temp.size());


	Vec2 nameWindowCenterPos = Vec2();
	nameWindowCenterPos.x = m_windowInfo.nameLeftTop.x + (m_windowInfo.nameWindowWidth * 0.5f);
	nameWindowCenterPos.y = m_windowInfo.nameLeftTop.y;

	float textWidth = GetDrawStringWidthToHandle(temp.c_str(), dispCharCount, fontHandle);
	textWidth *= 1.1f;


	// テキストの座標
	Vec2 textPos = Vec2();
	textPos.x = nameWindowCenterPos.x - (textWidth * 0.5f);
	textPos.y = nameWindowCenterPos.y;


	
	for (int i = 0; i < dispCharCount; i++)
	{
		if (currentByte >= temp.size()) break;
		unsigned char charData = temp[currentByte];
		int size = 0;


		if (i != 0)
		{
			// テキストの横幅を加算
			textPos.x += kCharacterNameWidth;
		}


		if (charData < 0x80)
		{
			size = 1;
		}
		else {
			size = 2;
		}

	



		// 文字列の描画
		DrawStringFToHandle(textPos.x, textPos.y, temp.substr(currentByte, size).c_str(), color, fontHandle);


		textPos.x += GetDrawStringWidth(temp.substr(currentByte, size).c_str(), size, fontHandle);

		currentByte += size;

	
	}
}


int MessageWindow::GetDrawStringWidth(const char* str, const int& length, const int& fontHandle)
{
	// 文字列の幅を計算
	int originalWidth = GetDrawStringWidthToHandle(str, length, fontHandle);
	return originalWidth;
}

bool MessageWindow::IsTextInWindow(const Vec2 textPos, const int fontHandle)
{
	// フォントサイズを取得
	const int fontSize = GetFontSizeToHandle(fontHandle);

	// テキストの右端座標を計算
	const float textRightPos = textPos.x + fontSize;

	// テキストの右端座標がウィンドウの右端座標を超えている場合、trueを返す
	if (m_windowInfo.rightBottom.x <= textRightPos)
	{
		return true;	
	}

	return false;
}





void MessageWindow::DrawMessageWindow()
{
	// 描画ブレンドモードをアルファブレンド（５０％）にする
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);

	// メッセージウィンドウの描画
	DrawBoxAA(m_windowInfo.leftTop.x, m_windowInfo.leftTop.y, m_windowInfo.rightBottom.x, m_windowInfo.rightBottom.y, 0xffffff, true);

	// キャラクター名を表示するウィンドウの描画
	DrawBoxAA(m_windowInfo.nameLeftTop.x, m_windowInfo.nameLeftTop.y, m_windowInfo.nameRightBottom.x, m_windowInfo.nameRightBottom.y, 0xffffff, true);

	// 描画ブレンドモードをノーブレンドにする
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// メッセージウィンドウの描画
	DrawBoxAA(m_windowInfo.leftTop.x, m_windowInfo.leftTop.y, m_windowInfo.rightBottom.x, m_windowInfo.rightBottom.y, 0xffffff, false);

	// キャラクター名を表示するウィンドウの描画
	DrawBoxAA(m_windowInfo.nameLeftTop.x, m_windowInfo.nameLeftTop.y, m_windowInfo.nameRightBottom.x, m_windowInfo.nameRightBottom.y, 0xffffff, false);
}

void MessageWindow::InitCharacterPos(const bool& isRightDraw)
{
	// キャラクター番号
	const int characterNumber = kTextElement[m_textInfo.currentNumber].characterNumber;

	// 一つ前のテキスト番号
	const int beforeTextNumber = m_textInfo.currentNumber - 1;



	if (beforeTextNumber < 0)
	{
		SetUpCharacterPos(kTextElement[m_textInfo.currentNumber].isRightDraw, characterNumber, false);

		return;
	}

	// キャラクター番号
	const int characterBeforeNumber = kTextElement[beforeTextNumber].characterNumber;


	if (kTextElement[m_textInfo.currentNumber].isRightDraw == kTextElement[beforeTextNumber].isRightDraw &&
		characterNumber == characterBeforeNumber)
	{
		return;
	}



	SetUpCharacterPos(kTextElement[beforeTextNumber].isRightDraw, characterBeforeNumber, true);


	SetUpCharacterPos(kTextElement[m_textInfo.currentNumber].isRightDraw, characterNumber, false);
}


void MessageWindow::SetUpCharacterPos(const bool& isRightDraw, const int& characterNumber, const bool isBeforeNumber)
{
	if (!isBeforeNumber)
	{
		// 左端に表示するかどうか
		if (!isRightDraw)
		{
			m_characterInfo[characterNumber].pos = Character::kLeftCenterPosHide;

			m_characterInfo[characterNumber].targetPos = Character::kLeftCenterPos;
		}
		else
		{
			m_characterInfo[characterNumber].pos = Character::kRightCenterPosHide;

			m_characterInfo[characterNumber].targetPos = Character::kRightCenterPos;
		}
	}
	else
	{
		// 左端に表示するかどうか
		if (!isRightDraw)
		{
			m_characterInfo[characterNumber].pos = Character::kLeftCenterPos;

			m_characterInfo[characterNumber].targetPos = Character::kLeftCenterPosHide;
		}
		else
		{
			m_characterInfo[characterNumber].pos = Character::kRightCenterPos;

			m_characterInfo[characterNumber].targetPos = Character::kRightCenterPosHide;
		}
	}

	// 移動量を初期化
	m_characterInfo[characterNumber].vec = Vec2();

	// 右側に表示されているかどうか
	m_characterInfo[characterNumber].isRightDraw = isRightDraw;
}

void MessageWindow::UpdateCharacter()
{

	// キャラクター番号
	const int characterNumber = kTextElement[m_textInfo.currentNumber].characterNumber;

	
	// キャラクターの座標を移動
	m_characterInfo[characterNumber].vec = EvoLib::Calculation::TargetMoveValue(m_characterInfo[characterNumber].pos, m_characterInfo[characterNumber].targetPos, 0.1f);


	m_characterInfo[characterNumber].pos += m_characterInfo[characterNumber].vec;


	// 一つ前のテキスト番号
	const int beforeTextNumber = m_textInfo.currentNumber - 1;

	// 一つ前のテキスト番号が0未満の場合、処理を終了する
	if (beforeTextNumber < 0)
	{
		return;
	}

	// キャラクター番号
	const int characterBeforeNumber = kTextElement[beforeTextNumber].characterNumber;


	// キャラクターの座標を移動
	m_characterInfo[characterBeforeNumber].vec = EvoLib::Calculation::TargetMoveValue(m_characterInfo[characterBeforeNumber].pos, m_characterInfo[characterBeforeNumber].targetPos, 0.1f);

	m_characterInfo[characterBeforeNumber].pos += m_characterInfo[characterBeforeNumber].vec;
}

void MessageWindow::DrawCharacter()
{
	// 現在のキャラクター番号
	const int characterNumber = kTextElement[m_textInfo.currentNumber].characterNumber;

	// 前回のキャラクター番号
	int characterBeforeNumber = 0;

	// 一つ前のテキスト番号
	const int beforeTextNumber = m_textInfo.currentNumber - 1;

	
	// キャラクターの描画
	DrawRotaGraph(m_characterInfo[characterNumber].pos.x, m_characterInfo[characterNumber].pos.y, 1.0, 0.0, m_characterInfo[characterNumber].graphicHandle, true);
	

	// 半透明にして描画
	{
		// 一つ前のテキスト番号が0未満の場合、処理を終了する
		if (beforeTextNumber < 0)
		{
			return;
		}

		// 前回のキャラクター番号代入
		characterBeforeNumber = kTextElement[beforeTextNumber].characterNumber;



		// どちらか片方にキャラクターが表示されていない場合、表示させる
 		if(kTextElement[m_textInfo.currentNumber].isRightDraw == kTextElement[beforeTextNumber].isRightDraw)
		{
			bool isRightDraw = kTextElement[m_textInfo.currentNumber].isRightDraw;

			for (int i = m_textInfo.currentNumber; i >= 0; --i)
			{
				if (isRightDraw != kTextElement[i].isRightDraw)
				{
					// 描画ブレンドモードをアルファブレンド（５０％）にする
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);

					int test = kTextElement[i].characterNumber;


					DrawRotaGraph(m_characterInfo[test].pos.x, m_characterInfo[test].pos.y, 1.0, 0.0, m_characterInfo[test].graphicHandle, true);

					// 描画ブレンドモードをノーブレンドにする
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

					return;
				}
			}
		}
		else
		{
			// 描画ブレンドモードをアルファブレンド（５０％）にする
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);

			DrawRotaGraph(m_characterInfo[characterBeforeNumber].pos.x, m_characterInfo[characterBeforeNumber].pos.y, 1.0, 0.0, m_characterInfo[characterBeforeNumber].graphicHandle, true);

			// 描画ブレンドモードをノーブレンドにする
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	}
}