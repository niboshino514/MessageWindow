#include "MessageWindow.h"
#include "Pad.h"
#include <DxLib.h>
#include "Vec2.h"
#include "game.h"
#include <cassert>
#include "EvoLib.h"



namespace
{
	// �e�L�X�g�X�s�[�h
	constexpr int kTextSpeed = 5;

	// �����̑傫��
	constexpr int kFontScale = 30;

	// �t�H���g
	struct Font
	{
		// �t�@�C���p�X
		const char* FilePath = "";

		// �t�H���g��
		const char* FontName = "";
	};

	// �t�H���g
	const std::vector<Font> kFont =
	{
		{"Data/Font/font1.ttf","DotGothic16"},
		{"Data/Font/font2.otf","07�₳�����A���`�b�N"},
	};

	// �e�L�X�g�v�f
	struct TextElement
	{
		// �e�L�X�g
		const char* text = "";

		// �L�����N�^�[�ԍ�
		int characterNumber = 0;

		// �E�[�ɕ\�����邩�ǂ���
		bool isRightDraw = false;

		// �e�L�X�g�̃t�H���g�J���[
		int color = 0xffffff;

		// �e�L�X�g�X�s�[�h
		int textSpeed = kTextSpeed;

		// �e�L�X�g�T�C�Y
		float textSize = kFontScale;

		// �t�H���g�^�C�v
		int fontType = 1;

		// ������k�킹�邩�ǂ���
		bool isVibration = false;
	};

	// �e�L�X�g�v�f
	const std::vector<TextElement> kTextElement =
	{

		{ "�C����������ˁB\n����A���Ԃɏo�����Ĉ��삪���Ȃ�����A��ɏo�Ă݂��񂾂��ǁc�c�ǂ��ɍs���Ă������킩��Ȃ���B�Â��āB", 0},
		{ "�����Ȃ̂�ˁ`�B���������o�邵�A���܂�Ȃ���B", 1 ,true},
		{ "���āA���񂽒N�H", 0 },
		{ "���������������Ȃ��B���񂽁A���������Ē��ځH", 1,true},
		{ "�l�͈Â��Ƃ���ł͕����ǂ������Ȃ��̂�B", 0 },
		{ "����H�@�邵���������Ȃ��l���������Ƃ���C�������B", 1,true },
		{ "����͎���ĐH�ׂ��肵�Ă������̂�B", 0 },
		{ "���[�Ȃ̂��[�B", 1,true },
		{ "�ŁA�ז��Ȃ�ł����ǁB", 0},
		{ "�ڂ̑O������ĐH�ׂ��l�ށH", 1,true },
		{ "�ǖ�͌��ɋꂵ���Č��t�m���Ă�H", 0},
		{ "�ǖ���Ă����Ă��A����ł݂Ȃ����킩��Ȃ����ǂˁB", 0},
	};
}

// ���b�Z�[�W�E�B���h�E
namespace Window
{

	// ���b�Z�[�W�E�B���h�E�̏c��
	constexpr float kMessageWindowHeight = 200.0f;

	// ��ʒ[���烁�b�Z�[�W�E�B���h�E�̉���
	constexpr float kMessageWindowEdge = 300.0f;
	
	// ��ʉ����烁�b�Z�[�W�E�B���h�E�܂ł̍���
	constexpr float kMessageWindowHeightFromBottom = 100.0f;
}

// �L�����N�^�[
namespace Character
{
	// �L�����N�^�[�̏c��
	constexpr float kCharacterHeight = 600.0f;

	// �L�����N�^�[�̉���
	constexpr float kCharacterWidth = 400.0f;


	// ��ʒ[����L�����N�^�[�̉���
	constexpr float kCharacterEdge = 300.0f;

	// ��ʉ�����L�����N�^�[�܂ł̍���
	constexpr float kCharacterHeightFromBottom = 50.0f;

	// ��\�����̒��S���W����̋���
	constexpr float kHideDistance = 40.0f;


	// ���[�̃L�����N�^�[���S���W
	Vec2 kLeftCenterPos = Vec2();

	// �E�[�̃L�����N�^�[���S���W
	Vec2 kRightCenterPos = Vec2();

	// ���[�̔�\���L�����N�^�[���S���W
	Vec2 kLeftCenterPosHide = Vec2();

	// �E�[�̔�\���L�����N�^�[���S���W
	Vec2 kRightCenterPosHide = Vec2();




	// �L�����N�^�[�̃O���t�B�b�N�t�@�C���p�X
	const std::vector<const char*> kGraphFilePath =
	{
		"Data/Character/Character1.png",
		"Data/Character/Character2.png",
		"Data/Character/Character3.png"
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
	// �t�H���g�̍폜
	for(auto&font:m_textInfo.fontHandle)
	{
		DeleteFontToHandle(font);
	}


}

void MessageWindow::Init()
{

	// �E�B���h�E���̏�����
	{

		// �E�B���h�E�̒��S���W��ݒ�
		Vec2 windowCenterPos = Vec2();

		windowCenterPos.x = Game::kScreenWidth * 0.5f;
		windowCenterPos.y = (Game::kScreenHeight - Window::kMessageWindowHeightFromBottom) - (Window::kMessageWindowHeight * 0.5f);


		// �E�B���h�E�̍�����W��ݒ�
		m_windowInfo.leftTop.x = Window::kMessageWindowEdge;
		m_windowInfo.leftTop.y = windowCenterPos.y - (Window::kMessageWindowHeight * 0.5f);

		// �E�B���h�E�̉E�����W��ݒ�
		m_windowInfo.rightBottom.x = Game::kScreenWidth - Window::kMessageWindowEdge;
		m_windowInfo.rightBottom.y = windowCenterPos.y + (Window::kMessageWindowHeight * 0.5f);
	}


	// �e�L�X�g���̏�����
	{
		// �e�L�X�g�X�s�[�h���t���[���J�E���g�ɑ��
		m_textInfo.frameCount = kTextSpeed;

		// �e�L�X�g�ԍ���0�ɂ���
		m_textInfo.currentNumber = 0;

		// ���͂̕\���I���t���O��false�ɂ���
		m_textInfo.isEndText = false;

		// ������𑁂��`�悷��t���O��false�ɂ���
		m_textInfo.isFastDraw = false;

		// �������\�����邩���w�肷��
		m_textInfo.dispCharCount = 0;

		// �������}������
		m_textInfo.m_temp = kTextElement[0].text;


		// �t�H���g�֘A
		{

			for (auto& font : kFont)
			{
				// �t�H���g�̕ۑ�
				m_textInfo.fontHandle.push_back(EvoLib::Load::LoadFont(font.FilePath, font.FontName, kFontScale));
			}


			// �t�H���g�T�C�Y���擾
			int fontSize = GetDrawStringWidthToHandle("L", 1, m_textInfo.fontHandle[0]);
			
			// �e�L�X�g�̍��W��ݒ�
			m_textInfo.textPos = Vec2(m_windowInfo.leftTop.x + fontSize, m_windowInfo.leftTop.y + fontSize);
		}
	}

	// �L�����N�^�[���̏�����
	{


		// ���W�֘A
		{
			// �L�����N�^�[�̒��S���W��ݒ�
			Vec2 characterCenterPos = Vec2();

			characterCenterPos.x = Game::kScreenWidth * 0.5f;
			characterCenterPos.y = (Game::kScreenHeight - Character::kCharacterHeightFromBottom) - (Character::kCharacterHeight * 0.5f);

			// �L�����N�^�[�̍��[���W��ݒ�
			Character::kLeftCenterPos.x = Character::kCharacterEdge;
			Character::kLeftCenterPos.y = characterCenterPos.y;

			// �L�����N�^�[�̉E�[���W��ݒ�
			Character::kRightCenterPos.x = Game::kScreenWidth - Character::kCharacterEdge;
			Character::kRightCenterPos.y = characterCenterPos.y;

			// �L�����N�^�[�̍��[��\�����W��ݒ�
			Character::kLeftCenterPosHide.x = Character::kLeftCenterPos.x - Character::kHideDistance;
			Character::kLeftCenterPosHide.y = Character::kLeftCenterPos.y + Character::kHideDistance;

			// �L�����N�^�[�̉E�[��\�����W��ݒ�
			Character::kRightCenterPosHide.x = Character::kRightCenterPos.x + Character::kHideDistance;
			Character::kRightCenterPosHide.y = Character::kRightCenterPos.y + Character::kHideDistance;
		}
		
		// �L�����N�^�[�̃O���t�B�b�N�n���h���̎擾
		{
			m_characterInfo.resize(static_cast<int>(Character::kGraphFilePath.size()));

			for (int i = 0; i < static_cast<int>(m_characterInfo.size()); i++)
			{
				m_characterInfo[i].graphicHandle = LoadGraph(Character::kGraphFilePath[i]);
			}
		}

		// ��Ԃ͂��߂ɕ\������L�����N�^�[�̍��W��ݒ�
		InitCharacterPos(kTextElement[m_textInfo.currentNumber].isRightDraw);

	}

}

void MessageWindow::Update()
{
	// �e�L�X�g�����̌Ăяo��
	UpdateTextDisplay();

	// �e�L�X�g��؂�ւ��鏈��
	UpdateTextOnInput();

	// �L�����N�^�[�̍X�V����
	UpdateCharacter();
}

void MessageWindow::Draw()
{
	// �L�����N�^�[�̕`��
	DrawCharacter();

	// ���b�Z�[�W�E�B���h�E�̕`��
	DrawMessageWindow();


	DrawMessageText();
}

void MessageWindow::UpdateTextDisplay()
{
	// ���͂̕\�����I����Ă����ꍇ�A�������I������
	if (m_textInfo.isEndText)
	{
		return;
	}

	if (!m_textInfo.isFastDraw)
	{
		// �t���[���J�E���g�����炷
		m_textInfo.frameCount--;

		// �t���[���J�E���g��0�ɂȂ������A�e�L�X�g�X�s�[�h���t���[���J�E���g�ɑ�����A�\�����镶�����𑝂₷
		if (m_textInfo.frameCount <= 0)
		{
			// �e�L�X�g�X�s�[�h���t���[���J�E���g�ɑ��
			m_textInfo.frameCount = kTextSpeed;

			// �\�����镶�����𑝂₷
			m_textInfo.dispCharCount++;
		}
	}
	else
	{
		// �\�����镶�����𑝂₷
		m_textInfo.dispCharCount++;
	}

	// �o�C�g�����J�E���g
	int currentByte = 0;

	for (int i = 0; i < m_textInfo.dispCharCount; i++)
	{
		if (currentByte >= m_textInfo.m_temp.size())
		{
			m_textInfo.isEndText = true;

			// �\�����镶�����S�ĕ\��������A�\�����镶�����𕶎���̒����ɂ���
			m_textInfo.dispCharCount = static_cast<int>(m_textInfo.m_temp.size());

			break;
		}

		unsigned char charData = m_textInfo.m_temp[currentByte];    // �`�F�b�N���镶��
		if (charData == '\n') {
			// ���s�����̏ꍇ
			currentByte += 1; // ���s�������X�L�b�v
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
			// ������
			{
				// �\�����镶������������
				m_textInfo.dispCharCount = 0;

				// ���͂̕\���I���t���O��false�ɂ���
				m_textInfo.isEndText = false;

				// ������𑁂��`�悷��t���O��false�ɂ���
				m_textInfo.isFastDraw = false;

				// �t���[���J�E���g���e�L�X�g�X�s�[�h�ɑ��
				m_textInfo.frameCount = kTextElement[m_textInfo.currentNumber].textSpeed;
			}

			// ���݂̑I�����ڂ�����ɂ��炷(���[�v����)
			m_textInfo.currentNumber = EvoLib::Calculation::SelectLoopNumber(0, static_cast<int>(kTextElement.size()), m_textInfo.currentNumber);

			// �������}������
			m_textInfo.m_temp = kTextElement[m_textInfo.currentNumber].text;

			// �L�����N�^�[���W������
			InitCharacterPos(kTextElement[m_textInfo.currentNumber].isRightDraw);
		}
		else
		{
			// ������𑁂��`�悷��t���O��true�ɂ���
			m_textInfo.isFastDraw = true;
		}
	}
}

void MessageWindow::DrawMessageText()
{

	// �e�L�X�g�̍��W
	Vec2 textPos = m_textInfo.textPos;

	int currentByte = 0;

	// �t�H���g�ԍ�
	const int fontNumber = kTextElement[m_textInfo.currentNumber].fontType;

	// �t�H���g�n���h���̌���i��F����̕����ʒu�Ńt�H���g��ύX����j
	const int fontHandle = m_textInfo.fontHandle[fontNumber];

	// �e�L�X�g�̐F
	const int color = kTextElement[m_textInfo.currentNumber].color;

	const float lineSpace = kTextElement[m_textInfo.currentNumber].textSize * 0.4f; // �s��



	for (int i = 0; i < m_textInfo.dispCharCount; i++)
	{
		if (currentByte >= m_textInfo.m_temp.size()) break;
		unsigned char charData = m_textInfo.m_temp[currentByte];
		int size = 0;

	

		if (charData == '\n') 
		{
			// ���s�����̏ꍇ
			textPos.x = m_textInfo.textPos.x; // �s�̐擪�ɖ߂�
			textPos.y += GetFontSizeToHandle(fontHandle); // �s�̍��������Z
			textPos.y += lineSpace; // �s�Ԃ����Z

			currentByte += 1; // ���s�������X�L�b�v
			continue;
		}
		else if (IsTextInWindow(textPos, fontHandle))
		{
			textPos.x = m_textInfo.textPos.x; // �s�̐擪�ɖ߂�
			textPos.y += GetFontSizeToHandle(fontHandle); // �s�̍��������Z
			textPos.y += lineSpace; // �s�Ԃ����Z
		}
		else if (charData < 0x80) {
			size = 1;
		}
		else {
			size = 2;
		}

		int shakeX = GetRand(2) - 1;
		int shakeY = GetRand(2) - 1;

		// �e�L�X�g�̗h���ݒ�
		if (!kTextElement[m_textInfo.currentNumber].isVibration)
		{
			shakeX = 0;
			shakeY = 0;
		}

		Vec2 shakePos = textPos;
		shakePos.x += shakeX;
		shakePos.y += shakeY;

		

		// ������̕`��
		DrawStringFToHandle(shakePos.x, shakePos.y, m_textInfo.m_temp.substr(currentByte, size).c_str(), color, fontHandle);

		textPos.x += GetDrawStringWidth(m_textInfo.m_temp.substr(currentByte, size).c_str(), size, fontHandle);

		currentByte += size;
	}
}


int MessageWindow::GetDrawStringWidth(const char* str, const int& length, const int& fontHandle)
{
	// ������̕����v�Z
	int originalWidth = GetDrawStringWidthToHandle(str, length, fontHandle);
	return originalWidth;
}

bool MessageWindow::IsTextInWindow(const Vec2 textPos, const int fontHandle)
{
	// �t�H���g�T�C�Y���擾
	const int fontSize = GetFontSizeToHandle(fontHandle);

	// �e�L�X�g�̉E�[���W���v�Z
	const float textRightPos = textPos.x + fontSize;

	// �e�L�X�g�̉E�[���W���E�B���h�E�̉E�[���W�𒴂��Ă���ꍇ�Atrue��Ԃ�
	if (m_windowInfo.rightBottom.x <= textRightPos)
	{
		return true;	
	}

	return false;
}





void MessageWindow::DrawMessageWindow()
{
	// �`��u�����h���[�h���A���t�@�u�����h�i�T�O���j�ɂ���
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);

	// ���b�Z�[�W�E�B���h�E�̕`��
	DrawBoxAA(m_windowInfo.leftTop.x, m_windowInfo.leftTop.y, m_windowInfo.rightBottom.x, m_windowInfo.rightBottom.y, 0xffffff, true);
	
	// �`��u�����h���[�h���m�[�u�����h�ɂ���
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);



	// ���b�Z�[�W�E�B���h�E�̕`��
	DrawBoxAA(m_windowInfo.leftTop.x, m_windowInfo.leftTop.y, m_windowInfo.rightBottom.x, m_windowInfo.rightBottom.y, 0xffffff, false);
}

void MessageWindow::InitCharacterPos(const bool& isRightDraw)
{
	// �L�����N�^�[�ԍ�
	const int characterNumber = kTextElement[m_textInfo.currentNumber].characterNumber;

	// ��O�̃e�L�X�g�ԍ�
	const int beforeTextNumber = m_textInfo.currentNumber - 1;



	if (beforeTextNumber < 0)
	{
		SetUpCharacterPos(kTextElement[m_textInfo.currentNumber].isRightDraw, characterNumber, false);

		return;
	}

	// �L�����N�^�[�ԍ�
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
		// ���[�ɕ\�����邩�ǂ���
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
		// ���[�ɕ\�����邩�ǂ���
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

	// �ړ��ʂ�������
	m_characterInfo[characterNumber].vec = Vec2();

	// �E���ɕ\������Ă��邩�ǂ���
	m_characterInfo[characterNumber].isRightDraw = isRightDraw;
}

void MessageWindow::UpdateCharacter()
{

	// �L�����N�^�[�ԍ�
	const int characterNumber = kTextElement[m_textInfo.currentNumber].characterNumber;

	
	// �L�����N�^�[�̍��W���ړ�
	m_characterInfo[characterNumber].vec = EvoLib::Calculation::TargetMoveValue(m_characterInfo[characterNumber].pos, m_characterInfo[characterNumber].targetPos, 0.1f);


	m_characterInfo[characterNumber].pos += m_characterInfo[characterNumber].vec;


	// ��O�̃e�L�X�g�ԍ�
	const int beforeTextNumber = m_textInfo.currentNumber - 1;

	// ��O�̃e�L�X�g�ԍ���0�����̏ꍇ�A�������I������
	if (beforeTextNumber < 0)
	{
		return;
	}

	// �L�����N�^�[�ԍ�
	const int characterBeforeNumber = kTextElement[beforeTextNumber].characterNumber;


	// �L�����N�^�[�̍��W���ړ�
	m_characterInfo[characterBeforeNumber].vec = EvoLib::Calculation::TargetMoveValue(m_characterInfo[characterBeforeNumber].pos, m_characterInfo[characterBeforeNumber].targetPos, 0.1f);

	m_characterInfo[characterBeforeNumber].pos += m_characterInfo[characterBeforeNumber].vec;
}

void MessageWindow::DrawCharacter()
{
	// ���݂̃L�����N�^�[�ԍ�
	const int characterNumber = kTextElement[m_textInfo.currentNumber].characterNumber;

	// �O��̃L�����N�^�[�ԍ�
	int characterBeforeNumber = 0;

	// ��O�̃e�L�X�g�ԍ�
	const int beforeTextNumber = m_textInfo.currentNumber - 1;

	
	// �L�����N�^�[�̕`��
	DrawRotaGraph(m_characterInfo[characterNumber].pos.x, m_characterInfo[characterNumber].pos.y, 1.0, 0.0, m_characterInfo[characterNumber].graphicHandle, true);
	

	// �������ɂ��ĕ`��
	{
		// ��O�̃e�L�X�g�ԍ���0�����̏ꍇ�A�������I������
		if (beforeTextNumber < 0)
		{
			return;
		}

		// �O��̃L�����N�^�[�ԍ����
		characterBeforeNumber = kTextElement[beforeTextNumber].characterNumber;



		// �ǂ��炩�Е��ɃL�����N�^�[���\������Ă��Ȃ��ꍇ�A�\��������
 		if(kTextElement[m_textInfo.currentNumber].isRightDraw == kTextElement[beforeTextNumber].isRightDraw)
		{
			bool isRightDraw = kTextElement[m_textInfo.currentNumber].isRightDraw;

			for (int i = m_textInfo.currentNumber; i >= 0; --i)
			{
				if (isRightDraw != kTextElement[i].isRightDraw)
				{
					// �`��u�����h���[�h���A���t�@�u�����h�i�T�O���j�ɂ���
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);

					int test = kTextElement[i].characterNumber;


					DrawRotaGraph(m_characterInfo[test].pos.x, m_characterInfo[test].pos.y, 1.0, 0.0, m_characterInfo[test].graphicHandle, true);

					// �`��u�����h���[�h���m�[�u�����h�ɂ���
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

					return;
				}
			}
		}
		else
		{
			// �`��u�����h���[�h���A���t�@�u�����h�i�T�O���j�ɂ���
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);

			DrawRotaGraph(m_characterInfo[characterBeforeNumber].pos.x, m_characterInfo[characterBeforeNumber].pos.y, 1.0, 0.0, m_characterInfo[characterBeforeNumber].graphicHandle, true);

			// �`��u�����h���[�h���m�[�u�����h�ɂ���
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	}
}