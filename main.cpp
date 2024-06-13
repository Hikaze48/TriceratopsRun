//�w�b�_�t�@�C���ǂݍ���
#include "DxLib.h"
#include "fps.h"
#include "game.h"
#include "key.h"
#include "mouse.h"
#include "font.h"
#include "music.h"
#include "graphic.h"
#include "animation.h"

//�v���g�^�C�v�錾
VOID GameAndDxLibAllEnd(VOID);	//�Q�[���I���̌�n��

//�Q�[���I���̌�n��
//������???_End�n���ł߂�
VOID GameAndDxLibAllEnd(VOID)
{
	Font_End();			//�t�H���g��n��
	Music_End();		//���y��n��
	Graphic_End();		//�摜��n��
	Animation_End();	//�A�j���[�V������n��
	DxLib_End();		//DxLib�I��

	return;
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR IpCmdLine, _In_ int nCmdShow)
{
	SetOutApplicationLogValidFlag(FALSE);				//Log.txt���o�͂��Ȃ�
	ChangeWindowMode(TRUE);								//�E�B���h�E���[�h�ɐݒ�
	SetGraphMode(GameWidth, GameHeight, GameColor);		//�𑜓x��ݒ�
	SetWindowSize(GameWidth, GameHeight);				//�E�B���h�E�̑傫����ݒ�
	SetMainWindowText(GameTitle);						//�E�B���h�E�̃^�C�g��
	SetBackgroundColor(0, 0, 0);						//�E�B���h�E�̔w�i�F
	SetWaitVSyncFlag(GameVsync);						//���������̐ݒ�
	SetAlwaysRunFlag(TRUE);								//��A�N�e�B�u�ł����s����

	SetWindowIconID(GameIcon);							//�A�C�R����ݒ�

	if (DxLib_Init() == -1) //DxLib������
	{
		return -1; //DxLib���������s�Ȃ�\�t�g�I��
	}

	//����ʂɕ`�悷��i�_�u���o�b�t�@�����O�j
	SetDrawScreen(DX_SCREEN_BACK);

	//�t�H���g������
	if (Font_Init() == FALSE)
	{
		//�Q�[���I���̌�n��
		GameAndDxLibAllEnd();

		return -1;
	}

	//���y������
	if (Music_Init() == FALSE)
	{
		GameAndDxLibAllEnd();	//�Q�[���I���̌�n��
		return -1;
	}

	//�摜������
	if (Graphic_Init() == FALSE)
	{
		GameAndDxLibAllEnd();	//�Q�[���I���̌�n��
		return -1;
	}

	//�A�j���[�V����������
	if (Animation_Init() == FALSE)
	{
		GameAndDxLibAllEnd();	//�Q�[���I���̌�n��
		return -1;
	}

	//�Q�[����ʏ�����
	GameInit();

	//FPS������
	FPSInit();

	//�L�[�{�[�h������
	KeyInit();

	//�}�E�X������
	MouseInit();

	//�^�C�g���V�[����������
	TitleInit();

	//�������[�v�i�Q�[�����[�v�j
	while (TRUE)
	{
		//���b�Z�[�W����������i�}�E�X�����L�[���͂Ȃǂ��󂯑�����j
		if (ProcessMessage() != 0)
		{
			break; //�������[�v����o��i�Q�[���I���j
		}

		//��ʂ���������i1���[�v������������j
		if (ClearDrawScreen() != 0)
		{
			break; //�������[�v����o��i�Q�[���I���j 
		}

		//�����ɑS�ẴQ�[�����삪����
		{
			//DrawString(0, 0, "Hello DxLib", GetColor(255, 255, 255)); //��������ʂɏo��
			FPSCheck();		//FPS�v��
			KeyUpdate();	//�L�[�{�[�h�X�V
			MouseUpdate();	//�}�E�X�X�V

			//���̃V�[����������
			if (NowGameScene != ChangeGameScene)
			{
				//�e�V�[���̏��������Ăяo��
				switch (ChangeGameScene)
				{
				case TitleScene:
					TitleInit();
					break;
				case PlayScene:
					PlayInit();
					break;
				case ResultScene:
					ResultInit();
					break;
				default:
					break;
				}

				//�V�[���؂�ւ���̃V�[�������݂̃V�[���ɂ���
				NowGameScene = ChangeGameScene;
			}
			else
			{
				//�V�[���؂�ւ�
				switch (NowGameScene)
				{
				case TitleScene:
					TitleCtrl();
					break;
				case PlayScene:
					PlayCtrl();
					break;
				case ResultScene:
					ResultCtrl();
					break;
				default:
					break;
				}
			}

			FPSDraw(); //FPS�`��
			FPSWait(); //FPS�ҋ@
		}

		//����ʂ���ʂɕ`��
		ScreenFlip();
	}

	//WaitKey(); //�ǂꂩ�̃L�[����́i������܂ŉ�ʂ���Ȃ��j

	//DxLib_End(); //DxLib�I��

	//�Q�[���I���̌�n��
	GameAndDxLibAllEnd();

	return 0; //�\�t�g�I��
}