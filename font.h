//�t�H���g�̃w�b�_�t�@�C��
#pragma once

//�w�b�_�t�@�C���ǂݍ���
#include "DxLib.h"

//�t�H���g�̃p�X�Ɩ��O

//�O���t�H���g
#define FontPathJiyu	".\\FONT\\Jiyucho.ttf"
#define FontNameJiyu	"���䂤���傤�t�H���g"

//�����t�H���g
#define FontNameMSMincho	"�l�r ����"

//�f�t�H���g�̃t�H���g
#define FontDefName	FontNameMSMincho	//�t�H���g��
#define FontDefSize	20					//�����T�C�Y
#define FontDefThinck 1					//�����̑���
#define FontDefType	DX_FONTTYPE_ANTIALIASING_8X8	//�A���`�G�C���A�X

//������̒���
#define FontNameStrMax		256
#define FontErrStrMax		512

//�G���[
#define FontInstallErrCap	"���C���X�g�[���ł��܂���"
#define FontInstallErrTitle	"�t�H���g�C���X�g�[���G���["

#define FontCreateErrCap	"���쐬�ł��܂���"
#define FontCreateErrTitle	"�t�H���g�쐬�G���["

//��������MAX������
#define FontAlignStrMax		512

//�񋓌^
enum Font_Align
{
	Align_Left,		//������
	Align_Center,	//��������
	Align_Right,	//�E����
	Align_AllCenter	//�㉺�����E����������
};

//�\����
typedef struct _AddFont
{
	char FontPath[FontNameStrMax];
	char FontName[FontNameStrMax];
	BOOL CanInstall = FALSE;	//�C���X�g�[���ł������H

}AddFont;	//�ꎞ�I�ɃC���X�g�[������t�H���g���

typedef struct _Font
{
	int Handle;					//�t�H���g�n���h��(�t�H���g�f�[�^�̊Ǘ��ԍ�)

	char Name[FontNameStrMax];	//�t�H���g��
	int Size;					//�t�H���g�̃T�C�Y
	int Thinck;					//�t�H���g�̑���
	int Type;					//�A���`�G�C���A�X

}Font;	//�t�H���g�f�[�^�쐬�p

//�O���O���[�o���ϐ�
extern AddFont	addJiyu;				//���䂤���傤�t�H���g��ǉ�
extern Font		fontDefault;			//�f�t�H���g�̃t�H���g
extern Font		fontJiyu100pt;			//���䂤���傤�t�H���g100pt
extern Font		fontJiyu100ptFuchi;		//�t�H���g�̉�

//�O���v���g�^�C�v�錾
extern BOOL Font_Init(VOID);												//�C���X�g�[��������
extern AddFont FontInstall(const char* path, const char* name);				//�C���X�g�[��
extern VOID FontInstallErrMessage(const char* path);						//�C���X�g�[���G���[���b�Z�[�W
extern Font FontCreate(const char* name, int size, int thinck, int type);	//�t�H���g�n���h������
extern VOID FontCreateErrMessage(Font font);								//�t�H���g�n���h�������G���[���b�Z�[�W
extern VOID FontDelete(Font font);											//�t�H���g�n���h���폜
extern VOID	FontUnInstall(AddFont add);										//�A���C���X�g�[��
extern VOID	Font_End(VOID);													//�폜���A���C���X�g�[��

//�t�H���g�𑵂��ĕ`��
extern VOID DrawFormatStringToHandleAlign(int x, int y, Font_Align align,
	unsigned int Color, int FontHandle, const char* FormatString, ...);
