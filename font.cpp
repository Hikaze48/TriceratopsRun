//�t�H���g�����̃\�[�X�t�@�C��

//�w�b�_�t�@�C���ǂݍ���
#include "font.h"

//�O���[�o���ϐ�
AddFont addJiyu;	//���䂤���傤�t�H���g��ǉ�
Font fontDefault;	//�f�t�H���g�̃t�H���g
Font fontJiyu100pt;	//���䂤���傤�t�H���g100pt(�T�C�Y���ς��Ȃ�ϐ����̐������ς��邱�ƁI)

Font fontJiyu100ptFuchi;	//�t�H���g�̉�

//�C���X�g�[��������
BOOL Font_Init(VOID)
{
	//�O���̃t�H���g���ꎞ�I�ɃC���X�g�[��
	addJiyu = FontInstall(FontPathJiyu, FontNameJiyu); if (addJiyu.CanInstall == FALSE) { return FALSE; }

	//�t�H���g�f�[�^�𐶐����ăn���h���ŊǗ�
	fontDefault = FontCreate(FontDefName, FontDefSize, FontDefThinck, FontDefType); if (fontDefault.Handle == -1) { return FALSE; }
	fontJiyu100pt = FontCreate(addJiyu.FontName, 100, 1, FontDefType); if (fontJiyu100pt.Handle == -1) { return FALSE; }
	fontJiyu100ptFuchi = FontCreate(addJiyu.FontName, 100, 1, FontDefType); if (fontJiyu100ptFuchi.Handle == -1) { return FALSE; }

	return TRUE;
}

//�C���X�g�[��
AddFont FontInstall(const char* path, const char* name)
{
	AddFont add;

	//�t�H���g����ݒ�
	strcpy_s(add.FontPath, sizeof(add.FontPath), path);	//�t�H���g�̃p�X���R�s�[
	strcpy_s(add.FontName, sizeof(add.FontName), name);	//�t�H���g�̖��O���R�s�[

	//��WinAPI�֐�
	//���̃\�t�g���̂ݎg����悤�A�ꎞ�I�ɃC���X�g�[��
	if (AddFontResourceEx(add.FontPath, FR_PRIVATE, NULL) == 0)
	{
		//�t�H���g�C���X�g�[�����s
		FontInstallErrMessage(add.FontPath);	//�G���[���b�Z�[�W�\��
		add.CanInstall = FALSE;
	}
	else
	{
		//�t�H���g�C���X�g�[������
		add.CanInstall = TRUE;
	}

	return add;
}

//�C���X�g�[���G���[���b�Z�[�W
VOID FontInstallErrMessage(const char* path)
{
	//�G���[�p������
	char ErrStr[FontErrStrMax];

	//�G���[�p������̓��e����ɂ���
	for (int i = 0; i < FontErrStrMax; i++) { ErrStr[i] = '\0'; }	//�k������(\0)�Ŗ��߂�

	//�G���[���e��A�����Đ���
	sprintf_s(ErrStr, sizeof(ErrStr), "%s%s", path, FontInstallErrCap);

	//��WinAPI�֐�
	//�p�X���Ԉ���Ă���ȂǂŃC���X�g�[���ł��Ȃ��ꍇ�̓G���[
	MessageBox(
		GetMainWindowHandle(),		//�E�B���h�E�n���h��
		ErrStr,						//�G���[���e
		FontInstallErrTitle,		//�G���[�^�C�g��
		MB_OK);						//OK�{�^���̂�

	return;
}

//�t�H���g�n���h������
Font FontCreate(const char* name, int size, int thinck, int type)
{
	Font font;

	strcpy_s(font.Name, sizeof(font.Name), name);		//�t�H���g�̖��O���R�s�[
	font.Size = size;
	font.Thinck = thinck;
	font.Type = type;

	//�t�H���g�̖��O������Ă���ȂǂŃt�H���g�����Ȃ��Ƃ��̓G���[
	if (CheckFontName(font.Name) == FALSE)
	{
		FontCreateErrMessage(font);	//�G���[���b�Z�[�W�\��
		font.Handle = -1;			//�G���[�̃n���h���ԍ������Ă���
	}
	else
	{
		//�t�H���g�f�[�^����
		font.Handle = CreateFontToHandle(font.Name, font.Size, font.Thinck, font.Type);
	}

	return font;
}

//�t�H���g�n���h�������G���[���b�Z�[�W
VOID FontCreateErrMessage(Font font)
{
	//�G���[�p������
	char ErrStr[FontErrStrMax];

	//�G���[�p������̓��e����ɂ���
	for (int i = 0; i < FontErrStrMax; i++) { ErrStr[i] = '\0'; }	//�k������(\0)�Ŗ��߂�

	//�G���[���e��A�����Đ���
	sprintf_s(ErrStr, sizeof(ErrStr), "%s%s", font.Name, FontCreateErrCap);

	//��WinAPI�֐�
	//�t�H���g�̖��O���Ԉ���Ă���ȂǂŃC���X�g�[���ł��Ȃ��ꍇ�̓G���[
	MessageBox(
		GetMainWindowHandle(),		//�E�B���h�E�n���h��
		ErrStr,						//�G���[���e
		FontCreateErrTitle,			//�G���[�^�C�g��
		MB_OK);						//OK�{�^���̂�

	return;
}

//�t�H���g�n���h���폜
VOID FontDelete(Font font)
{
	//�t�H���g�n���h���𐶐������Ȃ�
	if (font.Handle != -1)
	{
		//�t�H���g�f�[�^���폜
		DeleteFontToHandle(font.Handle);
	}

	return;
}

//�A���C���X�g�[��
VOID FontUnInstall(AddFont add)
{
	//�t�H���g���C���X�g�[�������Ȃ�
	if (add.CanInstall != FALSE)
	{
		//��WinAPI�֐�
		//�A���C���X�g�[��
		RemoveFontResourceEx(add.FontPath, FR_PRIVATE, NULL);
	}

	return;
}

//�폜���A���C���X�g�[��
VOID Font_End(VOID)
{
	//�t�H���g�f�[�^�폜
	FontDelete(fontDefault);
	FontDelete(fontJiyu100pt);

	//�t�H���g�A���C���X�g�[��
	FontUnInstall(addJiyu);

	return;
}

//�t�H���g�𑵂��ĕ`��
//�����ӁF��������FontAlignStrMax�𒴂���Ƃ���ȏ�͏o�͂��Ȃ�
VOID DrawFormatStringToHandleAlign(int x, int y, Font_Align align, 
	unsigned int Color, int FontHandle, const char* FormatString, ...)
{
	int aling_x = x;	//����������X�ʒu
	int aling_y = y;	//����������Y�ʒu
	int StrWidth = 0;	//������̕�
	int StrHeight = 0;	//������̍���

	char DrawStr[FontAlignStrMax];	//�`�悷��Ƃ��̕�����
	
	//�ψ���(...)�����炤����������
	va_list args;

	//�ψ�����FormatString�̌�납��n�܂�
	va_start(args, FormatString);

	//������������w��q�ŉψ������琶��
	vsnprintf(DrawStr, sizeof(DrawStr), FormatString, args);

	//������̕����v�Z
	StrWidth = GetDrawStringWidthToHandle(DrawStr, strlen(DrawStr), FontHandle);

	//������̍������擾
	StrHeight = GetFontSizeToHandle(FontHandle);

	//�����邲�ƂɈʒu���v�Z����
	switch (align)
	{
	case Align_Left:
		//�������͂��̂܂܂̈ʒu�Ȃ̂ŁA�������Ȃ�
		break;

	case Align_Center:
		//���������͒����ʒu���v�Z

		//X�ʒu�̂݁A�����Ɋ񂹂�
		aling_x = x - StrWidth / 2;
		break;

	case Align_Right:
		//�E����

		//X�ʒu�̂݁A�E�Ɋ񂹂�
		aling_x = x - StrWidth;
		break;

	case Align_AllCenter:
		//�㉺�����E����������

		//X�ʒu�𒆉��Ɋ񂹂�
		aling_x = x - StrWidth / 2;

		//Y�ʒu�𒆉��Ɋ񂹂�
		aling_y = y - StrHeight / 2;
		break;

	default:
		break;
	}

	//������`��
	DrawFormatStringToHandle(aling_x, aling_y, Color, FontHandle, "%s", DrawStr);

	//�ψ��������炤�̂��I���
	va_end(args);

	return;
}