//マウス処理のソースファイル

//ヘッダファイル読み込み
#include "mouse.h"
#include "game.h"

//グローバル変数
POINT NowPoint;					//現在のマウスの位置
POINT OldPoint;					//以前のマウスの位置

int NowMousePressFrame[MouseKindMax];	//現在のマウスのボタンを押しているフレーム数を管理
int OldMousePressFrame[MouseKindMax];	//以前のマウスのボタンを押しているフレーム数を管理

int NowWheelValue;	//現在のマウスのホイール回転量
int OldWheelValue;	//以前のマウスのホイール回転量

//マウスのボタンコードとフレーム数を管理している配列の要素数を紐づける
int MouseCodeIndex[MouseKindMax]
{
	MOUSE_INPUT_LEFT,		//配列の要素数0にマウスのボタン情報の0x0001の情報を入れる
	MOUSE_INPUT_RIGHT,		//配列の要素数1にマウスのボタン情報の0x0002の情報を入れる
	MOUSE_INPUT_MIDDLE,		//配列の要素数2にマウスのボタン情報の0x0004の情報を入れる
	MOUSE_INPUT_4,			//配列の要素数3にマウスのボタン情報の0x0008の情報を入れる
	MOUSE_INPUT_5,			//配列の要素数4にマウスのボタン情報の0x0010の情報を入れる
	MOUSE_INPUT_6,			//配列の要素数5にマウスのボタン情報の0x0020の情報を入れる
	MOUSE_INPUT_7,			//配列の要素数6にマウスのボタン情報の0x0040の情報を入れる
	MOUSE_INPUT_8,			//配列の要素数7にマウスのボタン情報の0x0080の情報を入れる
};

//Now???系の変数の値をOld???系の変数へ入れる
VOID MouseNowIntoOld(VOID)
{
	OldPoint = NowPoint;	//マウスの位置

	//フレーム数
	for (int i = 0; i < MouseKindMax; i++)
	{
		OldMousePressFrame[i] = NowMousePressFrame[i];
	}

	//ホイール量
	OldWheelValue = NowWheelValue;

	return;
}

//マウスのボタンコードを配列の要素数に変換する
int MouseCodeToIndex(int MOUSE_INPUT_)
{
	for (int i = 0; i < MouseKindMax; i++)
	{
		//マウスコードが紐づけされているなら
		if (MouseCodeIndex[i] == MOUSE_INPUT_)
		{
			return i;	//その要素数を返す
		}
	}

	//マウスコードがないならエラー！
	return MouseCodeErrIndex;
}

//マウス処理の初期化
VOID MouseInit(VOID)
{
	//マウスの位置
	NowPoint.x = 0;
	NowPoint.y = 0;

	//フレーム数
	for (int i = 0; i < MouseKindMax; i++)
	{
		NowMousePressFrame[i] = 0;
	}

	//ホイール量
	NowWheelValue = 0;

	//Old系も初期化
	MouseNowIntoOld();

	return;
}

//マウス処理の更新
VOID MouseUpdate(VOID)
{
	//マウスのボタン情報をすべて取得
	int Input;

	//現在の情報を以前の情報として保存
	MouseNowIntoOld();

	int GetX, GetY;	//取得用のXY座標

	//現在のマウスのクライアント座標の位置を取得
	GetMousePoint(&GetX, &GetY);

	//マウスの座標に入れる
	NowPoint = GetPoint(GetX, GetY);

	//もし、マウスの座標がゲーム画面外にあるなら、ゲーム画面内に収める
	if (NowPoint.x < 0) { NowPoint.x = 0; }	//左
	else if (NowPoint.x > GameWidth) { NowPoint.x = GameWidth; } //右
	if (NowPoint.y < 0) { NowPoint.y = 0; }	//上
	else if (NowPoint.y > GameHeight) { NowPoint.y = GameHeight; } //下

	//マウスのボタン情報を一気に取得
	Input = GetMouseInput();

	//各ボタンを押しているかチェック
	for (int i = 0; i < MouseKindMax; i++)
	{
		//【if文の条件の説明】
		//取得した値をマウスコードでマスクした結果が、そのマウスコードならば
		// 例) 取得した値が0x0007	   →   最後のバイトが 00000111 の場合
		//   マウスコードが0x0001(左)  →	最後のバイトが 00000001 で、
		//論理積でマウスが処理(上下とも1なら1/それ以外は0)&---------
		//				  結果0x0001   →　 最後のバイトが 00000001 となる
		//複数の値が入っていても、マスク処理をすれば、特定の値のみ抽出できる！
		//※某サイトでは、Input & 1 << i としている。(左シフトで1のビットをずらす)
		if ((Input & MouseCodeIndex[i]) == MouseCodeIndex[i])
		{
			//現在押しているボタンのフレーム数をカウントアップ
			NowMousePressFrame[i]++;
		}
		else if ((Input & MouseCodeIndex[i]) != MouseCodeIndex[i])
		{
			//現在押しているボタンのフレーム数を零クリア
			NowMousePressFrame[i] = 0;
		}
	}

	//ホイールの回転量を取得
	NowWheelValue = GetMouseWheelRotVol();

	return;
}

//特定のマウスのボタンを押したか？
//引数：DXライブラリのマウスコード（MOUSE_INPUT_で始まるマクロ定義）
BOOL MouseDown(int MOUSE_INPUT_)
{
	//マウスコードを配列の要素数に変換
	int index = MouseCodeToIndex(MOUSE_INPUT_);

	//実在するマウスコードなら
	if (index != MouseCodeErrIndex)
	{
		//現在押しているなら
		if (NowMousePressFrame[index] > 0)
		{
			return TRUE;	//押している
		}
	}

	return FALSE;	//押していない
}

//特定のマウスのボタンをクリックしたか？
//引数：DXライブラリのキーコード（MOUSE_INPUT_で始まるマクロ定義）
//説明：「ボタンを押す→ボタンを上げる」がセットで行われたときが、クリック
BOOL MouseClick(int MOUSE_INPUT_)
{
	//マウスコードを配列の要素数に変換
	int index = MouseCodeToIndex(MOUSE_INPUT_);

	
	//実在するマウスコードなら
	if (index != MouseCodeErrIndex)
	{
		if (NowMousePressFrame[index] == 0		//現在は押していないが
			&& OldMousePressFrame[index] > 0)	//以前は押していた
		{
			return TRUE;	//押している
		}
	}

	return FALSE;	//押していない
}

//特定のマウスのボタンを押したフレーム数
//引数：DXライブラリのマウスコード（MOUSE_INPUT_で始まるマクロ定義）
//注意：戻り値はミリ秒などではなく、フレーム数！
int MousePressFrame(int MOUSE_INPUT_)
{
	//マウスコードを配列の要素数に変換
	int index = MouseCodeToIndex(MOUSE_INPUT_);

	//実在するマウスコードなら
	if (index != MouseCodeErrIndex)
	{
		return NowMousePressFrame[MOUSE_INPUT_];
	}

	return 0;
}

//マウスの現在の位置を取得する
POINT GetPointMouse(VOID)
{
	return NowPoint;
}

//マウスの以前の位置を取得する
POINT GetOldPointMouse(VOID)
{
	return OldPoint;
}

//マウスの以前と現在の位置の差を取得する
POINT GetDiffPointMouse(VOID)
{
	POINT diff;
	diff.x = OldPoint.x - NowPoint.x;
	diff.y = OldPoint.y - NowPoint.y;
	return diff;
}

//マウスの現在のホイール量を取得する
int GetWheelMouse(VOID)
{
	return NowWheelValue;
}

//矩形とマウスの座標が当たっているか？
BOOL CollRectToMouse(RECT rect)
{
	return CollRectToPoint(rect, NowPoint);
}

//矩形内でマウスのボタンを押したか？
BOOL CollRectToMouseDown(RECT rect, int MOUSE_INPUT_)
{
	//矩形内で
	if (CollRectToMouse(rect) == TRUE)
	{
		//ボタンを押したか？
		if (MouseDown(MOUSE_INPUT_) == TRUE)
		{
			//押した
			return TRUE;
		}
	}

	//押していない
	return FALSE;
}

//矩形内でマウスのボタンをクリックしたか？
BOOL CollRectToMouseClick(RECT rect, int MOUSE_INPUT_)
{
	//矩形内で
	if (CollRectToMouse(rect) == TRUE)
	{
		//ボタンをクリックしたか？
		if (MouseClick(MOUSE_INPUT_) == TRUE)
		{
			//クリックした
			return TRUE;
		}
	}

	//クリックしていない
	return FALSE;
}

//円内でマウスの座標が当たっているか？
BOOL CollCircleToMouse(CIRCLE circle)
{
	return CollCircleToPoint(circle, NowPoint);
}

//円とマウスの点が当たっているか？
BOOL CollCircleToMousePoint(CIRCLE circle)
{
	//円と点の当たり判定の結果をそのまま返す
	return CollCircleToMouse(circle);
}

//円内でマウスのボタンを押したか？
BOOL CollCircleToMouseDown(CIRCLE circle, int MOUSE_INPUT_)
{
	//円内で
	if (CollCircleToMouse(circle) == TRUE)
	{
		//ボタンを押したか？
		if (MouseDown(MOUSE_INPUT_) == TRUE)
		{
			//押した
			return TRUE;
		}
	}

	//押していない
	return FALSE;
}

//円内でマウスのボタンをクリックしたか？
BOOL CollCircleToMouseClick(CIRCLE circle, int MOUSE_INPUT_)
{
	//円内で
	if (CollCircleToMouse(circle) == TRUE)
	{
		//ボタンをクリックしたか？
		if (MouseClick(MOUSE_INPUT_) == TRUE)
		{
			//クリックした
			return TRUE;
		}
	}

	//クリックしていない
	return FALSE;
}