#include "MessageWindow.h"
#include "Pad.h"
#include <DxLib.h>
#include "Vec2.h"
#include "game.h"
#include <cassert>
#include "EvoLib.h"
#include "MessageTextLoader.h"


namespace
{
	// キャラクターの移動速度
	constexpr float kCharcterMoveSpeed = 0.1f;

	// キャラクターグラフィックY座標調整値
	constexpr float kCharacterGraphPosY = 100.0f;

	// キャラクターグラフィックX座標調整値
	constexpr float kCharacterGraphPosX = 0.0f;
}


// キャラクター
namespace Character
{
	// 左端のキャラクター中心座標
	Vec2 kLeftCenterPos = Vec2();

	// 右端のキャラクター中心座標
	Vec2 kRightCenterPos = Vec2();

	// 左端の非表示キャラクター中心座標
	Vec2 kLeftCenterPosHide = Vec2();

	// 右端の非表示キャラクター中心座標
	Vec2 kRightCenterPosHide = Vec2();
}


MessageWindow::MessageWindow():
	m_textInfo(),
	m_windowInfo(),
	m_characterInfo(),
	m_moveSpeed(),
	m_graphNotSpeakAlpha(),
	m_pMessageTextLoader(std::make_shared<MessageTextLoader>())
{
}

MessageWindow::~MessageWindow()
{
	// データのアンロード
	UnloadData();
}

void MessageWindow::Init()
{
	// データのロード
	LoadData();
}

void MessageWindow::Update()
{
	// テキスト処理の呼び出し
	UpdateTextDisplay();

	// テキストを切り替える処理
	UpdateTextOnInput();

	// キャラクターの更新処理
	UpdateCharacterPos();
}

void MessageWindow::Draw()
{
	// キャラクターの描画
	DrawCharacter();

	// メッセージウィンドウの描画
	DrawMessageWindow();

	// メッセージテキストの描画
	DrawMessageText();

	// キャラクター名の描画
	DrawCharacterNameText();
}

void MessageWindow::LoadData()
{
	// ロードデータ
	const MessageTextLoader::LoadData loadData = m_pMessageTextLoader->LoadTextData();

	// 会話情報
	{
		// 会話データのサイズ
		const int talkDataSize = static_cast<int>(loadData.talkData.size());

		// 会話データのサイズ分、要素を追加
		m_messageElement.resize(talkDataSize);

		// 会話データのサイズだけループ
		for (int i = 0; i < talkDataSize; i++)
		{
			// 話す文章
			m_messageElement[i].talkText = loadData.talkData[i].talkText;

			// 話すキャラクター番号
			m_messageElement[i].talkCharacterNo = loadData.talkData[i].talkCharacterNo;

			// キャラクターの表情番号
			m_messageElement[i].talkFaceNo = loadData.talkData[i].talkFaceNo;

			// 右端に表示するかどうか
			m_messageElement[i].isRight = loadData.talkData[i].isRight;

			// 反転描画するかどうか
			m_messageElement[i].isFlip = loadData.talkData[i].isFlip;

			// テキストのフォントカラー
			m_messageElement[i].fontColor = loadData.talkData[i].fontColor;

			// フォントの透明度
			{
				// 透明度パーセンテージ
				const float percentage = 100.0f - loadData.talkData[i].fontAlpha;
				// 透明度を設定
				m_messageElement[i].fontAlpha = EvoLib::Convert::ConvertFromPercentToValue(255, percentage);
			}

			// フォントの文字サイズタイプ
			m_messageElement[i].fontSizeType = FontSize(loadData.talkData[i].fontSizeType);


			// 文字を震わせるかどうか
			m_messageElement[i].isShake = loadData.talkData[i].isShake;

			// テキストスピード
			m_messageElement[i].drawCharFrame = loadData.talkData[i].drawCharFrame;

			// フォントタイプ
			m_messageElement[i].fontType = loadData.talkData[i].fontType;

			// テキストの文字幅
			m_messageElement[i].charInterval = loadData.talkData[i].charInterval;

			// テキストサイズからの行間
			m_messageElement[i].lineInterval = loadData.talkData[i].lineInterval;

			// キャラクター名カラー
			m_messageElement[i].characterNameColor = loadData.talkData[i].characterNameColor;

			// キャラクター名
			m_messageElement[i].characterName = loadData.talkData[i].characterName;
		}
	}


	// ウィンドウ情報の初期化
	{

		// ウィンドウの中心座標を設定
		Vec2 windowCenterPos = Vec2();

		windowCenterPos.x = Game::kScreenWidth * 0.5f;
		windowCenterPos.y = (Game::kScreenHeight - loadData.messageWindowData.messageWindowPosOffsetY) - (loadData.messageWindowData.messageWindowWidth * 0.5f);


		// ウィンドウの左上座標を設定
		m_windowInfo.leftTop.x = loadData.messageWindowData.messageWindowMargin;
		m_windowInfo.leftTop.y = windowCenterPos.y - (loadData.messageWindowData.messageWindowWidth * 0.5f);

		// ウィンドウの右下座標を設定
		m_windowInfo.rightBottom.x = Game::kScreenWidth - loadData.messageWindowData.messageWindowMargin;
		m_windowInfo.rightBottom.y = windowCenterPos.y + (loadData.messageWindowData.messageWindowWidth * 0.5f);

		loadData.fontData.characterNameFontSize;

		// キャラクター名の幅を設定
		const float characterNameFontSize = loadData.fontData.characterNameFontSize * 1.2f;

		// キャラクター名を表示するウィンドウの左上座標を設定
		m_windowInfo.nameLeftTop.x = m_windowInfo.leftTop.x;
		m_windowInfo.nameLeftTop.y = m_windowInfo.leftTop.y - characterNameFontSize;



		m_windowInfo.nameWindowWidth = (loadData.fontData.characterNameCharInterval + characterNameFontSize) * (loadData.fontData.characterNameMaxCharCount + 1);

		m_windowInfo.nameRightBottom.x = m_windowInfo.nameLeftTop.x + m_windowInfo.nameWindowWidth;
		m_windowInfo.nameRightBottom.y = m_windowInfo.nameLeftTop.y + characterNameFontSize;
	}


	// テキスト情報の初期化
	{
		// テキストスピードをフレームカウントに代入
		m_textInfo.frameCount = loadData.talkData[0].drawCharFrame;

		// テキスト番号を0にする
		m_textInfo.currentNumber = 0;

		// 文章の表示終了フラグをfalseにする
		m_textInfo.isEndText = false;

		// 文字列を早く描画するフラグをfalseにする
		m_textInfo.isFastDraw = false;

		// 何文字表示するかを指定する
		m_textInfo.dispCharCount = 0;

		// 文字列を挿入する
		m_textInfo.m_temp = loadData.talkData[0].talkText.c_str();


		// フォント関連
		{
			// 通常フォントサイズを取得
			m_textInfo.normalFontSize = loadData.fontData.normalFontSize;
			// 小さいフォントサイズを取得
			m_textInfo.smallFontSize = loadData.fontData.smallFontSize;
			// 大きいフォントサイズを取得
			m_textInfo.bigFontSize = loadData.fontData.bigFontSize;

			// フォントデータのサイズ
			const int fontDataSize = static_cast<int>(loadData.fontData.fontFilePath.size());

			// フォントハンドルのサイズを設定
			m_textInfo.fontHandle.resize(fontDataSize);

			// フォントの数だけループ
			for (int i = 0; i < fontDataSize; i++)
			{
				// 通常フォントサイズのフォントハンドルを取得
				m_textInfo.fontHandle[i].push_back
				((EvoLib::Load::LoadFont(loadData.fontData.fontFilePath[i].c_str(), loadData.fontData.fontName[i].c_str(), m_textInfo.normalFontSize)));

				// 小さいフォントサイズのフォントハンドルを取得
				m_textInfo.fontHandle[i].push_back
				((EvoLib::Load::LoadFont(loadData.fontData.fontFilePath[i].c_str(), loadData.fontData.fontName[i].c_str(), m_textInfo.smallFontSize)));

				// 大きいフォントサイズのフォントハンドルを取得
				m_textInfo.fontHandle[i].push_back
				((EvoLib::Load::LoadFont(loadData.fontData.fontFilePath[i].c_str(), loadData.fontData.fontName[i].c_str(), m_textInfo.bigFontSize)));
			}


			// キャラクター名のフォントを取得
			m_textInfo.nameFontHandle =
				EvoLib::Load::LoadFont(loadData.fontData.fontFilePath[loadData.fontData.characterNameFontType].c_str(), loadData.fontData.fontName[loadData.fontData.characterNameFontType].c_str(), loadData.fontData.characterNameFontSize);



			// キャラクター名の文字横間隔を設定
			m_textInfo.characterNameCharInterval = loadData.fontData.characterNameCharInterval;

			// フォントサイズを取得
			int fontSize = GetDrawStringWidthToHandle("L", 1, m_textInfo.fontHandle[0][0]);

			// テキストの座標を設定
			m_textInfo.textPos = Vec2(m_windowInfo.leftTop.x + fontSize, m_windowInfo.leftTop.y + fontSize);
		}
	}

	// キャラクター情報の初期化
	{
		// キャラクターのグラフィックハンドルの取得
		{
			// キャラクターデータのサイズ
			const int characterGraphFilePathSize = static_cast<int>(loadData.characterData.characterFilePath.size());

			// キャラクター情報のサイズを設定
			m_characterInfo.resize(characterGraphFilePathSize);


			for (int i = 0; i < static_cast<int>(m_characterInfo.size()); i++)
			{
				// キャラクターの分割数
				const int SplitX = loadData.characterData.characterSplitX[i];
				const int SplitY = loadData.characterData.characterSplitY[i];

				// グラフィックの分割数
				const EvoLib::Load::DivNum divNum = { SplitX,SplitY };

				// キャラクターのグラフィックハンドルの取得
				m_characterInfo[i].graphicHandle = EvoLib::Load::LoadDivGraph_EvoLib_Revision(loadData.characterData.characterFilePath[i].c_str(), divNum);

				// キャラクターを右向きにするかどうか
				m_characterInfo[i].isGraphRight = !loadData.characterData.characterIsRight[i];

				// キャラクターの拡大率を設定
				m_characterInfo[i].scale = loadData.characterData.characterScale[i];

				// キャラクター名を設定
				m_characterInfo[i].name = loadData.characterData.characterName[i].c_str();

				// キャラクターの調整値を設定
				m_characterInfo[i].centerPosOffset =
					Vec2(loadData.characterData.characterAdjustX[i], loadData.characterData.characterAdjustY[i]);


			}
		}

		// 座標関連
		{

			// キャラクターの中心座標を設定
			Vec2 characterCenterPos = Vec2();



			characterCenterPos.x = Game::kScreenWidth * 0.5f;
			characterCenterPos.y = (Game::kScreenHeight - loadData.characterData.characterCenterPosOffsetY);


			// キャラクターの左端座標を設定
			Character::kLeftCenterPos.x = loadData.characterData.characterCenterPosOffsetX;
			Character::kLeftCenterPos.y = characterCenterPos.y;

			// キャラクターの右端座標を設定
			Character::kRightCenterPos.x = Game::kScreenWidth - loadData.characterData.characterCenterPosOffsetX;
			Character::kRightCenterPos.y = characterCenterPos.y;

			loadData.characterData.characterNotSpeakCenterPosOffsetY;

			// キャラクターの左端非表示座標を設定
			Character::kLeftCenterPosHide.x = Character::kLeftCenterPos.x - loadData.characterData.characterNotSpeakCenterPosOffsetY;
			Character::kLeftCenterPosHide.y = Character::kLeftCenterPos.y + loadData.characterData.characterNotSpeakCenterPosOffsetY;

			// キャラクターの右端非表示座標を設定
			Character::kRightCenterPosHide.x = Character::kRightCenterPos.x + loadData.characterData.characterNotSpeakCenterPosOffsetY;
			Character::kRightCenterPosHide.y = Character::kRightCenterPos.y + loadData.characterData.characterNotSpeakCenterPosOffsetY;
		}

		// キャラクターの移動速度を設定
		m_moveSpeed = kCharcterMoveSpeed;

		// キャラクターの透明度を設定
		{
			// キャラクターが話していない時の画像の透明度パーセンテージ
			const float percentage = 100.0f - loadData.characterData.characterNotSpeakAlphaPercentage;
			// キャラクターが話していない時の画像の透明度を設定
			m_graphNotSpeakAlpha = EvoLib::Convert::ConvertFromPercentToValue(255, percentage);
		}


		// 一番はじめに表示するキャラクターの座標を設定
		InitCharacterPos(m_messageElement[m_textInfo.currentNumber].isRight);
	}
}

void MessageWindow::UnloadData()
{
	// グラフィックハンドルの解放
	{
		// キャラクター情報のサイズ
		const int characterInfoSize = static_cast<int>(m_characterInfo.size());

		// キャラクター情報のサイズだけループ
		for (int i = 0; i < characterInfoSize; i++)
		{
			// グラフィックハンドルのサイズ
			const int graphicHandleSize = static_cast<int>(m_characterInfo[i].graphicHandle.size());

			// グラフィックハンドルのサイズだけループ
			for (int j = 0; j < graphicHandleSize; j++)
			{
				// グラフィックハンドルの解放
				DeleteGraph(m_characterInfo[i].graphicHandle[j]);
			}
		}
	}

	// フォントハンドルの解放
	{
		// フォントデータのサイズ
		const int fontDataSize = static_cast<int>(m_textInfo.fontHandle.size());

		// フォントデータのサイズだけループ
		for (int i = 0; i < fontDataSize; i++)
		{
			// フォントハンドルのサイズ
			const int fontHandleSize = static_cast<int>(m_textInfo.fontHandle[i].size());

			// フォントハンドルのサイズだけループ
			for (int j = 0; j < fontHandleSize; j++)
			{
				// フォントハンドルの解放
				DeleteFontToHandle(m_textInfo.fontHandle[i][j]);
			}
		}
	}
}

void MessageWindow::UpdateTextDisplay()
{
	// 文章の表示が終わっていた場合、処理を終了する
	if (m_textInfo.isEndText)
	{
		return;
	}

	// 文字列を早く描画するフラグが立っていない場合、フレームカウントを減らす
	if (!m_textInfo.isFastDraw)
	{
		// フレームカウントを減らす
		m_textInfo.frameCount--;

		// フレームカウントが0になった時、テキストスピードをフレームカウントに代入し、表示する文字数を増やす
		if (m_textInfo.frameCount <= 0)
		{
			// テキストスピードをフレームカウントに代入
			m_textInfo.frameCount = m_messageElement[m_textInfo.currentNumber].drawCharFrame;

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

	// 文字列のバイト数をカウント
	for (int i = 0; i < m_textInfo.dispCharCount; i++)
	{
		// 文字列のバイト数をカウント
		const int tempSize = static_cast<int>(m_textInfo.m_temp.size());

		// 文字列のバイト数を超えた場合、処理を終了する
		if (currentByte >= m_textInfo.m_temp.size())
		{
			m_textInfo.isEndText = true;

			// 表示する文字列を全て表示したら、表示する文字数を文字列の長さにする
			m_textInfo.dispCharCount = static_cast<int>(m_textInfo.m_temp.size());

			break;
		}

		// 文字データを取得
		unsigned char charData = m_textInfo.m_temp[currentByte]; 
		
		// チェックする文字
		if (charData == '\\')
		{
			// 改行文字の場合
			currentByte += 2; // 改行文字をスキップ
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
		// 文章の表示が終わっていた場合、処理を終了する
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
				m_textInfo.frameCount = m_messageElement[m_textInfo.currentNumber].drawCharFrame;
			}

			// 現在の選択項目を一つ下にずらす(ループする)
			m_textInfo.currentNumber = EvoLib::Calculation::SelectLoopNumber(0, static_cast<int>(m_messageElement.size()), m_textInfo.currentNumber);

			// 文字列を挿入する
			m_textInfo.m_temp = m_messageElement[m_textInfo.currentNumber].talkText;

			// キャラクター座標初期化
			InitCharacterPos(m_messageElement[m_textInfo.currentNumber].isRight);
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

	// 現在のテキスト番号
	const int currentNumber = m_textInfo.currentNumber;

	// テキストの座標
	Vec2 textPos = m_textInfo.textPos;

	int currentByte = 0;

	// フォント番号
	const int fontNumber = m_messageElement[currentNumber].fontType;

	// フォントハンドルの決定（例：特定の文字位置でフォントを変更する）
	const int fontHandle = m_textInfo.fontHandle[fontNumber][static_cast<int>(m_messageElement[currentNumber].fontSizeType)];

	// テキストの色
	const int color = m_messageElement[currentNumber].fontColor;

	// 行間
	const float lineSpace = m_textInfo.normalFontSize * m_messageElement[currentNumber].lineInterval; // 行間

	// 改行したかどうか
	bool isLineBreak = false;

	bool isLineBreak_test = false;



	// 描画ブレンドモードをアルファブレンドにする
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_messageElement[currentNumber].fontAlpha);


	for (int i = 0; i < m_textInfo.dispCharCount; i++)
	{
		if (currentByte >= m_textInfo.m_temp.size()) break;
		unsigned char charData = m_textInfo.m_temp[currentByte];
		int size = 0;

	

		if (charData == '\\')
		{
			// 改行文字の場合
			textPos.x = m_textInfo.textPos.x; // 行の先頭に戻る
			textPos.y += GetFontSizeToHandle(fontHandle); // 行の高さを加算
			textPos.y += lineSpace; // 行間を加算

			currentByte += 2; // 改行文字をスキップ

			isLineBreak = true;

			isLineBreak_test = true;

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
				textPos.x += m_messageElement[currentNumber].charInterval;
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
		if (!m_messageElement[currentNumber].isShake)
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
		isLineBreak_test = false;
	}

	// 描画ブレンドモードをノーブレンドにする
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void MessageWindow::DrawCharacterNameText()
{
	

	int currentByte = 0;

	// フォントハンドルの決定（例：特定の文字位置でフォントを変更する）
	const int fontHandle = m_textInfo.nameFontHandle;

	// テキストの色
	const int color = m_messageElement[m_textInfo.currentNumber].characterNameColor;


	// 文字列を挿入する
	std::string temp = m_messageElement[m_textInfo.currentNumber].characterName;

	



	// 表示する文字列を全て表示したら、表示する文字数を文字列の長さにする
	const int dispCharCount = static_cast<int>(temp.size());


	Vec2 nameWindowCenterPos = Vec2();
	nameWindowCenterPos.x = m_windowInfo.nameLeftTop.x + (m_windowInfo.nameWindowWidth * 0.5f);
	nameWindowCenterPos.y = m_windowInfo.nameLeftTop.y;

	float textWidth = static_cast<float>(GetDrawStringWidthToHandle(temp.c_str(), dispCharCount, fontHandle));
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
			textPos.x += m_textInfo.characterNameCharInterval;
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
	const float textRightPos = textPos.x + (fontSize*2);

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
	const int characterNumber = m_messageElement[m_textInfo.currentNumber].talkCharacterNo;

	// 一つ前のテキスト番号
	const int beforeTextNumber = m_textInfo.currentNumber - 1;



	if (beforeTextNumber < 0)
	{
		SetUpCharacterPos(m_messageElement[m_textInfo.currentNumber].isRight, characterNumber, false);

		return;
	}

	// キャラクター番号
	const int characterBeforeNumber = m_messageElement[beforeTextNumber].talkCharacterNo;


	if (m_messageElement[m_textInfo.currentNumber].isRight == m_messageElement[beforeTextNumber].isRight &&
		characterNumber == characterBeforeNumber)
	{
		return;
	}



	SetUpCharacterPos(m_messageElement[beforeTextNumber].isRight, characterBeforeNumber, true);


	SetUpCharacterPos(m_messageElement[m_textInfo.currentNumber].isRight, characterNumber, false);
}


void MessageWindow::SetUpCharacterPos(const bool& isRightDraw, const int& characterNumber, const bool isBeforeNumber)
{
	if (!isBeforeNumber)
	{
		// 左端に表示するかどうか
		if (!isRightDraw)
		{
			m_characterInfo[characterNumber].pos = Character::kLeftCenterPosHide;
			m_characterInfo[characterNumber].pos.y += m_characterInfo[characterNumber].centerPosOffset.y;
			m_characterInfo[characterNumber].pos.x += m_characterInfo[characterNumber].centerPosOffset.x;

			m_characterInfo[characterNumber].targetPos = Character::kLeftCenterPos;
			m_characterInfo[characterNumber].targetPos.y += m_characterInfo[characterNumber].centerPosOffset.y;
			m_characterInfo[characterNumber].targetPos.x += m_characterInfo[characterNumber].centerPosOffset.x;

		}
		else
		{
			m_characterInfo[characterNumber].pos = Character::kRightCenterPosHide;
			m_characterInfo[characterNumber].pos.y += m_characterInfo[characterNumber].centerPosOffset.y;
			m_characterInfo[characterNumber].pos.x -= m_characterInfo[characterNumber].centerPosOffset.x;

			m_characterInfo[characterNumber].targetPos = Character::kRightCenterPos;
			m_characterInfo[characterNumber].targetPos.y += m_characterInfo[characterNumber].centerPosOffset.y;
			m_characterInfo[characterNumber].targetPos.x -= m_characterInfo[characterNumber].centerPosOffset.x;
		}
	}
	else
	{
		// 左端に表示するかどうか
		if (!isRightDraw)
		{
			m_characterInfo[characterNumber].pos = Character::kLeftCenterPos;
			m_characterInfo[characterNumber].pos.y += m_characterInfo[characterNumber].centerPosOffset.y;
			m_characterInfo[characterNumber].pos.x += m_characterInfo[characterNumber].centerPosOffset.x;

			m_characterInfo[characterNumber].targetPos = Character::kLeftCenterPosHide;
			m_characterInfo[characterNumber].targetPos.y += m_characterInfo[characterNumber].centerPosOffset.y;
			m_characterInfo[characterNumber].targetPos.x += m_characterInfo[characterNumber].centerPosOffset.x;
		}
		else
		{
			m_characterInfo[characterNumber].pos = Character::kRightCenterPos;
			m_characterInfo[characterNumber].pos.y += m_characterInfo[characterNumber].centerPosOffset.y;
			m_characterInfo[characterNumber].pos.x -= m_characterInfo[characterNumber].centerPosOffset.x;


			m_characterInfo[characterNumber].targetPos = Character::kRightCenterPosHide;
			m_characterInfo[characterNumber].targetPos.y += m_characterInfo[characterNumber].centerPosOffset.y;
			m_characterInfo[characterNumber].targetPos.x -= m_characterInfo[characterNumber].centerPosOffset.x;
		}
	}

	// 移動量を初期化
	m_characterInfo[characterNumber].vec = Vec2();

	// 右側に表示されているかどうか
	m_characterInfo[characterNumber].isRightDraw = isRightDraw;
}

void MessageWindow::UpdateCharacterPos()
{

	// キャラクター番号
	const int characterNumber = m_messageElement[m_textInfo.currentNumber].talkCharacterNo;


	// キャラクターの座標を移動
	m_characterInfo[characterNumber].vec = EvoLib::Calculation::TargetMoveValue(m_characterInfo[characterNumber].pos, m_characterInfo[characterNumber].targetPos, m_moveSpeed);


	m_characterInfo[characterNumber].pos += m_characterInfo[characterNumber].vec;


	// 一つ前のテキスト番号
	const int beforeTextNumber = m_textInfo.currentNumber - 1;

	// 一つ前のテキスト番号が0未満の場合、処理を終了する
	if (beforeTextNumber < 0)
	{
		return;
	}

	// キャラクター番号
	const int characterBeforeNumber = m_messageElement[beforeTextNumber].talkCharacterNo;


	// キャラクターの座標を移動
	m_characterInfo[characterBeforeNumber].vec = EvoLib::Calculation::TargetMoveValue(m_characterInfo[characterBeforeNumber].pos, m_characterInfo[characterBeforeNumber].targetPos, 0.1f);

	m_characterInfo[characterBeforeNumber].pos += m_characterInfo[characterBeforeNumber].vec;
}

void MessageWindow::DrawCharacter()
{
	// 現在のキャラクター番号
	const int characterNumber = m_messageElement[m_textInfo.currentNumber].talkCharacterNo;

	// 前回のキャラクター番号
	int characterBeforeNumber = 0;

	// 一つ前のテキスト番号
	const int beforeTextNumber = m_textInfo.currentNumber - 1;

	// 反転して描画するかどうか
	bool isGraphReverse = false;

	
	isGraphReverse = IsFlipCharacter(characterNumber, m_textInfo.currentNumber);
	

	// キャラクターの描画
	DrawRotaGraphF
	(
		m_characterInfo[characterNumber].pos.x,
		m_characterInfo[characterNumber].pos.y,
		m_characterInfo[characterNumber].scale,
		0.0, 
		m_characterInfo[characterNumber].graphicHandle[m_messageElement[m_textInfo.currentNumber].talkFaceNo],
		true, 
		isGraphReverse
	);
	

	// 半透明にして描画
	{
		// 一つ前のテキスト番号が0未満の場合、処理を終了する
		if (beforeTextNumber < 0)
		{
			return;
		}

		// 前回のキャラクター番号代入
		characterBeforeNumber = m_messageElement[beforeTextNumber].talkCharacterNo;



		// どちらか片方にキャラクターが表示されていない場合、表示させる
 		if(m_messageElement[m_textInfo.currentNumber].isRight == m_messageElement[beforeTextNumber].isRight)
		{
			bool isRightDraw = m_messageElement[m_textInfo.currentNumber].isRight;

			for (int i = m_textInfo.currentNumber; i >= 0; --i)
			{
				if (isRightDraw != m_messageElement[i].isRight)
				{
					// 描画ブレンドモードをアルファブレンド（５０％）にする
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_graphNotSpeakAlpha);

					int number = m_messageElement[i].talkCharacterNo;

					
					if (characterNumber == number)
					{
						continue;
					}

					if(isRightDraw == m_characterInfo[number].isRightDraw)
					{
						continue;
					}



					isGraphReverse = IsFlipCharacter(number, i);



					DrawRotaGraphF
					(
						m_characterInfo[number].pos.x, 
						m_characterInfo[number].pos.y, 
						m_characterInfo[number].scale, 
						0.0, 
						m_characterInfo[number].graphicHandle[m_messageElement[i].talkFaceNo],
						true, 
						isGraphReverse
					);

					// 描画ブレンドモードをノーブレンドにする
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

					return;
				}
			}
		}
		else
		{

 			if (characterNumber == characterBeforeNumber)
			{
				return;
			}


			isGraphReverse = IsFlipCharacter(characterBeforeNumber, beforeTextNumber);

			// 描画ブレンドモードをアルファブレンド
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_graphNotSpeakAlpha);

			// キャラクターの描画
			DrawRotaGraphF
			(
				m_characterInfo[characterBeforeNumber].pos.x, 
				m_characterInfo[characterBeforeNumber].pos.y, 
				m_characterInfo[characterBeforeNumber].scale,
				0.0, 
				m_characterInfo[characterBeforeNumber].graphicHandle[m_messageElement[beforeTextNumber].talkFaceNo], 
				true, 
				isGraphReverse
			);

			// 描画ブレンドモードをノーブレンドにする
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	}
}

bool MessageWindow::IsFlipCharacter(const int& characterNumber, const int& textNumber)
{
	if (m_characterInfo[characterNumber].isGraphRight)
	{
		// 何事もなければtrueを返す
		const bool isRightDraw = m_messageElement[textNumber].isRight;

		const bool isFlip = m_messageElement[textNumber].isFlip;


		if(isRightDraw == isFlip)
		{
			return true;
		}
		
		if (!isRightDraw == isFlip)
		{
			return false;
		}
	}
	else
	{
		// 何事もなければfalseを返す

		const bool isRightDraw = m_messageElement[textNumber].isRight;

		const bool isFlip = m_messageElement[textNumber].isFlip;

		if (isRightDraw == isFlip)
		{
			return false;
		}

		if (!isRightDraw == isFlip)
		{
			return true;
		}
	}

	return false;
}
