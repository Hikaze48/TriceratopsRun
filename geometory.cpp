//幾何学(図形)処理のソースファイル

//ヘッダファイル読み込み
#include "geometory.h"

//関数

//X地点とY地点からPOINT型を一時的に取得
POINT GetPoint(int x, int y)
{
	POINT pt;

	pt.x = x;
	pt.y = y;

	return pt;
}

//点と点が当たっているか？
BOOL CollPointToPoint(POINT a, POINT b)
{
	if (a.x == b.x && a.y == b.y)
	{
		//当たっている
		return TRUE;
	}

	//当たっていない
	return FALSE;
}

//左上右下からRECT型を一時的に取得
RECT GetRect(int left, int top, int right, int bottom)
{
	RECT rect;

	rect.left = left;
	rect.top = top;
	rect.right = right;
	rect.bottom = bottom;

	return rect;
}

//矩形と矩形が当たっているか？
BOOL CollRectToRect(RECT a, RECT b)
{
	if (a.left <= b.right
		&& a.top <= b.bottom
		&& a.right >= b.left
		&& a.bottom >= b.top)
	{
		//当たっている
		return TRUE;
	}

	//当たっていない
	return FALSE;
}

//矩形と点が当たっているか？
BOOL CollRectToPoint(RECT rect, POINT pt)
{
	if (rect.left <= pt.x
		&& rect.top <= pt.y
		&& rect.right >= pt.x
		&& rect.bottom >= pt.y)
	{
		//当たっている
		return TRUE;
	}

	//当たっていない
	return FALSE;
}

//RECT型で矩形を描く
VOID DrawRect(RECT rect, unsigned int color, BOOL fill)
{
	//矩形を描く
	DrawBox(
		rect.left,
		rect.top,
		rect.right,
		rect.bottom,
		color,
		fill
	);

	return;
}

//CIRCLE型を一時的に取得
CIRCLE GetCircle(POINT pt, float rad)
{
	CIRCLE c;

	c.pt = pt;
	c.radius = rad;

	return c;
}

//円と円が当たっているか？
BOOL CollCircleToCircle(CIRCLE C1, CIRCLE C2)
{
	//三角形をつくる
	float a = 0.0f;
	float b = 0.0f;
	float c = 0.0f;

	a = C1.pt.x - C2.pt.x;
	b = C1.pt.y - C2.pt.y;
	c = sqrt(a * a + b * b);

	if (c <= C1.radius + C2.radius)
	{
		//当たっている
		return TRUE;
	}

	/*
	//高速処理版
	a = C1.pt.x - C2.pt.x;
	b = C1.pt.y - C2.pt.y;
	c = a * a + b * b;
	float rad = C1.radius + C2.radius;	//半径の合計

	if (c <= (rad * rad)
	{
		//当たっている
		return TRUE;
	}
	*/

	//当たっていない
	return FALSE;
}

//円と点が当たっているか？
BOOL CollCircleToPoint(CIRCLE circle, POINT pt)
{
	//三角形をつくる
	float a = 0.0f;
	float b = 0.0f;
	float c = 0.0f;

	a = circle.pt.x - pt.x;
	b = circle.pt.y - pt.y;
	c = sqrt(a * a + b * b);

	if (c <= circle.radius)
	{
		//当たっている
		return TRUE;
	}

	//当たっていない
	return FALSE;
}

//CIRCLE型で描く
VOID DrawEn(CIRCLE circle, unsigned int color, BOOL fill)
{
	//円を描く
	DrawCircle(circle.pt.x, circle.pt.y, circle.radius, color, fill);

	return;
}