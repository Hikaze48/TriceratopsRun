//�A�j���[�V���������̃w�b�_�t�@�C��
#pragma once

//�w�b�_�t�@�C���ǂݍ���
#include "DxLib.h"
#include "graphic.h"
#include "game.h"

//�G���[
#define AnimationLoadErrCap		"���ǂݍ��߂܂���ł���"
#define AnimationLoadErrTitle		"�A�j���[�V�����ǂݍ��݃G���["

//������̒���
#define AnimationPathStrMax	256
#define AnimationErrStrMax	512

//�A�j���[�V�����t�@�C���̃p�X
#define GraphicPathTitleAnimExpl	".\\graphic\\explosion.png"
#define AnimExplDivX				5								//�����A�j���̉�������
#define AnimExplDivY				1								//�����A�j���̏c������

#define GraphicPathTitleAnimCoin	".\\graphic\\coin.png"
#define AnimCoinDivX				14								//�R�C���A�j���̉�������
#define AnimCoinDivY				1								//�R�C���A�j���̏c������

#define GraphicPathTitleAnimSlash	".\\graphic\\slash.png"
#define AnimSlashDivX				5								//�a���A�j���̉�������
#define AnimSlashDivY				1								//�a���A�j���̏c������

#define GraphicPathAnimAvoid		".\\graphic\\My_Big_kyoryu1_avoid.png"
#define AnimAvoidDivX				1								//������A�j���̉�������
#define AnimAvoidDivY				3								//������A�j���̏c������

#define GraphicPathAnimMyTriceratops		".\\graphic\\My_Big_kyoryu1.png"
#define AnimMyTriceratopsDivX			3							//�����̃g���P���g�v�X�̉�������
#define AnimMyTriceratopsDivY			1							//�����̃g���P���g�v�X�̏c������

#define GraphicPathAnimEnemyTriceratops		".\\graphic\\Enemy_Big_kyoryu1.png"
#define AnimEnemyTriceratopsDivX			3						//�G�̃g���P���g�v�X�̉�������
#define AnimEnemyTriceratopsDivY			1						//�G�̃g���P���g�v�X�̏c������

#define GraphicPathAnimAnkylosaurus		".\\graphic\\Enemy_Big_kyoryu2.png"
#define AnimAnkylosaurusDivX		3								//�G�̃A���L���T�E���X�̉�������
#define AnimAnkylosaurusDivY		1								//�G�̃A���L���T�E���X�̏c������

#define GraphicPathAnimPachycephalosaurus		".\\graphic\\Enemy_Big_kyoryu3.png"
#define AnimPachycephalosaurusDivX			3						//�G�̃p�L�P�t�@���T�E���X�̉�������
#define AnimPachycephalosaurusDivY			1						//�G�̃p�L�P�t�@���T�E���X�̏c������

#define GraphicPathAnimSeismosaurus		".\\graphic\\Enemy_Big_kyoryu4.png"
#define AnimSeismosaurusDivX		3								//�G�̃Z�C�X���T�E���X�̉�������
#define AnimSeismosaurusDivY		1								//�G�̃Z�C�X���T�E���X�̏c������

//�A�j���[�V���������p��(�����Ȃ̂Œʏ�͂��肦�Ȃ�����)
#define AnimationInfinity	-99999

//�A�j���[�V����1��̂�(�����Ȃ̂Œʏ�͂��肦�Ȃ�����)
#define AnimationOnce		-11111

//�A�j���[�V�����\���̂̃R�A����
typedef struct _AnimationCore
{
	int NowHandleIndex = -1;		//���݂̃n���h���̗v�f��

	int DivX = 0;					//�摜�̉�������
	int DivY = 0;					//�摜�̏c������

	int FrameCnt = 0;				//�A�j���[�V�����̃R�A����
	int FrameMax = 0;				//�A�j���[�V�����̃R�A����MAX

	int FrameByFrameCnt = 0;		//�A�j���̃R�A���莞��
	int FrameByFrameMax = 0;		//�A�j���̃R�A���莞��MAX

	BOOL IsAnimStartFlg = FALSE;	//�A�j���[�V�����J�n�t���O
}AnimationCore;

//�A�j���[�V�����\����
typedef struct _Animation
{
	Graphic			g;	//�摜
	AnimationCore	a;	//�A�j���[�V�����R�A
	int* Handle;		//�n���h��(�������𓮓I�m��)
}Animation;

//����
typedef struct _DINO
{
	float JumpBeforeY;			//�W�����v�O�̏c�̈ʒu
	int JumpTime;				//�W�����v����

	double XSpeed;				//���ړ��̑���

	RECT Ajust;					//�����蔻��i�����j
	double JumpPower;			//�W�����v�́i���a�j
	BOOL IsJump = FALSE;		//�W�����v���H
	BOOL IsJumpOver = FALSE;	//�W�����v�Ŕ�щz�������H
	Animation DINOa;			//�A�j���[�V����
}DINO;

//�O���O���[�o���ϐ�
extern Animation AnimExpl;						//�����A�j���[�V����
extern Animation AnimCoin;						//�R�C���A�j���[�V����
extern Animation AnimSlash;						//�a���A�j���[�V����
extern Animation AnimAvoid;						//������A�j���[�V����

extern DINO AnimMyTriceratops;					//�����̃g���P���g�v�X�A�j���[�V����
extern DINO AnimEnemyTriceratops;				//�G�̃g���P���g�v�X�A�j���[�V����
extern DINO AnimAnkylosaurus;					//�A���L���T�E���X�A�j���[�V����
extern DINO AnimPachycephalosaurus;				//�p�L�P�t�@���T�E���X�A�j���[�V����
extern DINO AnimSeismosaurus;					//�Z�C�X���T�E���X�A�j���[�V����

//extern DINO My;									//����
extern DINO Enemy[EnemyOneTimeMax];				//�G

//�O���v���g�^�C�v�錾
extern BOOL Animation_Init(VOID);								//�ǂݍ��݁E�n���h������
extern VOID Animation_End(VOID);								//��n��
extern VOID AnimationLoadErrMessage(const char* path);			//�ǂݍ��݃G���[���b�Z�[�W


extern Animation LoadAnimation(Graphic graphic, int XNum, int YNum);	//�A�j���[�V�����ǂݍ���
extern VOID DrawAnimation(Animation* animation);						//�`��
extern VOID DeleteAnimation(Animation animation);						//���

extern VOID AnimationStart(Animation* animation, int MillTime, int MillInterval);	//�A�j���[�V�����J�n