//�}�E�X�����̃\�[�X�t�@�C��

//�w�b�_�t�@�C���ǂݍ���
#include "mouse.h"
#include "game.h"

//�O���[�o���ϐ�
POINT NowPoint;					//���݂̃}�E�X�̈ʒu
POINT OldPoint;					//�ȑO�̃}�E�X�̈ʒu

int NowMousePressFrame[MouseKindMax];	//���݂̃}�E�X�̃{�^���������Ă���t���[�������Ǘ�
int OldMousePressFrame[MouseKindMax];	//�ȑO�̃}�E�X�̃{�^���������Ă���t���[�������Ǘ�

int NowWheelValue;	//���݂̃}�E�X�̃z�C�[����]��
int OldWheelValue;	//�ȑO�̃}�E�X�̃z�C�[����]��

//�}�E�X�̃{�^���R�[�h�ƃt���[�������Ǘ����Ă���z��̗v�f����R�Â���
int MouseCodeIndex[MouseKindMax]
{
	MOUSE_INPUT_LEFT,		//�z��̗v�f��0�Ƀ}�E�X�̃{�^������0x0001�̏�������
	MOUSE_INPUT_RIGHT,		//�z��̗v�f��1�Ƀ}�E�X�̃{�^������0x0002�̏�������
	MOUSE_INPUT_MIDDLE,		//�z��̗v�f��2�Ƀ}�E�X�̃{�^������0x0004�̏�������
	MOUSE_INPUT_4,			//�z��̗v�f��3�Ƀ}�E�X�̃{�^������0x0008�̏�������
	MOUSE_INPUT_5,			//�z��̗v�f��4�Ƀ}�E�X�̃{�^������0x0010�̏�������
	MOUSE_INPUT_6,			//�z��̗v�f��5�Ƀ}�E�X�̃{�^������0x0020�̏�������
	MOUSE_INPUT_7,			//�z��̗v�f��6�Ƀ}�E�X�̃{�^������0x0040�̏�������
	MOUSE_INPUT_8,			//�z��̗v�f��7�Ƀ}�E�X�̃{�^������0x0080�̏�������
};

//Now???�n�̕ϐ��̒l��Old???�n�̕ϐ��֓����
VOID MouseNowIntoOld(VOID)
{
	OldPoint = NowPoint;	//�}�E�X�̈ʒu

	//�t���[����
	for (int i = 0; i < MouseKindMax; i++)
	{
		OldMousePressFrame[i] = NowMousePressFrame[i];
	}

	//�z�C�[����
	OldWheelValue = NowWheelValue;

	return;
}

//�}�E�X�̃{�^���R�[�h��z��̗v�f���ɕϊ�����
int MouseCodeToIndex(int MOUSE_INPUT_)
{
	for (int i = 0; i < MouseKindMax; i++)
	{
		//�}�E�X�R�[�h���R�Â�����Ă���Ȃ�
		if (MouseCodeIndex[i] == MOUSE_INPUT_)
		{
			return i;	//���̗v�f����Ԃ�
		}
	}

	//�}�E�X�R�[�h���Ȃ��Ȃ�G���[�I
	return MouseCodeErrIndex;
}

//�}�E�X�����̏�����
VOID MouseInit(VOID)
{
	//�}�E�X�̈ʒu
	NowPoint.x = 0;
	NowPoint.y = 0;

	//�t���[����
	for (int i = 0; i < MouseKindMax; i++)
	{
		NowMousePressFrame[i] = 0;
	}

	//�z�C�[����
	NowWheelValue = 0;

	//Old�n��������
	MouseNowIntoOld();

	return;
}

//�}�E�X�����̍X�V
VOID MouseUpdate(VOID)
{
	//�}�E�X�̃{�^���������ׂĎ擾
	int Input;

	//���݂̏����ȑO�̏��Ƃ��ĕۑ�
	MouseNowIntoOld();

	int GetX, GetY;	//�擾�p��XY���W

	//���݂̃}�E�X�̃N���C�A���g���W�̈ʒu���擾
	GetMousePoint(&GetX, &GetY);

	//�}�E�X�̍��W�ɓ����
	NowPoint = GetPoint(GetX, GetY);

	//�����A�}�E�X�̍��W���Q�[����ʊO�ɂ���Ȃ�A�Q�[����ʓ��Ɏ��߂�
	if (NowPoint.x < 0) { NowPoint.x = 0; }	//��
	else if (NowPoint.x > GameWidth) { NowPoint.x = GameWidth; } //�E
	if (NowPoint.y < 0) { NowPoint.y = 0; }	//��
	else if (NowPoint.y > GameHeight) { NowPoint.y = GameHeight; } //��

	//�}�E�X�̃{�^��������C�Ɏ擾
	Input = GetMouseInput();

	//�e�{�^���������Ă��邩�`�F�b�N
	for (int i = 0; i < MouseKindMax; i++)
	{
		//�yif���̏����̐����z
		//�擾�����l���}�E�X�R�[�h�Ń}�X�N�������ʂ��A���̃}�E�X�R�[�h�Ȃ��
		// ��) �擾�����l��0x0007	   ��   �Ō�̃o�C�g�� 00000111 �̏ꍇ
		//   �}�E�X�R�[�h��0x0001(��)  ��	�Ō�̃o�C�g�� 00000001 �ŁA
		//�_���ςŃ}�E�X������(�㉺�Ƃ�1�Ȃ�1/����ȊO��0)&---------
		//				  ����0x0001   ���@ �Ō�̃o�C�g�� 00000001 �ƂȂ�
		//�����̒l�������Ă��Ă��A�}�X�N����������΁A����̒l�̂ݒ��o�ł���I
		//���^�T�C�g�ł́AInput & 1 << i �Ƃ��Ă���B(���V�t�g��1�̃r�b�g�����炷)
		if ((Input & MouseCodeIndex[i]) == MouseCodeIndex[i])
		{
			//���݉����Ă���{�^���̃t���[�������J�E���g�A�b�v
			NowMousePressFrame[i]++;
		}
		else if ((Input & MouseCodeIndex[i]) != MouseCodeIndex[i])
		{
			//���݉����Ă���{�^���̃t���[�������N���A
			NowMousePressFrame[i] = 0;
		}
	}

	//�z�C�[���̉�]�ʂ��擾
	NowWheelValue = GetMouseWheelRotVol();

	return;
}

//����̃}�E�X�̃{�^�������������H
//�����FDX���C�u�����̃}�E�X�R�[�h�iMOUSE_INPUT_�Ŏn�܂�}�N����`�j
BOOL MouseDown(int MOUSE_INPUT_)
{
	//�}�E�X�R�[�h��z��̗v�f���ɕϊ�
	int index = MouseCodeToIndex(MOUSE_INPUT_);

	//���݂���}�E�X�R�[�h�Ȃ�
	if (index != MouseCodeErrIndex)
	{
		//���݉����Ă���Ȃ�
		if (NowMousePressFrame[index] > 0)
		{
			return TRUE;	//�����Ă���
		}
	}

	return FALSE;	//�����Ă��Ȃ�
}

//����̃}�E�X�̃{�^�����N���b�N�������H
//�����FDX���C�u�����̃L�[�R�[�h�iMOUSE_INPUT_�Ŏn�܂�}�N����`�j
//�����F�u�{�^�����������{�^�����グ��v���Z�b�g�ōs��ꂽ�Ƃ����A�N���b�N
BOOL MouseClick(int MOUSE_INPUT_)
{
	//�}�E�X�R�[�h��z��̗v�f���ɕϊ�
	int index = MouseCodeToIndex(MOUSE_INPUT_);

	
	//���݂���}�E�X�R�[�h�Ȃ�
	if (index != MouseCodeErrIndex)
	{
		if (NowMousePressFrame[index] == 0		//���݂͉����Ă��Ȃ���
			&& OldMousePressFrame[index] > 0)	//�ȑO�͉����Ă���
		{
			return TRUE;	//�����Ă���
		}
	}

	return FALSE;	//�����Ă��Ȃ�
}

//����̃}�E�X�̃{�^�����������t���[����
//�����FDX���C�u�����̃}�E�X�R�[�h�iMOUSE_INPUT_�Ŏn�܂�}�N����`�j
//���ӁF�߂�l�̓~���b�Ȃǂł͂Ȃ��A�t���[�����I
int MousePressFrame(int MOUSE_INPUT_)
{
	//�}�E�X�R�[�h��z��̗v�f���ɕϊ�
	int index = MouseCodeToIndex(MOUSE_INPUT_);

	//���݂���}�E�X�R�[�h�Ȃ�
	if (index != MouseCodeErrIndex)
	{
		return NowMousePressFrame[MOUSE_INPUT_];
	}

	return 0;
}

//�}�E�X�̌��݂̈ʒu���擾����
POINT GetPointMouse(VOID)
{
	return NowPoint;
}

//�}�E�X�̈ȑO�̈ʒu���擾����
POINT GetOldPointMouse(VOID)
{
	return OldPoint;
}

//�}�E�X�̈ȑO�ƌ��݂̈ʒu�̍����擾����
POINT GetDiffPointMouse(VOID)
{
	POINT diff;
	diff.x = OldPoint.x - NowPoint.x;
	diff.y = OldPoint.y - NowPoint.y;
	return diff;
}

//�}�E�X�̌��݂̃z�C�[���ʂ��擾����
int GetWheelMouse(VOID)
{
	return NowWheelValue;
}

//��`�ƃ}�E�X�̍��W���������Ă��邩�H
BOOL CollRectToMouse(RECT rect)
{
	return CollRectToPoint(rect, NowPoint);
}

//��`���Ń}�E�X�̃{�^�������������H
BOOL CollRectToMouseDown(RECT rect, int MOUSE_INPUT_)
{
	//��`����
	if (CollRectToMouse(rect) == TRUE)
	{
		//�{�^�������������H
		if (MouseDown(MOUSE_INPUT_) == TRUE)
		{
			//������
			return TRUE;
		}
	}

	//�����Ă��Ȃ�
	return FALSE;
}

//��`���Ń}�E�X�̃{�^�����N���b�N�������H
BOOL CollRectToMouseClick(RECT rect, int MOUSE_INPUT_)
{
	//��`����
	if (CollRectToMouse(rect) == TRUE)
	{
		//�{�^�����N���b�N�������H
		if (MouseClick(MOUSE_INPUT_) == TRUE)
		{
			//�N���b�N����
			return TRUE;
		}
	}

	//�N���b�N���Ă��Ȃ�
	return FALSE;
}

//�~���Ń}�E�X�̍��W���������Ă��邩�H
BOOL CollCircleToMouse(CIRCLE circle)
{
	return CollCircleToPoint(circle, NowPoint);
}

//�~�ƃ}�E�X�̓_���������Ă��邩�H
BOOL CollCircleToMousePoint(CIRCLE circle)
{
	//�~�Ɠ_�̓����蔻��̌��ʂ����̂܂ܕԂ�
	return CollCircleToMouse(circle);
}

//�~���Ń}�E�X�̃{�^�������������H
BOOL CollCircleToMouseDown(CIRCLE circle, int MOUSE_INPUT_)
{
	//�~����
	if (CollCircleToMouse(circle) == TRUE)
	{
		//�{�^�������������H
		if (MouseDown(MOUSE_INPUT_) == TRUE)
		{
			//������
			return TRUE;
		}
	}

	//�����Ă��Ȃ�
	return FALSE;
}

//�~���Ń}�E�X�̃{�^�����N���b�N�������H
BOOL CollCircleToMouseClick(CIRCLE circle, int MOUSE_INPUT_)
{
	//�~����
	if (CollCircleToMouse(circle) == TRUE)
	{
		//�{�^�����N���b�N�������H
		if (MouseClick(MOUSE_INPUT_) == TRUE)
		{
			//�N���b�N����
			return TRUE;
		}
	}

	//�N���b�N���Ă��Ȃ�
	return FALSE;
}