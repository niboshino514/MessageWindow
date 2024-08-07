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


	

	// �e�L�X�g���
	struct TextInfo
	{
		// �e�L�X�g�̍��W
		Vec2 textPos = Vec2(0, 0);

		// �e�L�X�g�ԍ�
		int currentNumber = 0;

		// ���͂̕\�����I��������ǂ���
		bool isEndText = false;

		// ������𑁂��`�悷�邩�ǂ���
		bool isFastDraw = false;

		// ������i�[
		std::string m_temp = "";

		// �i���؂�ւ��t���O
		bool isParagraph = false;

		// �t���[�����J�E���g
		int frameCount = 0;

		// �\�����镶����
		int dispCharCount = 0;

		// �t�H���g�n���h��
		std::vector<int> fontHandle;
	};

	// �E�B���h�E���
	struct WindowInfo
	{
		// �E�B���h�E�̍�����W
		Vec2 leftTop = Vec2();

		// �E�B���h�E�̉E�����W
		Vec2 rightBottom = Vec2();

		// �L�����N�^�[����\������E�B���h�E�̍�����W
		Vec2 nameLeftTop = Vec2();

		// �L�����N�^�[����\������E�B���h�E�̉E�����W
		Vec2 nameRightBottom = Vec2();

		// �L�����N�^�[����\������E�B���h�E�̉���
		int nameWindowWidth = 0;
	};

	// �L�����N�^�[���
	struct CharacterInfo
	{
		// �L�����N�^�[�O���t�B�b�N�n���h��
		int graphicHandle = -1;

		// �L�����N�^�[��
		std::string name = "";

		// �L�����N�^�[�g�嗦
		float scale = 1.0f;

		// �L�����N�^�[�̍��W
		Vec2 pos = Vec2();

		// �^�[�Q�b�g���W
		Vec2 targetPos = Vec2();

		// �ړ���
		Vec2 vec = Vec2();

		// �E���ɕ\������Ă��邩�ǂ���
		bool isRightDraw = false;
	};


private:

	/// <summary>
	/// �e�L�X�g�\���i�s
	/// </summary>
	void UpdateTextDisplay();

	/// <summary>
	/// ���͎��Ƀe�L�X�g�̍X�V
	/// </summary>
	void UpdateTextOnInput();

	/// <summary>
	/// �e�L�X�g�`��
	/// </summary>
	void DrawMessageText();

	void DrawCharacterNameText();

	/// <summary>
	/// ������̃T�C�Y���擾
	/// </summary>
	/// <param name="str">������</param>
	/// <param name="length">���ׂ镶��</param>
	/// <param name="fontHandle">�t�H���g�n���h��</param>
	/// <returns>������̃T�C�Y</returns>
	int GetDrawStringWidth(const char* str, const int& length, const int& fontHandle);

	// �����񂪃��b�Z�[�W�E�B���h�E�Ɏ��܂邩�ǂ���
	bool IsTextInWindow(const Vec2 textPos, const int fontHandle);



	/// <summary>
	/// ���b�Z�[�W�E�B���h�E�̕`��
	/// </summary>
	void DrawMessageWindow();

	

	/// <summary>
	/// �L�����N�^�[�̏����ʒu�ݒ�
	/// </summary>
	/// <param name="isRightDraw">�E�ɕ\�����邩�ǂ���</param>
	void InitCharacterPos(const bool& isRightDraw);

	/// <summary>
	/// �L�����N�^�[�̈ʒu�ݒ�
	/// </summary>
	/// <param name="isRightDraw">�E�ɕ\�����邩�ǂ���</param>
	/// <param name="characterNumber">�L�����N�^�[�ԍ�</param>
	/// <param name="isBeforeNumber">�O�̃L�����N�^�[�ԍ����ǂ���</param>
	void SetUpCharacterPos(const bool& isRightDraw, const int& characterNumber, const bool isBeforeNumber);


	void UpdateCharacter();

	void DrawCharacter();

private:

	// �e�L�X�g���
	TextInfo m_textInfo;

	// �E�B���h�E���
	WindowInfo m_windowInfo;


	// �L�����N�^�[���
	std::vector<CharacterInfo> m_characterInfo;





	// �L�����N�^�[�̈ړ����x
	float m_characterMoveSpeed = 0.0f;


};

