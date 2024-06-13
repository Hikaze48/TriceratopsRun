//ヘッダファイル読み込み
#include "DxLib.h"
#include "fps.h"
#include "game.h"
#include "key.h"
#include "mouse.h"
#include "font.h"
#include "music.h"
#include "graphic.h"
#include "animation.h"

//プロトタイプ宣言
VOID GameAndDxLibAllEnd(VOID);	//ゲーム終了の後始末

//ゲーム終了の後始末
//ここに???_End系を固める
VOID GameAndDxLibAllEnd(VOID)
{
	Font_End();			//フォント後始末
	Music_End();		//音楽後始末
	Graphic_End();		//画像後始末
	Animation_End();	//アニメーション後始末
	DxLib_End();		//DxLib終了

	return;
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR IpCmdLine, _In_ int nCmdShow)
{
	SetOutApplicationLogValidFlag(FALSE);				//Log.txtを出力しない
	ChangeWindowMode(TRUE);								//ウィンドウモードに設定
	SetGraphMode(GameWidth, GameHeight, GameColor);		//解像度を設定
	SetWindowSize(GameWidth, GameHeight);				//ウィンドウの大きさを設定
	SetMainWindowText(GameTitle);						//ウィンドウのタイトル
	SetBackgroundColor(0, 0, 0);						//ウィンドウの背景色
	SetWaitVSyncFlag(GameVsync);						//垂直同期の設定
	SetAlwaysRunFlag(TRUE);								//非アクティブでも実行する

	SetWindowIconID(GameIcon);							//アイコンを設定

	if (DxLib_Init() == -1) //DxLib初期化
	{
		return -1; //DxLib初期化失敗ならソフト終了
	}

	//裏画面に描画する（ダブルバッファリング）
	SetDrawScreen(DX_SCREEN_BACK);

	//フォント初期化
	if (Font_Init() == FALSE)
	{
		//ゲーム終了の後始末
		GameAndDxLibAllEnd();

		return -1;
	}

	//音楽初期化
	if (Music_Init() == FALSE)
	{
		GameAndDxLibAllEnd();	//ゲーム終了の後始末
		return -1;
	}

	//画像初期化
	if (Graphic_Init() == FALSE)
	{
		GameAndDxLibAllEnd();	//ゲーム終了の後始末
		return -1;
	}

	//アニメーション初期化
	if (Animation_Init() == FALSE)
	{
		GameAndDxLibAllEnd();	//ゲーム終了の後始末
		return -1;
	}

	//ゲーム画面初期化
	GameInit();

	//FPS初期化
	FPSInit();

	//キーボード初期化
	KeyInit();

	//マウス初期化
	MouseInit();

	//タイトルシーンを初期化
	TitleInit();

	//無限ループ（ゲームループ）
	while (TRUE)
	{
		//メッセージ処理をする（マウス操作やキー入力などを受け続ける）
		if (ProcessMessage() != 0)
		{
			break; //無限ループから出る（ゲーム終了）
		}

		//画面を消去する（1ループずつ書き換える）
		if (ClearDrawScreen() != 0)
		{
			break; //無限ループから出る（ゲーム終了） 
		}

		//ここに全てのゲーム動作が入る
		{
			//DrawString(0, 0, "Hello DxLib", GetColor(255, 255, 255)); //文字を画面に出力
			FPSCheck();		//FPS計測
			KeyUpdate();	//キーボード更新
			MouseUpdate();	//マウス更新

			//次のシーンを初期化
			if (NowGameScene != ChangeGameScene)
			{
				//各シーンの初期化を呼び出す
				switch (ChangeGameScene)
				{
				case TitleScene:
					TitleInit();
					break;
				case PlayScene:
					PlayInit();
					break;
				case ResultScene:
					ResultInit();
					break;
				default:
					break;
				}

				//シーン切り替え後のシーンを現在のシーンにする
				NowGameScene = ChangeGameScene;
			}
			else
			{
				//シーン切り替え
				switch (NowGameScene)
				{
				case TitleScene:
					TitleCtrl();
					break;
				case PlayScene:
					PlayCtrl();
					break;
				case ResultScene:
					ResultCtrl();
					break;
				default:
					break;
				}
			}

			FPSDraw(); //FPS描画
			FPSWait(); //FPS待機
		}

		//裏画面を画面に描画
		ScreenFlip();
	}

	//WaitKey(); //どれかのキーを入力（があるまで画面を閉じない）

	//DxLib_End(); //DxLib終了

	//ゲーム終了の後始末
	GameAndDxLibAllEnd();

	return 0; //ソフト終了
}