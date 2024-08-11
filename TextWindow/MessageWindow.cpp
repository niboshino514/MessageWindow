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
	m_pMessageTextLoader(std::make_shared<MessageTextLoader>())
{
}

MessageWindow::~MessageWindow()
{
	// フォントの削除
	for (auto& font : m_textInfo.fontHandle)
	{
		DeleteFontToHandle(font);
	}
}

void MessageWindow::Init()
{
	// ロードデータ
	const MessageTextLoader::LoadData loadData = m_pMessageTextLoader->LoadTextData();

	// 会話情報
	{
		// 会話データのサイズ
		const int talkDataSize = loadData.talkData.size();

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
			// フォントサイズを取得
			m_textInfo.fontSize = loadData.fontData.fontSize;


			// フォントの数だけループ
			for (int i = 0; i < loadData.fontData.fontFilePath.size(); i++)
			{
				// フォントの保存
				m_textInfo.fontHandle.push_back
				(EvoLib::Load::LoadFont(loadData.fontData.fontFilePath[i].c_str(), loadData.fontData.fontName[i].c_str(), m_textInfo.fontSize));
			}


			// キャラクター名のフォントを取得
			m_textInfo.nameFontHandle =
				EvoLib::Load::LoadFont(loadData.fontData.fontFilePath[loadData.fontData.characterNameFontType].c_str(), loadData.fontData.fontName[loadData.fontData.characterNameFontType].c_str(), loadData.fontData.characterNameFontSize);



			// キャラクター名の文字横間隔を設定
			m_textInfo.characterNameCharInterval = loadData.fontData.characterNameCharInterval;

			// フォントサイズを取得
			int fontSize = GetDrawStringWidthToHandle("L", 1, m_textInfo.fontHandle[0]);
			
			// テキストの座標を設定
			m_textInfo.textPos = Vec2(m_windowInfo.leftTop.x + fontSize, m_windowInfo.leftTop.y + fontSize);
		}
	}

	// キャラクター情報の初期化
	{
		// キャラクターのグラフィックハンドルの取得
		{
			// キャラクターデータのサイズ
			const int characterGraphFilePathSize = loadData.characterData.characterFilePath.size();
	
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
		m_graphNotSpeakAlpha= EvoLib::Convert::ConvertFromPercentToValue(255, loadData.characterData.characterNotSpeakAlphaPercentage);


		// 一番はじめに表示するキャラクターの座標を設定
		InitCharacterPos(m_messageElement[m_textInfo.currentNumber].isRight);
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

	for (int i = 0; i < m_textInfo.dispCharCount; i++)
	{
		const int tempSize = m_textInfo.m_temp.size();

		if (currentByte >= m_textInfo.m_temp.size())
		{
			m_textInfo.isEndText = true;

			// 表示する文字列を全て表示したら、表示する文字数を文字列の長さにする
			m_textInfo.dispCharCount = static_cast<int>(m_textInfo.m_temp.size());

			break;
		}

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

	// テキストの座標
	Vec2 textPos = m_textInfo.textPos;

	int currentByte = 0;

	// フォント番号
	const int fontNumber = m_messageElement[m_textInfo.currentNumber].fontType;

	// フォントハンドルの決定（例：特定の文字位置でフォントを変更する）
	const int fontHandle = m_textInfo.fontHandle[fontNumber];

	// テキストの色
	const int color = m_messageElement[m_textInfo.currentNumber].fontColor;

	// 行間
	const float lineSpace = m_textInfo.fontSize * m_messageElement[m_textInfo.currentNumber].lineInterval; // 行間

	// 改行したかどうか
	bool isLineBreak = false;

	bool isLineBreak_test = false;

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
				textPos.x += m_messageElement[m_textInfo.currentNumber].charInterval;
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
		if (!m_messageElement[m_textInfo.currentNumber].isShake)
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

void MessageWindow::UpdateCharacter()
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
	DrawRotaGraph(m_characterInfo[characterNumber].pos.x, m_characterInfo[characterNumber].pos.y, m_characterInfo[characterNumber].scale, 0.0, m_characterInfo[characterNumber].graphicHandle[m_messageElement[m_textInfo.currentNumber].talkFaceNo], true, isGraphReverse);
	

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

					
					if(isRightDraw == m_characterInfo[number].isRightDraw)
					{
						continue;
					}



					isGraphReverse = IsFlipCharacter(number, i);



					DrawRotaGraph(m_characterInfo[number].pos.x, m_characterInfo[number].pos.y, m_characterInfo[number].scale, 0.0, m_characterInfo[number].graphicHandle[m_messageElement[i].talkFaceNo], true, isGraphReverse);

					// 描画ブレンドモードをノーブレンドにする
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

					return;
				}
			}
		}
		else
		{

			isGraphReverse = IsFlipCharacter(characterBeforeNumber, beforeTextNumber);

			// 描画ブレンドモードをアルファブレンド
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_graphNotSpeakAlpha);

			DrawRotaGraph(m_characterInfo[characterBeforeNumber].pos.x, m_characterInfo[characterBeforeNumber].pos.y, m_characterInfo[characterBeforeNumber].scale, 0.0, m_characterInfo[characterBeforeNumber].graphicHandle[m_messageElement[beforeTextNumber].talkFaceNo], true, isGraphReverse);

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
}
