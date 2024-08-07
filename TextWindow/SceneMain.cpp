#include <DxLib.h>
#include "SceneMain.h"
#include "Vec2.h"
#include "game.h"
#include "Pad.h"

#include "MessageWindow.h"




namespace
{
	// �e�L�X�g�̈ʒu
	const Vec2 kTextPos = { 0.0f, 0.0f};

	// �e�L�X�g
	const char* const kText = "TestCode";

	// �e�L�X�g�F
	constexpr int kTextColor = 0xffffff;

	// �w�i�F
	constexpr int kBackGroundColor = 0x000000;

	// �w�i�̃��l(255���ő��0�ɋ߂Â����A�����ɂȂ�)
	constexpr int kBackGroundAlpha = 255;
}



SceneMain::SceneMain():
	m_pMessageWindow(std::make_shared<MessageWindow>())
{
}

SceneMain::~SceneMain()
{
}

void SceneMain::init()
{
	// ���b�Z�[�W�E�B���h�E�̏�����
	m_pMessageWindow->Init();
}

SceneBase* SceneMain::update()
{

	// ���b�Z�[�W�E�B���h�E�̍X�V
	m_pMessageWindow->Update();

	return this;
}

void SceneMain::draw()
{
	// �����ɂ��ĕ\������
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, kBackGroundAlpha);
	// �w�i
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, kBackGroundColor, true);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// �e�L�X�g�`��
	DrawStringF(kTextPos.x, kTextPos.y, kText, kTextColor);

	////////////////////////
	// �������珈�������� //
	////////////////////////


	// ���b�Z�[�W�E�B���h�E�̕`��
	m_pMessageWindow->Draw();
	




}