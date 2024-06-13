//�Q�[�������̃\�[�X�t�@�C��

//�w�b�_�t�@�C���ǂݍ���
#include "game.h"
#include "key.h"
#include "mouse.h"
#include "geometory.h"
#include "font.h"
#include "music.h"
#include "graphic.h"
#include "animation.h"
#include <math.h>

//�O���[�o���ϐ�

//�Q�[���V�[��
enum GameScene NowGameScene;	//���݂̃Q�[���V�[��
enum GameScene ChangeGameScene;	//�؂�ւ��Q�[���V�[��
SCORE score;

//�Q�[����ʊ֌W
RECT GameWindow;				//�Q�[����ʂ̋�`
HWND GameHandle;				//�Q�[���̃E�B���h�E�n���h��

double EnemyCreateTime = 0.0f;			//�G�����J�E���g
double EnemyCreateTimeMAX = 0.0f;		//�G�����J�E���gMAX

BOOL IsGameOverFlg = FALSE;		//�Q�[���I�[�o�[�t���O
BOOL IsAvoidFlg = FALSE;		//������t���O

double StiffnessTime = 0.0f;	//��������̍d������

//�Q�[���V�[���̖��O
char GameSceneName[GameSceneCount][GameSceneNameMax]
{
	"�^�C�g�����",
	"�v���C���",
	"���U���g���"
};

//�V�[���؂�ւ���̃t���[�������Ǘ�
int GameSceneFrameCount[GameSceneCount];

//�֐�

//�Q�[����ʂ̃n���h�����擾
HWND GetGameHandle(VOID)
{
	return GameHandle;
}

//�Q�[����ʂ̋�`���擾
RECT GetGameWindow(VOID)
{
	return GameWindow;
}

//�Q�[����ʂ̏㉺���E�̒������W���擾
POINT GetGameWindowCenter(VOID)
{
	POINT pt;
	pt.x = GameWidth / 2;
	pt.y = GameHeight / 2;

	return pt;
}

//�Q�[����ʏ�����
VOID GameInit(VOID)
{
	//�Q�[����ʂ̃n���h��(�Ǘ��ԍ�)���擾
	GameHandle = GetMainWindowHandle();

	//�Q�[����ʂ̋�`���擾
	GameWindow = GetRect(0, 0, GameWidth, GameHeight);

	//�ŏ��̃V�[���̓^�C�g������
	NowGameScene = TitleScene;

	//���̃V�[�����^�C�g������
	ChangeGameScene = TitleScene;


	return;
}

//�^�C�g��������
VOID TitleInit(VOID)
{
	//�V�[����؂�ւ����t���[������������
	GameSceneFrameCount[ChangeGameScene] = 0;

	//�v���C��ʏ���

	//�X�R�A�f�[�^�֘A
	{
		//�X�R�A������
		score.ScorePoint = 0;

		//�X�R�A�f�[�^�����邩�m�F
		fopen_s(&score.Scorefp, ScoreDataPath, "r");
		if (score.Scorefp == NULL)
		{
			//�V���Ƀt�@�C���V�K�쐬
			fopen_s(&score.Scorefp, ScoreDataPath, "w");

			//�������f�[�^������
			fprintf_s(score.Scorefp, "%d", 0);
		}

		//�X�R�A�f�[�^��ǂݎ��
		fscanf_s(score.Scorefp, "%d", &score.ReadScore);

		//�X�R�A�f�[�^�����
		fclose(score.Scorefp);
	}

	IsGameOverFlg = FALSE;		//�Q�[���I�[�o�[�t���O

	AnimMyTriceratops.DINOa.g.c.Pos.x = GameWidth / 4 * 1 - AnimMyTriceratops.DINOa.g.c.Width / 2;
	AnimMyTriceratops.DINOa.g.c.Pos.y = Ground - AnimMyTriceratops.DINOa.g.c.Height;
	AnimMyTriceratops.JumpPower = JumpValue;		//�W�����v��
	AnimMyTriceratops.IsJump = FALSE;
	AnimMyTriceratops.XSpeed = 4.5;
	//�����蔻�蒲��
	AnimMyTriceratops.Ajust = AnimMyTriceratops.DINOa.g.c.Coll;
	AnimMyTriceratops.Ajust.left = 10;
	AnimMyTriceratops.Ajust.right = 10;
	AnimMyTriceratops.Ajust.top = 50;
	AnimMyTriceratops.Ajust.bottom = 20;


	AnimEnemyTriceratops.DINOa.g.c.Pos.x = GameWidth;
	AnimEnemyTriceratops.DINOa.g.c.Pos.y = Ground - AnimEnemyTriceratops.DINOa.g.c.Height;
	AnimEnemyTriceratops.JumpPower = JumpValue;		//�W�����v��
	AnimEnemyTriceratops.IsJump = FALSE;
	AnimEnemyTriceratops.IsJumpOver = FALSE;
	AnimEnemyTriceratops.XSpeed = 2.0;				//�����Ƃ�ƁB
	//�����蔻�蒲��
	AnimEnemyTriceratops.Ajust = AnimEnemyTriceratops.DINOa.g.c.Coll;
	AnimEnemyTriceratops.Ajust.left = 10;
	AnimEnemyTriceratops.Ajust.right = 10;
	AnimEnemyTriceratops.Ajust.top = 50;
	AnimEnemyTriceratops.Ajust.bottom = 20;


	AnimAnkylosaurus.DINOa.g.c.Pos.x = GameWidth;
	AnimAnkylosaurus.DINOa.g.c.Pos.y = Ground - AnimAnkylosaurus.DINOa.g.c.Height;
	AnimAnkylosaurus.JumpPower = JumpValue;				//�W�����v��
	AnimAnkylosaurus.IsJump = FALSE;
	AnimAnkylosaurus.IsJumpOver = FALSE;
	AnimAnkylosaurus.XSpeed = 4.0f;						//���΂₭�B
	//�����蔻�蒲��
	AnimAnkylosaurus.Ajust = AnimAnkylosaurus.DINOa.g.c.Coll;
	AnimAnkylosaurus.Ajust.left = 10;
	AnimAnkylosaurus.Ajust.right = 10;
	AnimAnkylosaurus.Ajust.top = 50;
	AnimAnkylosaurus.Ajust.bottom = 20;


	AnimPachycephalosaurus.DINOa.g.c.Pos.x = GameWidth;
	AnimPachycephalosaurus.DINOa.g.c.Pos.y = Ground - AnimPachycephalosaurus.DINOa.g.c.Height;
	AnimPachycephalosaurus.JumpPower = JumpValue;				//�W�����v��
	AnimPachycephalosaurus.IsJump = FALSE;
	AnimPachycephalosaurus.IsJumpOver = FALSE;
	AnimPachycephalosaurus.XSpeed = 5.0f;						//�r�X�����B
	//�����蔻�蒲��
	AnimPachycephalosaurus.Ajust = AnimPachycephalosaurus.DINOa.g.c.Coll;
	AnimPachycephalosaurus.Ajust.left = 20;
	AnimPachycephalosaurus.Ajust.right = 20;
	AnimPachycephalosaurus.Ajust.top = 0;
	AnimPachycephalosaurus.Ajust.bottom = 20;


	AnimSeismosaurus.DINOa.g.c.Pos.x = GameWidth;
	AnimSeismosaurus.DINOa.g.c.Pos.y = Ground - AnimSeismosaurus.DINOa.g.c.Height;
	AnimSeismosaurus.JumpPower = JumpValue;				//�W�����v��
	AnimSeismosaurus.IsJump = FALSE;
	AnimSeismosaurus.IsJumpOver = FALSE;
	AnimSeismosaurus.XSpeed = 3.0f;						//�Y��ɁB
	//�����蔻�蒲��
	AnimSeismosaurus.Ajust = AnimSeismosaurus.DINOa.g.c.Coll;
	AnimSeismosaurus.Ajust.left = 0;
	AnimSeismosaurus.Ajust.right = 0;
	AnimSeismosaurus.Ajust.top = 0;
	AnimSeismosaurus.Ajust.bottom = 20;

	for (int i = 0; i < EnemyOneTimeMax; i++)
	{
		Enemy[i].DINOa.g.c.IsDraw = FALSE;		//�G�̉摜�͑S�Ĕ�\��
	}

	TitleBackImage.c.Pos.x = 0;	//�w�i
	BackImageTurn.c.Pos.x = GameWidth;		//�w�i���]

	//�d������
	StiffnessTime = 5.0f;

	//�摜�G�t�F�N�g�J�n
	GraphicFxStart(
		&TitleButton,		//�ǂ̉摜�ɃG�t�F�N�g��������H
		GraFxFadeInOut,		//�ǂ�ȃG�t�F�N�g��������H
		GraFxInfinity,		//�G�t�F�N�g�����p��
		1000);				//1000�~���b�Ԋu

	//�A�j���[�V�����J�n
	AnimationStart(
		&AnimExpl,			//�ǂ̃A�j���[�V�������Đ�����H
		1000,				//�A�j���[�V�����p������
		500);				//500�~���b�Ԋu�Ŏ��̃R�}��

	/*
	//�A�j���[�V�����J�n
	AnimationStart(
		&AnimCoin,			//�ǂ̃A�j���[�V�������Đ�����H
		AnimationOnce,		//�A�j���[�V�����p������
		100);				//100�~���b�Ԋu�Ŏ��̃R�}��

	//�A�j���[�V�����J�n
	AnimationStart(
		&AnimSlash,			//�ǂ̃A�j���[�V�������Đ�����H
		AnimationInfinity,	//�A�j���[�V�����p������
		50);				//50�~���b�Ԋu�Ŏ��̃R�}��
	:*/

	if (GameDebug == TRUE)
	{
		//�V�[�����\��
		DrawFormatStringToHandle(
			GameWidth - 200, 0, Color_white,
			fontDefault.Handle,	//���̃t�H���g�f�[�^���g�p
			"%s%s", GameSceneName[NowGameScene], "������"
		);

		//�K�؂ȃV�[���̏��������ł��Ă��邩�e�X�g
		//ScreenFlip();
		//WaitTimer(1000);
	}

	return;
}
//�^�C�g���Ǘ�
VOID TitleCtrl(VOID)
{
	TitleProc();	//���������Ă���
	TitleDraw();	//�`�悷��!

	return;
}
//�^�C�g������
VOID TitleProc(VOID)
{
	//�V�[���؂�ւ���̃t���[�������J�E���g�A�b�v
	GameSceneFrameCount[NowGameScene]++;

	//�t�F�[�h�C�����čĐ�
	FadeInPlayMusic(&TitleBGM, 5000);	//5�b�����ăt�F�[�h�C��

	
	//�V�[���؂�ւ�
	if (CollRectToMouseDown(TitleButton.c.Coll, MOUSE_INPUT_LEFT) == TRUE	//�^�C�g���{�^���̂ǂ������}�E�X���{�^���ŉ������Ƃ�
		&& GameSceneFrameCount[NowGameScene] >= GameSceneChangeFrame
		|| KeyClick(KEY_INPUT_SPACE) == TRUE								//�X�y�[�X�L�[���������Ƃ�
		&& GameSceneFrameCount[NowGameScene] >= GameSceneChangeFrame)		//���A�؂�ւ��\�ȃt���[�����𒴂�����
	{
		//���ʉ�
		PlayMusic(ButtonClickSE);

		//���y��~
		PauseMusic(&TitleBGM);

		//�V�[���؂�ւ�
		ChangeGameScene = PlayScene;

		//�����ɐ؂�ւ���
		return;
	}


	return;
}
//�^�C�g���`��
VOID TitleDraw(VOID)
{
	//�����������قǉ��ɏ������
	DrawGraphic(&TitleBackImage);	//�w�i�摜��`��
	DrawGraphic(&TitleLogo);		//�^�C�g�����S��`��
	DrawGraphic(&TitleButton);		//�^�C�g���{�^����`��

	//�A�j���[�V�����������ɕ`��
	//DrawAnimation(&AnimExpl);		//�����A�j��(1��̂�)
	//DrawAnimation(&AnimCoin);		//�R�C���A�j��(����)
	//DrawAnimation(&AnimSlash);		//�a���A�j��(����)

	//�ō��X�R�A��`��
	DrawFormatStringToHandleAlign(
		GetGameWindowCenter().x, 50, Align_AllCenter, Color_black,
		fontJiyu100pt.Handle,	//���̃t�H���g�f�[�^���g�p
		"%s%05d", "�ō�SCORE:", score.ReadScore
	);

	if (GameDebug == TRUE)
	{
		/*
		//�K���ɕ`��
		DrawBox(0, 0, GameWidth, GameHeight, Color_skyblue, TRUE);
		*/

		//�V�[�����\��
		DrawFormatStringToHandle(
			GameWidth - 200, 0, Color_white,
			fontDefault.Handle,	//���̃t�H���g�f�[�^���g�p
			"%s%s", GameSceneName[NowGameScene], "�`�撆"
		);

		//�}�E�X�|�C���g�̕`��
		DrawFormatStringToHandleAlign(
			GetPointMouse().x, GetPointMouse().y, Align_AllCenter, Color_black,
			fontJiyu100pt.Handle,	//���̃t�H���g�f�[�^���g�p
			"Mouse:x%4d/Y%4d", GetPointMouse().x, GetPointMouse().y
		);
	}
	
	
	return;
}

//�v���C������
VOID PlayInit(VOID)
{
	//�V�[����؂�ւ����t���[������������
	GameSceneFrameCount[ChangeGameScene] = 0;

	AnimationStart(
		&AnimMyTriceratops.DINOa,	//�ǂ̃A�j���[�V�������Đ�����H
		AnimationInfinity,	//�A�j���[�V�����p������
		250);				//250�~���b�Ԋu�Ŏ��̃R�}��

	AnimationStart(
		&AnimEnemyTriceratops.DINOa,	//�ǂ̃A�j���[�V�������Đ�����H
		AnimationInfinity,	//�A�j���[�V�����p������
		250);				//250�~���b�Ԋu�Ŏ��̃R�}��

	AnimationStart(
		&AnimAnkylosaurus.DINOa,	//�ǂ̃A�j���[�V�������Đ�����H
		AnimationInfinity,	//�A�j���[�V�����p������
		250);				//250�~���b�Ԋu�Ŏ��̃R�}��

	AnimationStart(
		&AnimPachycephalosaurus.DINOa,	//�ǂ̃A�j���[�V�������Đ�����H
		AnimationInfinity,	//�A�j���[�V�����p������
		250);				//250�~���b�Ԋu�Ŏ��̃R�}��

	AnimationStart(
		&AnimSeismosaurus.DINOa,	//�ǂ̃A�j���[�V�������Đ�����H
		AnimationInfinity,	//�A�j���[�V�����p������
		250);				//250�~���b�Ԋu�Ŏ��̃R�}��

	AnimationStart(
		&AnimExpl,			//�ǂ̃A�j���[�V�������Đ�����H
		1000,				//�A�j���[�V�����p������
		500);				//500�~���b�Ԋu�Ŏ��̃R�}��

	if (GameDebug == TRUE)
	{
		//�V�[�����\��
		DrawFormatStringToHandle(
			GameWidth - 200, 0, Color_white,
			fontDefault.Handle,	//���̃t�H���g�f�[�^���g�p
			"%s%s", GameSceneName[NowGameScene], "������"
		);

		//�K�؂ȃV�[���̏��������ł��Ă��邩�e�X�g
		//ScreenFlip();
		//WaitTimer(1000);
	}

	return;
}
//�v���C�Ǘ�
VOID PlayCtrl(VOID)
{
	PlayProc();	//���������Ă���
	PlayDraw();	//�`�悷��!

	return;
}
//�v���C����
VOID PlayProc(VOID)
{
	score.ScorePoint++;

	//�V�[���؂�ւ���̃t���[�������J�E���g�A�b�v
	GameSceneFrameCount[NowGameScene]++;

	//���y�Đ�
	PlayMusic(PlayBGM);


	//�G�̏���
	{
		for (int i = 0; i < EnemyOneTimeMax; i++)
		{
			if (Enemy[i].DINOa.g.c.IsDraw == TRUE)
			{
				//�����蔻��Čv�Z
				Enemy[i].DINOa.g.c.Coll.left = Enemy[i].DINOa.g.c.Pos.x + Enemy[i].Ajust.left;
				Enemy[i].DINOa.g.c.Coll.top = Enemy[i].DINOa.g.c.Pos.y + Enemy[i].Ajust.top;
				Enemy[i].DINOa.g.c.Coll.right = Enemy[i].DINOa.g.c.Pos.x + Enemy[i].DINOa.g.c.Width - Enemy[i].Ajust.right;
				Enemy[i].DINOa.g.c.Coll.bottom = Enemy[i].DINOa.g.c.Pos.y + Enemy[i].DINOa.g.c.Height - Enemy[i].Ajust.bottom;
				
				//�G�̈ړ�
				Enemy[i].DINOa.g.c.Pos.x -= Enemy[i].XSpeed;

				//�G�����[�܂ōs������`�������
				if (Enemy[i].DINOa.g.c.Pos.x + Enemy[i].DINOa.g.c.Width <= 0)
				{
					Enemy[i].DINOa.g.c.IsDraw = FALSE;
				}

				//�G���z������X�R�A�A�b�v
				if (Enemy[i].IsJumpOver == FALSE && Enemy[i].DINOa.g.c.Pos.x < AnimMyTriceratops.DINOa.g.c.Pos.x)
				{
					score.ScorePoint += 100;
					Enemy[i].IsJumpOver = TRUE;
				}

				//�����ƓG������������Q�[���I�[�o�[
				if (AnimMyTriceratops.DINOa.g.c.Coll.left <= Enemy[i].DINOa.g.c.Coll.right
					&& AnimMyTriceratops.DINOa.g.c.Coll.top <= Enemy[i].DINOa.g.c.Coll.bottom
					&& AnimMyTriceratops.DINOa.g.c.Coll.right >= Enemy[i].DINOa.g.c.Coll.left
					&& AnimMyTriceratops.DINOa.g.c.Coll.bottom >= Enemy[i].DINOa.g.c.Coll.top)
				{
					//�Q�[���I�[�o�[�t���O
					IsGameOverFlg = TRUE;

					//�����A�j���[�V����
					AnimExpl.g.c.Pos.x = (AnimMyTriceratops.DINOa.g.c.Pos.x + Enemy[i].DINOa.g.c.Pos.x) / 2;
					AnimExpl.g.c.Pos.y = (AnimMyTriceratops.DINOa.g.c.Pos.y + Enemy[i].DINOa.g.c.Pos.y) / 2;

					//�����̃A�j���[�V������`�悵�Ȃ��悤�ɂ���
					AnimMyTriceratops.DINOa.g.c.IsDraw = FALSE;
					Enemy[i].DINOa.g.c.IsDraw = FALSE;

					//�W�����v���ʉ�
					PlayMusic(ExplSE);
					/*
					//���y��~
					PauseMusic(&PlayBGM);

					//�ō����_�X�V
					if (score.ScorePoint > score.ReadScore)
					{
						//�ō����_�����o��
						fopen_s(&score.Scorefp, ScoreDataPath, "w");
						fprintf_s(score.Scorefp, "%d", score.ScorePoint);
						fclose(score.Scorefp);
					}

					if (AnimExpl.a.IsAnimStartFlg == FALSE)
					{
						ChangeGameScene = ResultScene;
					}
					*/
				}
			}
		}

		//�G���o�Ă��鎞�Ԃ��v�Z
		EnemyCreateTime += fps.Deltatime;

		//�X�R�A�����ēG���o�Ă��鎞�Ԃ𒲐�
		if (score.ScorePoint < 2000) { EnemyCreateTimeMAX = 8.0f; }
		else if (score.ScorePoint < 5000) { EnemyCreateTimeMAX = 5.0f; }
		else if (score.ScorePoint < 7500) { EnemyCreateTimeMAX = 3.0f; }
		else if (score.ScorePoint < 10000) { EnemyCreateTimeMAX = 1.0f; }

		//�G�𐶐�
		if (EnemyCreateTime >= EnemyCreateTimeMAX)
		{
			//��x�ɏo��G�̐��͐�������
			for (int i = 0; i < EnemyOneTimeMax; i++)
			{
				if (Enemy[i].DINOa.g.c.IsDraw == FALSE)
				{
					//4�킩��I��
					switch (GetRand(3))
					{
					case 0:
						Enemy[i] = AnimEnemyTriceratops;
						break;
					case 1:
						Enemy[i] = AnimAnkylosaurus;
						break;
					case 2:
						Enemy[i] = AnimPachycephalosaurus;
						break;
					case 3:
						Enemy[i] = AnimSeismosaurus;
						break;
					default:
						break;
					}

					//���[�v�𔲂���
					break;
				}
			}

			//�G�������Ԃ����ɖ߂�
			EnemyCreateTime = 0.0f;
		}

	}

	//�����̏���
	{
		//�����蔻��Čv�Z
		{
			AnimMyTriceratops.DINOa.g.c.Coll.left = AnimMyTriceratops.DINOa.g.c.Pos.x + AnimMyTriceratops.Ajust.left;
			AnimMyTriceratops.DINOa.g.c.Coll.top = AnimMyTriceratops.DINOa.g.c.Pos.y + AnimMyTriceratops.Ajust.top;
			AnimMyTriceratops.DINOa.g.c.Coll.right = AnimMyTriceratops.DINOa.g.c.Pos.x + AnimMyTriceratops.DINOa.g.c.Width - AnimMyTriceratops.Ajust.right;
			AnimMyTriceratops.DINOa.g.c.Coll.bottom = AnimMyTriceratops.DINOa.g.c.Pos.y + AnimMyTriceratops.DINOa.g.c.Height - AnimMyTriceratops.Ajust.bottom;
		}

		//�X�y�[�X�L�[����ŃW�����v
		if (KeyPressFrame(KEY_INPUT_SPACE) > 0 && AnimMyTriceratops.IsJump == FALSE
			|| KeyPressFrame(KEY_INPUT_UP) > 0 && AnimMyTriceratops.IsJump == FALSE)
		{
			AnimMyTriceratops.IsJump = TRUE;
			AnimMyTriceratops.JumpBeforeY = AnimMyTriceratops.DINOa.g.c.Pos.y;	//�W�����v�O�̈ʒu������Ă���
			AnimMyTriceratops.JumpTime = 0;						//�W�����v���ԏ�����
			AnimMyTriceratops.DINOa.g.c.Pos.y--;					//������Ə�ɔ�΂�

			//�W�����v���ʉ�
			PlayMusic(JumpSE);
		}

		//�W�����v���̎�
		if (AnimMyTriceratops.IsJump == TRUE)
		{
			AnimMyTriceratops.JumpTime += JumpUpSpeed;
			AnimMyTriceratops.DINOa.g.c.Pos.y = AnimMyTriceratops.JumpBeforeY - sin(AnimMyTriceratops.JumpTime * DX_PI / 180.0f) * AnimMyTriceratops.JumpPower;

			//�n�ʂɂ�����
			if (AnimMyTriceratops.DINOa.g.c.Pos.y + AnimMyTriceratops.DINOa.g.c.Height >= Ground)
			{
				AnimMyTriceratops.DINOa.g.c.Pos.y = Ground - AnimMyTriceratops.DINOa.g.c.Height;
				AnimMyTriceratops.IsJump = FALSE;
			}
		}


		//�E�������Ă�����E�ɐi��
		if (KeyPressFrame(KEY_INPUT_RIGHT) > 0 || KeyPressFrame(KEY_INPUT_D) > 0)
		{
			AnimMyTriceratops.DINOa.g.c.Pos.x += AnimMyTriceratops.XSpeed;

			//�E��ʒ[�ȏ�ɂ͂����Ȃ�
			if (AnimMyTriceratops.DINOa.g.c.Pos.x + AnimMyTriceratops.DINOa.g.c.Width >= GameWidth)
			{
				AnimMyTriceratops.DINOa.g.c.Pos.x = GameWidth - AnimMyTriceratops.DINOa.g.c.Width;
			}
		}


		//�����������獶�ɐi��
		if (KeyPressFrame(KEY_INPUT_LEFT) > 0 || KeyPressFrame(KEY_INPUT_A) > 0)
		{
			AnimMyTriceratops.DINOa.g.c.Pos.x -= AnimMyTriceratops.XSpeed;

			//����ʒ[�ȏ�ɂ͂����Ȃ�
			if (AnimMyTriceratops.DINOa.g.c.Pos.x <= 0)
			{
				AnimMyTriceratops.DINOa.g.c.Pos.x = 0;
			}
		}


		//�����������������
		if (KeyPressFrame(KEY_INPUT_DOWN) > 0 && IsAvoidFlg == FALSE && StiffnessTime >= 5.0f
			|| KeyPressFrame(KEY_INPUT_S) > 0 && IsAvoidFlg == FALSE && StiffnessTime >= 5.0f)
		{
			//������t���O
			IsAvoidFlg = TRUE;

			//��������ʉ�
			PlayMusic(AvoidSE);

			//�d������
			StiffnessTime = 0;

			//�A�j���[�V������������
			AnimationStart(
				&AnimAvoid,			//�ǂ̃A�j���[�V�������Đ�����H
				900,				//�A�j���[�V�����p������
				300);				//100�~���b�Ԋu�Ŏ��̃R�}��

			AnimAvoid.g.c.Pos.x = AnimMyTriceratops.DINOa.g.c.Pos.x;
			AnimAvoid.g.c.Pos.y = AnimMyTriceratops.DINOa.g.c.Pos.y - 20;

			AnimMyTriceratops.DINOa.g.c.IsDraw = FALSE;
		}
		
		//������A�j���[�V������
		if (AnimAvoid.a.IsAnimStartFlg == TRUE)
		{
			//�L�����̓����蔻����Ȃ���
			AnimMyTriceratops.DINOa.g.c.Coll.left = 0;
			AnimMyTriceratops.DINOa.g.c.Coll.top = 0;
			AnimMyTriceratops.DINOa.g.c.Coll.right = 0;
			AnimMyTriceratops.DINOa.g.c.Coll.bottom = 0;
		}

		//������A�j���[�V�������I�������
		if (AnimAvoid.a.IsAnimStartFlg == FALSE && IsAvoidFlg == TRUE)
		{
			IsAvoidFlg = FALSE;
			AnimMyTriceratops.DINOa.g.c.IsDraw = TRUE;
		}

		//������d������
		StiffnessTime += fps.Deltatime;
	}


	if (AnimExpl.a.IsAnimStartFlg == FALSE)
	{
		//���y��~
		PauseMusic(&PlayBGM);

		//�ō����_�X�V
		if (score.ScorePoint > score.ReadScore)
		{
			//�ō����_�����o��
			fopen_s(&score.Scorefp, ScoreDataPath, "w");
			fprintf_s(score.Scorefp, "%d", score.ScorePoint);
			fclose(score.Scorefp);
		}

		ChangeGameScene = ResultScene;
	}

	return;
}
//�v���C�`��
VOID PlayDraw(VOID)
{
	//�w�i�ړ�
	TitleBackImage.c.Pos.x -= 1;	//�w�i
	BackImageTurn.c.Pos.x -= 1;		//�w�i���]

	//�w�i�̈ʒu�����E�ɖ߂�
	if (TitleBackImage.c.Pos.x + TitleBackImage.c.Width <= 0) { TitleBackImage.c.Pos.x = BackImageTurn.c.Pos.x + BackImageTurn.c.Width; }
	if (BackImageTurn.c.Pos.x + BackImageTurn.c.Width <= 0) { BackImageTurn.c.Pos.x = TitleBackImage.c.Pos.x + TitleBackImage.c.Width; }

	//�����ړ�
	for (int i = 0; i < BackGrassNum; i++)
	{
		BackGrass[i].c.Pos.x -= 10;
	}

	//�����̈ʒu���E�ɖ߂�
	for (int i = 0; i < BackGrassNum; i++)
	{
		if (BackGrass[i].c.Pos.x + BackGrass[i].c.Width <= 0)
		{
			if (i == 0)
			{
				//0�̎������͓���
				BackGrass[i].c.Pos.x = BackGrass[BackGrassNum - 1].c.Pos.x + BackGrass[BackGrassNum - 1].c.Width;
			}
			else
			{
				//����ȊO�̎��͈���̉摜�̉E�ɕ��ג���
				BackGrass[i].c.Pos.x = BackGrass[i - 1].c.Pos.x + BackGrass[i - 1].c.Width;
			}
		}
	}

	//�w�i�`��
	DrawGraphic(&TitleBackImage);	//�w�i�摜��`��
	DrawTurnGraph(BackImageTurn.c.Pos.x, BackImageTurn.c.Pos.y, BackImageTurn.Handle, TRUE);	//�w�i���]

	//�����`��
	for (int i = 0; i < BackGrassNum; i++)
	{
		//�Q�[����ʂɉf�肱�ވʒu�Ȃ�
		if (BackGrass[i].c.Pos.x < GameWidth)
		{
			DrawGraphic(&BackGrass[i]);
		}
	}

	//�G�`��
	{
		for (int i = 0; i < EnemyOneTimeMax; i++)
		{
			DrawAnimation(&Enemy[i].DINOa);
		}
	}

	//�����`��
	{
		DrawAnimation(&AnimMyTriceratops.DINOa);
	}

	//�����ƓG������������Q�[���I�[�o�[
	if (IsGameOverFlg == TRUE)
	{
		DrawAnimation(&AnimExpl);		//�����A�j��(1��̂�)
	}

	//�����邱�Ƃ��\���`��
	if (StiffnessTime >= 5.0f)
	{
		DrawFormatStringToHandleAlign(
			GetGameWindowCenter().x, 150, Align_AllCenter, Color_skyblue,
			fontJiyu100pt.Handle,	//���̃t�H���g�f�[�^���g�p
			"%s", "�����͂Ŕ������"
		);
	}
	else
	{
		DrawFormatStringToHandleAlign(
			GetGameWindowCenter().x, 150, Align_AllCenter, Color_pink,
			fontJiyu100pt.Handle,	//���̃t�H���g�f�[�^���g�p
			"%s%.1f", "�N�[���^�C��:",5.0f - StiffnessTime
		);
	}

	//������
	if (IsAvoidFlg == TRUE)
	{
		DrawAnimation(&AnimAvoid);		//������A�j��(1��̂�)
	}

	//�X�R�A��`��
	DrawFormatStringToHandleAlign(
		GetGameWindowCenter().x, 50, Align_AllCenter, Color_black,
		fontJiyu100pt.Handle,	//���̃t�H���g�f�[�^���g�p
		"%s%05d", "SCORE:", score.ScorePoint
	);


	if (GameDebug == TRUE)
	{
		//�V�[�����\��
		DrawFormatStringToHandle(
			GameWidth - 200, 0, Color_white,
			fontDefault.Handle,	//���̃t�H���g�f�[�^���g�p
			"%s%s", GameSceneName[NowGameScene], "�`�扻"
		);

		//�n�ʂ�`��
		DrawLine(0, Ground, GameWidth, Ground, GetColor(128, 0, 0), 5);

		//�}�E�X�|�C���^��`��
		DrawFormatStringToHandleAlign(
			GetPointMouse().x, GetPointMouse().y, Align_AllCenter, Color_black,
			fontJiyu100pt.Handle,	//���̃t�H���g�f�[�^���g�p
			"Mouse:x%4d/Y%4d", GetPointMouse().x, GetPointMouse().y
		);
	}


	return;
}

//���U���g������
VOID ResultInit(VOID)
{
	//�摜�G�t�F�N�g�J�n
	GraphicFxStart(
		&GameoverLogo,		//�ǂ̉摜�ɃG�t�F�N�g��������H
		GraFxFadeInOut,		//�ǂ�ȃG�t�F�N�g��������H
		GraFxInfinity,		//�G�t�F�N�g�����p��
		1000);				//1000�~���b�Ԋu

	GraphicFxStart(
		&NewrecordLogo,		//�ǂ̉摜�ɃG�t�F�N�g��������H
		GraFxFadeInOut,		//�ǂ�ȃG�t�F�N�g��������H
		GraFxInfinity,		//�G�t�F�N�g�����p��
		1000);				//1000�~���b�Ԋu

	//TitleBackImage.c.Pos.x = 0;		//�w�i

	if (GameDebug == TRUE)
	{
		//�V�[�����\��
		DrawFormatStringToHandle(
			GameWidth - 200, 0, Color_white,
			fontDefault.Handle,	//���̃t�H���g�f�[�^���g�p
			"%s%s", GameSceneName[NowGameScene], "������"
		);

		//�K�؂ȃV�[���̏��������ł��Ă��邩�e�X�g
		//ScreenFlip();
		//WaitTimer(1000);
	}

	//�V�[����؂�ւ����t���[������������
	GameSceneFrameCount[ChangeGameScene] = 0;

	return;
}
//���U���g�Ǘ�
VOID ResultCtrl(VOID)
{
	ResultProc();	//���������Ă���
	ResultDraw();	//�`�悷��!

	return;
}
//���U���g���� 
VOID ResultProc(VOID)
{
	//�V�[���؂�ւ���̃t���[�������J�E���g�A�b�v
	GameSceneFrameCount[NowGameScene]++;

	//���y�Đ�
	PlayMusic(ResultBGM);

	if (KeyClick(KEY_INPUT_SPACE) == TRUE									//�X�y�[�X�L�[���������Ƃ�
		&& GameSceneFrameCount[NowGameScene] >= GameSceneChangeFrame)		//���A�؂�ւ��\�ȃt���[�����𒴂�����
	{
		//���ʉ�
		PlayMusic(ButtonClickSE);

		//���y��~
		PauseMusic(&ResultBGM);

		//�V�[���؂�ւ�
		ChangeGameScene = TitleScene;

		//�����ɐ؂�ւ���
		return;
	}

	return;
}
//���U���g�`��
extern VOID ResultDraw(VOID)
{	
	//�����������قǉ��ɏ������

	DrawGraphic(&TitleBackImage);	//�w�i�摜��`��
	DrawTurnGraph(BackImageTurn.c.Pos.x, BackImageTurn.c.Pos.y, BackImageTurn.Handle, TRUE);	//�w�i���]��`��

	DrawGraphic(&GameoverLogo);		//�Q�[���I�[�o�[���S��`��
	DrawFormatStringToHandleAlign(
		GetGameWindowCenter().x, 50, Align_AllCenter, Color_black,
		fontJiyu100pt.Handle,	//���̃t�H���g�f�[�^���g�p
		"%s%05d", "SCORE:", score.ScorePoint
	);

	//�ō����_�Ȃ�
	if (score.ScorePoint > score.ReadScore)
	{
		DrawGraphic(&NewrecordLogo);	//�j���[���R�[�h���S��`��
	}


	if (GameDebug == TRUE)
	{
		//�V�[�����\��
		DrawFormatStringToHandle(
			GameWidth - 200, 0, Color_white,
			fontDefault.Handle,	//���̃t�H���g�f�[�^���g�p
			"%s%s", GameSceneName[NowGameScene], "�`�扻"
		);
	}


	return;
}