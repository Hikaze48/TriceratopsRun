//�Q�[�������̃w�b�_�t�@�C��
#pragma once

//�w�b�_�t�@�C���ǂݍ���
#include "DxLib.h"

//�}�N����`
#define GameWidth	1280			//��ʂ̕�
#define GameHeight	720				//��ʂ̍���
#define GameColor	32				//��ʂ̐F
#define GameTitle	"Tricera Run"		//��ʃ^�C�g��
#define GameVsync	TRUE			//V-Sync���g���Ȃ�TRUE
#define GameIcon	555				// ��ʃA�C�R��

#define GameDebug	FALSE			//�f�o�b�O���[�h

#define GameSceneCount		3		//�Q�[���V�[���̐�
#define GameSceneNameMax	20		//�Q�[���V�[�����̕�����MAX

#define GameSceneChangeFrame 60		//�Q�[���V�[���̐؂�ւ����\�ɂ���t���[����

//�X�R�A�̃f�[�^�p�X
#define ScoreDataPath	".\\score.txt"

//�n��
#define Ground		700				//�n�ʂ̍���
#define JumpValue	350				//�W�����v��(����500)
#define JumpUpSpeed 3				//�W�����v�̏オ��X�s�[�h(����1)

//�^�C�g���ő҂���
#define TitleWait	1.0f			//�b��
#define ResultWait	3.0f			//�b��

//�G
#define EnemyOneTimeMax 7			//�G�̈�x�ɏo�Ă������(����4)

//�F�n�̖��O(���F�厫�T�l���Q�l��https://www.colordic.org/)

#define Color_black			GetColor(  0,   0,   0)
#define Color_white			GetColor(255, 255, 255)
#define Color_skyblue		GetColor(135, 206, 235)
#define Color_tomato		GetColor(255, 99, 71)
#define Color_lightyellow	GetColor(255, 255, 224)
#define Color_lawngreen		GetColor(124, 252, 0)
#define Color_pink			GetColor(255, 192, 203)
#define Color_yellow		GetColor(255, 255, 0)

//�񋓌^

//�Q�[���V�[��
enum GameScene {
	TitleScene,		//�^�C�g���V�[��
	PlayScene,		//�v���C�V�[��
	ResultScene	//���U���g�V�[��
};

typedef struct _SCORE
{
	int ScorePoint = 0;			//�Q�[�����̃X�R�A
	int ReadScore = 0;		//�ǂݍ��񂾃X�R�A
	FILE* Scorefp = NULL;	//�X�R�A�f�[�^�̃t�@�C���|�C���^
}SCORE;

//�O���̃O���[�o���ϐ�
extern enum GameScene NowGameScene;		//���݂̃Q�[���V�[��
extern enum GameScene ChangeGameScene;	//�؂�ւ��Q�[���V�[��
extern SCORE score;

//�O���̃v���g�^�C�v�錾

extern VOID GameInit(VOID);			//�Q�[����ʏ�����
extern HWND GetGameHandle(VOID);	//�Q�[����ʂ̃n���h�����擾
extern RECT GetGameWindow(VOID);	//�Q�[����ʂ̋�`���擾

extern POINT GetGameWindowCenter(VOID);	//�Q�[����ʂ̏㉺���E�̒������W���擾

extern VOID TitleInit(VOID);	//�^�C�g��������
extern VOID TitleCtrl(VOID);	//�^�C�g���Ǘ�
extern VOID TitleProc(VOID);	//�^�C�g������
extern VOID TitleDraw(VOID);	//�^�C�g���`��

extern VOID PlayInit(VOID);		//�v���C������
extern VOID PlayCtrl(VOID);		//�v���C�Ǘ�
extern VOID PlayProc(VOID);		//�v���C����
extern VOID PlayDraw(VOID);		//�v���C�`��

extern VOID ResultInit(VOID);	//���U���g������
extern VOID ResultCtrl(VOID);	//���U���g�Ǘ�
extern VOID ResultProc(VOID);	//���U���g����
extern VOID ResultDraw(VOID);	//���U���g�`��
