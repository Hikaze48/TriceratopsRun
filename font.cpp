//フォント処理のソースファイル

//ヘッダファイル読み込み
#include "font.h"

//グローバル変数
AddFont addJiyu;	//じゆうちょうフォントを追加
Font fontDefault;	//デフォルトのフォント
Font fontJiyu100pt;	//じゆうちょうフォント100pt(サイズが変わるなら変数名の数字も変えること！)

Font fontJiyu100ptFuchi;	//フォントの縁

//インストール＆生成
BOOL Font_Init(VOID)
{
	//外部のフォントを一時的にインストール
	addJiyu = FontInstall(FontPathJiyu, FontNameJiyu); if (addJiyu.CanInstall == FALSE) { return FALSE; }

	//フォントデータを生成してハンドルで管理
	fontDefault = FontCreate(FontDefName, FontDefSize, FontDefThinck, FontDefType); if (fontDefault.Handle == -1) { return FALSE; }
	fontJiyu100pt = FontCreate(addJiyu.FontName, 100, 1, FontDefType); if (fontJiyu100pt.Handle == -1) { return FALSE; }
	fontJiyu100ptFuchi = FontCreate(addJiyu.FontName, 100, 1, FontDefType); if (fontJiyu100ptFuchi.Handle == -1) { return FALSE; }

	return TRUE;
}

//インストール
AddFont FontInstall(const char* path, const char* name)
{
	AddFont add;

	//フォント情報を設定
	strcpy_s(add.FontPath, sizeof(add.FontPath), path);	//フォントのパスをコピー
	strcpy_s(add.FontName, sizeof(add.FontName), name);	//フォントの名前をコピー

	//※WinAPI関数
	//このソフト内のみ使えるよう、一時的にインストール
	if (AddFontResourceEx(add.FontPath, FR_PRIVATE, NULL) == 0)
	{
		//フォントインストール失敗
		FontInstallErrMessage(add.FontPath);	//エラーメッセージ表示
		add.CanInstall = FALSE;
	}
	else
	{
		//フォントインストール成功
		add.CanInstall = TRUE;
	}

	return add;
}

//インストールエラーメッセージ
VOID FontInstallErrMessage(const char* path)
{
	//エラー用文字列
	char ErrStr[FontErrStrMax];

	//エラー用文字列の内容を空にする
	for (int i = 0; i < FontErrStrMax; i++) { ErrStr[i] = '\0'; }	//ヌル文字(\0)で埋める

	//エラー内容を連結して生成
	sprintf_s(ErrStr, sizeof(ErrStr), "%s%s", path, FontInstallErrCap);

	//※WinAPI関数
	//パスが間違っているなどでインストールできない場合はエラー
	MessageBox(
		GetMainWindowHandle(),		//ウィンドウハンドル
		ErrStr,						//エラー内容
		FontInstallErrTitle,		//エラータイトル
		MB_OK);						//OKボタンのみ

	return;
}

//フォントハンドル生成
Font FontCreate(const char* name, int size, int thinck, int type)
{
	Font font;

	strcpy_s(font.Name, sizeof(font.Name), name);		//フォントの名前をコピー
	font.Size = size;
	font.Thinck = thinck;
	font.Type = type;

	//フォントの名前が違っているなどでフォントを作れないときはエラー
	if (CheckFontName(font.Name) == FALSE)
	{
		FontCreateErrMessage(font);	//エラーメッセージ表示
		font.Handle = -1;			//エラーのハンドル番号を入れておく
	}
	else
	{
		//フォントデータ生成
		font.Handle = CreateFontToHandle(font.Name, font.Size, font.Thinck, font.Type);
	}

	return font;
}

//フォントハンドル生成エラーメッセージ
VOID FontCreateErrMessage(Font font)
{
	//エラー用文字列
	char ErrStr[FontErrStrMax];

	//エラー用文字列の内容を空にする
	for (int i = 0; i < FontErrStrMax; i++) { ErrStr[i] = '\0'; }	//ヌル文字(\0)で埋める

	//エラー内容を連結して生成
	sprintf_s(ErrStr, sizeof(ErrStr), "%s%s", font.Name, FontCreateErrCap);

	//※WinAPI関数
	//フォントの名前が間違っているなどでインストールできない場合はエラー
	MessageBox(
		GetMainWindowHandle(),		//ウィンドウハンドル
		ErrStr,						//エラー内容
		FontCreateErrTitle,			//エラータイトル
		MB_OK);						//OKボタンのみ

	return;
}

//フォントハンドル削除
VOID FontDelete(Font font)
{
	//フォントハンドルを生成したなら
	if (font.Handle != -1)
	{
		//フォントデータを削除
		DeleteFontToHandle(font.Handle);
	}

	return;
}

//アンインストール
VOID FontUnInstall(AddFont add)
{
	//フォントをインストールしたなら
	if (add.CanInstall != FALSE)
	{
		//※WinAPI関数
		//アンインストール
		RemoveFontResourceEx(add.FontPath, FR_PRIVATE, NULL);
	}

	return;
}

//削除＆アンインストール
VOID Font_End(VOID)
{
	//フォントデータ削除
	FontDelete(fontDefault);
	FontDelete(fontJiyu100pt);

	//フォントアンインストール
	FontUnInstall(addJiyu);

	return;
}

//フォントを揃えて描画
//※注意：文字数がFontAlignStrMaxを超えるとそれ以上は出力しない
VOID DrawFormatStringToHandleAlign(int x, int y, Font_Align align, 
	unsigned int Color, int FontHandle, const char* FormatString, ...)
{
	int aling_x = x;	//揃えた時のX位置
	int aling_y = y;	//揃えた時のY位置
	int StrWidth = 0;	//文字列の幅
	int StrHeight = 0;	//文字列の高さ

	char DrawStr[FontAlignStrMax];	//描画するときの文字列
	
	//可変引数(...)をもらう準備をする
	va_list args;

	//可変引数はFormatStringの後ろから始まる
	va_start(args, FormatString);

	//文字列を書式指定子で可変引数から生成
	vsnprintf(DrawStr, sizeof(DrawStr), FormatString, args);

	//文字列の幅を計算
	StrWidth = GetDrawStringWidthToHandle(DrawStr, strlen(DrawStr), FontHandle);

	//文字列の高さを取得
	StrHeight = GetFontSizeToHandle(FontHandle);

	//揃えるごとに位置を計算する
	switch (align)
	{
	case Align_Left:
		//左揃えはそのままの位置なので、何もしない
		break;

	case Align_Center:
		//中央揃えは中央位置を計算

		//X位置のみ、中央に寄せる
		aling_x = x - StrWidth / 2;
		break;

	case Align_Right:
		//右揃え

		//X位置のみ、右に寄せる
		aling_x = x - StrWidth;
		break;

	case Align_AllCenter:
		//上下も左右も中央揃え

		//X位置を中央に寄せる
		aling_x = x - StrWidth / 2;

		//Y位置を中央に寄せる
		aling_y = y - StrHeight / 2;
		break;

	default:
		break;
	}

	//文字列描画
	DrawFormatStringToHandle(aling_x, aling_y, Color, FontHandle, "%s", DrawStr);

	//可変引数をもらうのを終わる
	va_end(args);

	return;
}