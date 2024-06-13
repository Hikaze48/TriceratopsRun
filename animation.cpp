//�A�j���[�V���������̃\�[�X�t�@�C��

//�w�b�_�t�@�C���ǂݍ���
#include "animation.h"

Animation AnimExpl;						//�����A�j���[�V����
Animation AnimCoin;						//�R�C���A�j���[�V����
Animation AnimSlash;					//�a���A�j���[�V����
Animation AnimAvoid;					//������A�j���[�V����

DINO AnimMyTriceratops;				//�����̃g���P���g�v�X�A�j���[�V����
DINO AnimEnemyTriceratops;			//�G�̃g���P���g�v�X�A�j���[�V����
DINO AnimAnkylosaurus;				//�A���L���T�E���X�A�j���[�V����
DINO AnimPachycephalosaurus;		//�p�L�P�t�@���T�E���X�A�j���[�V����
DINO AnimSeismosaurus;				//�Z�C�X���T�E���X�A�j���[�V����
//DINO My;							//�����L����
DINO Enemy[EnemyOneTimeMax];		//�G�L����

//�ǂݍ��݁E�n���h������
BOOL Animation_Init(VOID)
{
	//�����A�j���[�V����
	AnimExpl = LoadAnimation(
		LoadGraphic(					//�A�j���[�V�����摜�ǂݍ���
			GraphicPathTitleAnimExpl,	//�A�j���[�V�����摜�p�X
			GetPoint(0, 0),		//�E�ォ��
			GetRect(0, 0, 0, 0),		//�����蔻��̗]���͖���
			GraAlignTopL),
		AnimExplDivX,					//�A�j���[�V������������
		AnimExplDivY					//�A�j���[�V�����c������
	);	if (AnimExpl.Handle[0] == -1) { return FALSE; }

	//�R�C���A�j���[�V����
	AnimCoin = LoadAnimation(
		LoadGraphic(					//�A�j���[�V�����摜�ǂݍ���
			GraphicPathTitleAnimCoin,	//�A�j���[�V�����摜�p�X
			GetPoint(0, 0),				//���ォ��
			GetRect(0, 0, 0, 0),		//�����蔻��̗]���͖���
			GraAlignTopL),
		AnimCoinDivX,					//�A�j���[�V������������
		AnimCoinDivY					//�A�j���[�V�����c������
	);	if (AnimCoin.Handle[0] == -1) { return FALSE; }

	//�a���A�j���[�V����
	AnimSlash = LoadAnimation(
		LoadGraphic(					//�A�j���[�V�����摜�ǂݍ���
			GraphicPathTitleAnimSlash,	//�A�j���[�V�����摜�p�X
			GetPoint(GameWidth, GameHeight),	//�E������
			GetRect(0, 0, 0, 0),		//�����蔻��̗]���͖���
			GraAlignBottomR),
		AnimSlashDivX,					//�A�j���[�V������������
		AnimSlashDivY					//�A�j���[�V�����c������
	);	if (AnimSlash.Handle[0] == -1) { return FALSE; }

	//������A�j���[�V����
	AnimAvoid = LoadAnimation(
		LoadGraphic(					//�A�j���[�V�����摜�ǂݍ���
			GraphicPathAnimAvoid,		//�A�j���[�V�����摜�p�X
			GetPoint(0, 0),				//���ォ��
			GetRect(0, 0, 0, 0),		//�����蔻��̗]���͖���
			GraAlignTopL),
		AnimAvoidDivX,					//�A�j���[�V������������
		AnimAvoidDivY					//�A�j���[�V�����c������
	);	if (AnimAvoid.Handle[0] == -1) { return FALSE; }

	//�����̃g���P���g�v�X�A�j���[�V����
	AnimMyTriceratops.DINOa = LoadAnimation(
		LoadGraphic(						//�A�j���[�V�����摜�ǂݍ���
			GraphicPathAnimMyTriceratops,	//�A�j���[�V�����摜�p�X
			GetPoint(0, 0),					//���ォ��
			GetRect(0, 0, 0, 0),			//�����蔻��̗]���͖���
			GraAlignTopL),
		AnimMyTriceratopsDivX,				//�A�j���[�V������������
		AnimMyTriceratopsDivY				//�A�j���[�V�����c������
	);	if (AnimMyTriceratops.DINOa.Handle[0] == -1) { return FALSE; }

	//�G�̃g���P���g�v�X�A�j���[�V����
	AnimEnemyTriceratops.DINOa = LoadAnimation(
		LoadGraphic(							//�A�j���[�V�����摜�ǂݍ���
			GraphicPathAnimEnemyTriceratops,	//�A�j���[�V�����摜�p�X
			GetPoint(0, 0),						//���ォ��
			GetRect(0, 0, 0, 0),				//�����蔻��̗]���͖���
			GraAlignTopL),
		AnimEnemyTriceratopsDivX,				//�A�j���[�V������������
		AnimEnemyTriceratopsDivY				//�A�j���[�V�����c������
	);	if (AnimEnemyTriceratops.DINOa.Handle[0] == -1) { return FALSE; }

	//�A���L���T�E���X�A�j���[�V����
	AnimAnkylosaurus.DINOa = LoadAnimation(
		LoadGraphic(							//�A�j���[�V�����摜�ǂݍ���
			GraphicPathAnimAnkylosaurus,		//�A�j���[�V�����摜�p�X
			GetPoint(0, 0),						//���ォ��
			GetRect(0, 0, 0, 0),				//�����蔻��̗]���͖���
			GraAlignTopL),
		AnimAnkylosaurusDivX,					//�A�j���[�V������������
		AnimAnkylosaurusDivY					//�A�j���[�V�����c������
	);	if (AnimAnkylosaurus.DINOa.Handle[0] == -1) { return FALSE; }

	//�p�L�P�t�@���T�E���X�A�j���[�V����
	AnimPachycephalosaurus.DINOa = LoadAnimation(
		LoadGraphic(							//�A�j���[�V�����摜�ǂݍ���
			GraphicPathAnimPachycephalosaurus,	//�A�j���[�V�����摜�p�X
			GetPoint(0, 0),						//���ォ��
			GetRect(0, 0, 0, 0),				//�����蔻��̗]���͖���
			GraAlignTopL),
		AnimPachycephalosaurusDivX,				//�A�j���[�V������������
		AnimPachycephalosaurusDivY				//�A�j���[�V�����c������
	);	if (AnimPachycephalosaurus.DINOa.Handle[0] == -1) { return FALSE; }


	//�Z�C�X���T�E���X�A�j���[�V����
	AnimSeismosaurus.DINOa = LoadAnimation(
		LoadGraphic(							//�A�j���[�V�����摜�ǂݍ���
			GraphicPathAnimSeismosaurus,		//�A�j���[�V�����摜�p�X
			GetPoint(0, 0),						//���ォ��
			GetRect(0, 0, 0, 0),				//�����蔻��̗]���͖���
			GraAlignTopL),
		AnimSeismosaurusDivX,					//�A�j���[�V������������
		AnimSeismosaurusDivY					//�A�j���[�V�����c������
	);	if (AnimSeismosaurus.DINOa.Handle[0] == -1) { return FALSE; }


	return TRUE;
}

//��n��
VOID Animation_End(VOID)
{
	DeleteAnimation(AnimExpl);
	DeleteAnimation(AnimCoin);
	DeleteAnimation(AnimSlash);
	DeleteAnimation(AnimAvoid);
	DeleteAnimation(AnimMyTriceratops.DINOa);
	DeleteAnimation(AnimEnemyTriceratops.DINOa);
	DeleteAnimation(AnimAnkylosaurus.DINOa);
	DeleteAnimation(AnimPachycephalosaurus.DINOa);
	DeleteAnimation(AnimSeismosaurus.DINOa);

	return;
}

//�ǂݍ��݃G���[���b�Z�[�W
VOID AnimationLoadErrMessage(const char* path)
{
	//�G���[�p������
	char ErrStr[AnimationPathStrMax];

	//�G���[�p������̓��e����ɂ���
	for (int i = 0; i < AnimationPathStrMax; i++) { ErrStr[i] = '\0'; }

	//�G���[���e��A�����Đ���
	sprintf_s(ErrStr, sizeof(ErrStr), "%s%s", path, AnimationLoadErrCap);

	//�p�X���Ԉ���Ă���ȂǂŃC���X�g�[���ł��Ȃ��ꍇ�̓G���[
	MessageBox(
		GetMainWindowHandle(),		//�E�B���h�E�n���h��
		ErrStr,						//�G���[���e
		AnimationLoadErrTitle,		//�G���[�^�C�g��
		MB_OK);						//OK�{�^���̂�

	return;
}

//�A�j���[�V�����ǂݍ���
Animation LoadAnimation(Graphic graphic, int XNum, int YNum)
{
	Animation animation;

	//�ǂݍ��񂾉摜�̏��������p��
	animation.g = graphic;

	//�摜�̕�������ݒ�
	animation.a.DivX = XNum;
	animation.a.DivY = YNum;

	//�摜�̕��ƍ������Čv�Z
	animation.g.c.Width = animation.g.c.Width / XNum;
	animation.g.c.Height = animation.g.c.Height / YNum;

	//�����蔻����Čv�Z
	ReMakeCollRect(&animation.g);

	//�A�j���[�V�����̃n���h���z��𓮓I�m��
	animation.Handle
		= (int*)				//int�^�̃|�C���^�Ɍ^�ϊ�
		calloc(					//�������𓮓I�m�ۂ��Ēl���[���ŏ�����
			XNum * YNum,		//�m�ۂ���v�f�̌�
			sizeof(int)			//�m�ۂ���v�f�̃f�[�^�^
		);

	//�A�j���[�V�����𕪊����ă������ɓǂݍ���
	LoadDivGraph(
		graphic.c.Path,			//�A�j���[�V�����̃p�X
		(XNum * YNum),			//��������
		XNum, YNum,				//��(��)�������A-(�c)������
		animation.g.c.Width,	//��������1���̕�
		animation.g.c.Height,	//��������1���̍���
		animation.Handle		//�A�������n���h���z��̐擪
	);

	//�ǂݍ��݃G���[
	if (animation.Handle == NULL || animation.Handle[0] == -1)
	{
		AnimationLoadErrMessage(graphic.c.Path);
	}

	//�������ɓǂݍ��񂾉摜�̓T�C�Y��m�肽�������Ȃ̂ŗp�ς�
	//��graphic��handle�͏��������
	DeleteGraphic(graphic);

	//�n���h���̗v�f����������
	animation.a.NowHandleIndex = 0;

	//�ŏ��̃A�j���[�V�����̗v�f�����Z�b�g
	animation.g.Handle = animation.Handle[animation.a.NowHandleIndex];

	return animation;
}

//�`��
VOID DrawAnimation(Animation* animation)
{
	//�摜�`��
	DrawGraphic(&animation->g);

	//�A�j���[�V�������Ȃ�R�}��i�߂�
	if (animation->a.IsAnimStartFlg == TRUE)
	{
		if (animation->a.FrameByFrameCnt < animation->a.FrameByFrameMax)
		{
			animation->a.FrameByFrameCnt++;
		}
		else
		{
			//�R�}��i�߂Ă��镔��(-1�����Ȃ��Ɣz��𒴂���)
			if (animation->a.NowHandleIndex < animation->a.DivX * animation->a.DivY - 1)
			{
				animation->a.NowHandleIndex++;
			}
			else
			{
				animation->a.NowHandleIndex = 0;
			}

			//�A�j���[�V�����̗v�f�����Z�b�g
			animation->g.Handle = animation->Handle[animation->a.NowHandleIndex];

			//�R�}���菉����
			animation->a.FrameByFrameCnt = 0;
		}

		//�A�j���[�V�������ԃJ�E���g�A�b�v
		animation->a.FrameCnt++;

		//�A�j���[�V�����������p���ł͂Ȃ��Ƃ�
		if (animation->a.FrameMax != AnimationInfinity)
		{
			//�A�j���[�V������1��݂̂Ȃ�A�j���[�V�������Ԃ𖳎�
			if (animation->a.FrameMax != AnimationOnce)
			{
				//�A�j���[�V�������Ԃ��I���Ȃ�΃A�j���[�V�����I��
				if (animation->a.FrameCnt > animation->a.FrameMax)
				{
					animation->a.IsAnimStartFlg = FALSE;		//�A�j���[�V�����J�n�t���OOFF
					animation->g.c.IsDraw = FALSE;				//�A�j���[�V�����`��t���OOFF
				}
			}

			//�A�j���[�V�����̋�̍Ō�Ȃ�΃A�j���[�V�����I��(-1�����Ȃ��Ɣz��𒴂���)
			if (animation->a.NowHandleIndex >= animation->a.DivX * animation->a.DivY - 1)
			{
				animation->a.IsAnimStartFlg = FALSE;	//�A�j���[�V�����J�n�t���OOFF
				animation->g.c.IsDraw = FALSE;	//�A�j���[�V�����`��t���OOFF
			}
		}
	}

	return;
}

//���
VOID DeleteAnimation(Animation animation)
{
	//����ɓǂݍ��݂��ł��Ă����
	if (animation.Handle != NULL && animation.Handle[0] != -1)
	{
		//������������
		for (int i = 0; i < animation.a.DivX * animation.a.DivY; i++)
		{
			DeleteGraph(animation.Handle[i]);
		}

		//���I�m�ۂ��������������
		free(animation.Handle);
	}

	//2��ȏ��free��h���v���O�����̃N���b�V���h�~
	animation.Handle = NULL;

	return;
}

//�A�j���[�V�����J�n
VOID AnimationStart(Animation* animation, int MillTime, int MillInterval)
{
	//�A�j���[�V�����̕b����������
	animation->a.FrameCnt = 0;

	//�A�j���[�V�����̌p�����Ԃ��v�Z
	if (MillTime == AnimationInfinity)
	{
		//�����A�j���[�V�����������p���Ȃ�A���ۂ�MAX���Ԃ��v�Z�����Ȃ�
		animation->a.FrameMax = AnimationInfinity;
	}
	else if (MillTime == AnimationOnce)
	{
		//�����A�j���[�V������1��݂̂Ȃ�A���ۂ�MAX���Ԃ��v�Z�����Ȃ�
		animation->a.FrameMax = AnimationOnce;
	}
	else
	{
		animation->a.FrameMax = (MillTime / 1000.0f) * GameFPS;
	}

	//�A�j���[�V�����̊Ԋu��������
	animation->a.FrameByFrameCnt = 0;
	animation->a.FrameByFrameMax = (MillInterval / 1000.0f) * GameFPS;

	//�n���h���̗v�f����������
	animation->a.NowHandleIndex = 0;

	//�ŏ��̃A�j���[�V�����̗v�f�����Z�b�g
	animation->g.Handle = animation->Handle[animation->a.NowHandleIndex];

	//�A�j���[�V�����J�n�t���OON
	animation->a.IsAnimStartFlg = TRUE;

	//�A�j���[�V�����`��t���OON
	animation->g.c.IsDraw = TRUE;

	return;
}