//ゲーム処理のソースファイル

//ヘッダファイル読み込み
#include "game.h"
#include "key.h"
#include "mouse.h"
#include "geometory.h"
#include "font.h"
#include "music.h"
#include "graphic.h"
#include "animation.h"
#include <math.h>

//グローバル変数

//ゲームシーン
enum GameScene NowGameScene;	//現在のゲームシーン
enum GameScene ChangeGameScene;	//切り替わるゲームシーン
SCORE score;

//ゲーム画面関係
RECT GameWindow;				//ゲーム画面の矩形
HWND GameHandle;				//ゲームのウィンドウハンドル

double EnemyCreateTime = 0.0f;			//敵生成カウント
double EnemyCreateTimeMAX = 0.0f;		//敵生成カウントMAX

BOOL IsGameOverFlg = FALSE;		//ゲームオーバーフラグ
BOOL IsAvoidFlg = FALSE;		//避けるフラグ

double StiffnessTime = 0.0f;	//避けた後の硬直時間

//ゲームシーンの名前
char GameSceneName[GameSceneCount][GameSceneNameMax]
{
	"タイトル画面",
	"プレイ画面",
	"リザルト画面"
};

//シーン切り替え後のフレーム数を管理
int GameSceneFrameCount[GameSceneCount];

//関数

//ゲーム画面のハンドルを取得
HWND GetGameHandle(VOID)
{
	return GameHandle;
}

//ゲーム画面の矩形を取得
RECT GetGameWindow(VOID)
{
	return GameWindow;
}

//ゲーム画面の上下左右の中央座標を取得
POINT GetGameWindowCenter(VOID)
{
	POINT pt;
	pt.x = GameWidth / 2;
	pt.y = GameHeight / 2;

	return pt;
}

//ゲーム画面初期化
VOID GameInit(VOID)
{
	//ゲーム画面のハンドル(管理番号)を取得
	GameHandle = GetMainWindowHandle();

	//ゲーム画面の矩形を取得
	GameWindow = GetRect(0, 0, GameWidth, GameHeight);

	//最初のシーンはタイトルから
	NowGameScene = TitleScene;

	//次のシーンもタイトルから
	ChangeGameScene = TitleScene;


	return;
}

//タイトル初期化
VOID TitleInit(VOID)
{
	//シーンを切り替えたフレーム数を初期化
	GameSceneFrameCount[ChangeGameScene] = 0;

	//プレイ画面準備

	//スコアデータ関連
	{
		//スコア初期化
		score.ScorePoint = 0;

		//スコアデータがあるか確認
		fopen_s(&score.Scorefp, ScoreDataPath, "r");
		if (score.Scorefp == NULL)
		{
			//新たにファイル新規作成
			fopen_s(&score.Scorefp, ScoreDataPath, "w");

			//初期化データを入れる
			fprintf_s(score.Scorefp, "%d", 0);
		}

		//スコアデータを読み取る
		fscanf_s(score.Scorefp, "%d", &score.ReadScore);

		//スコアデータを閉じる
		fclose(score.Scorefp);
	}

	IsGameOverFlg = FALSE;		//ゲームオーバーフラグ

	AnimMyTriceratops.DINOa.g.c.Pos.x = GameWidth / 4 * 1 - AnimMyTriceratops.DINOa.g.c.Width / 2;
	AnimMyTriceratops.DINOa.g.c.Pos.y = Ground - AnimMyTriceratops.DINOa.g.c.Height;
	AnimMyTriceratops.JumpPower = JumpValue;		//ジャンプ力
	AnimMyTriceratops.IsJump = FALSE;
	AnimMyTriceratops.XSpeed = 4.5;
	//当たり判定調整
	AnimMyTriceratops.Ajust = AnimMyTriceratops.DINOa.g.c.Coll;
	AnimMyTriceratops.Ajust.left = 10;
	AnimMyTriceratops.Ajust.right = 10;
	AnimMyTriceratops.Ajust.top = 50;
	AnimMyTriceratops.Ajust.bottom = 20;


	AnimEnemyTriceratops.DINOa.g.c.Pos.x = GameWidth;
	AnimEnemyTriceratops.DINOa.g.c.Pos.y = Ground - AnimEnemyTriceratops.DINOa.g.c.Height;
	AnimEnemyTriceratops.JumpPower = JumpValue;		//ジャンプ力
	AnimEnemyTriceratops.IsJump = FALSE;
	AnimEnemyTriceratops.IsJumpOver = FALSE;
	AnimEnemyTriceratops.XSpeed = 2.0;				//おっとりと。
	//当たり判定調整
	AnimEnemyTriceratops.Ajust = AnimEnemyTriceratops.DINOa.g.c.Coll;
	AnimEnemyTriceratops.Ajust.left = 10;
	AnimEnemyTriceratops.Ajust.right = 10;
	AnimEnemyTriceratops.Ajust.top = 50;
	AnimEnemyTriceratops.Ajust.bottom = 20;


	AnimAnkylosaurus.DINOa.g.c.Pos.x = GameWidth;
	AnimAnkylosaurus.DINOa.g.c.Pos.y = Ground - AnimAnkylosaurus.DINOa.g.c.Height;
	AnimAnkylosaurus.JumpPower = JumpValue;				//ジャンプ力
	AnimAnkylosaurus.IsJump = FALSE;
	AnimAnkylosaurus.IsJumpOver = FALSE;
	AnimAnkylosaurus.XSpeed = 4.0f;						//すばやく。
	//当たり判定調整
	AnimAnkylosaurus.Ajust = AnimAnkylosaurus.DINOa.g.c.Coll;
	AnimAnkylosaurus.Ajust.left = 10;
	AnimAnkylosaurus.Ajust.right = 10;
	AnimAnkylosaurus.Ajust.top = 50;
	AnimAnkylosaurus.Ajust.bottom = 20;


	AnimPachycephalosaurus.DINOa.g.c.Pos.x = GameWidth;
	AnimPachycephalosaurus.DINOa.g.c.Pos.y = Ground - AnimPachycephalosaurus.DINOa.g.c.Height;
	AnimPachycephalosaurus.JumpPower = JumpValue;				//ジャンプ力
	AnimPachycephalosaurus.IsJump = FALSE;
	AnimPachycephalosaurus.IsJumpOver = FALSE;
	AnimPachycephalosaurus.XSpeed = 5.0f;						//荒々しく。
	//当たり判定調整
	AnimPachycephalosaurus.Ajust = AnimPachycephalosaurus.DINOa.g.c.Coll;
	AnimPachycephalosaurus.Ajust.left = 20;
	AnimPachycephalosaurus.Ajust.right = 20;
	AnimPachycephalosaurus.Ajust.top = 0;
	AnimPachycephalosaurus.Ajust.bottom = 20;


	AnimSeismosaurus.DINOa.g.c.Pos.x = GameWidth;
	AnimSeismosaurus.DINOa.g.c.Pos.y = Ground - AnimSeismosaurus.DINOa.g.c.Height;
	AnimSeismosaurus.JumpPower = JumpValue;				//ジャンプ力
	AnimSeismosaurus.IsJump = FALSE;
	AnimSeismosaurus.IsJumpOver = FALSE;
	AnimSeismosaurus.XSpeed = 3.0f;						//雄大に。
	//当たり判定調整
	AnimSeismosaurus.Ajust = AnimSeismosaurus.DINOa.g.c.Coll;
	AnimSeismosaurus.Ajust.left = 0;
	AnimSeismosaurus.Ajust.right = 0;
	AnimSeismosaurus.Ajust.top = 0;
	AnimSeismosaurus.Ajust.bottom = 20;

	for (int i = 0; i < EnemyOneTimeMax; i++)
	{
		Enemy[i].DINOa.g.c.IsDraw = FALSE;		//敵の画像は全て非表示
	}

	TitleBackImage.c.Pos.x = 0;	//背景
	BackImageTurn.c.Pos.x = GameWidth;		//背景反転

	//硬直時間
	StiffnessTime = 5.0f;

	//画像エフェクト開始
	GraphicFxStart(
		&TitleButton,		//どの画像にエフェクトをかける？
		GraFxFadeInOut,		//どんなエフェクトをかける？
		GraFxInfinity,		//エフェクト無限継続
		1000);				//1000ミリ秒間隔

	//アニメーション開始
	AnimationStart(
		&AnimExpl,			//どのアニメーションを再生する？
		1000,				//アニメーション継続時間
		500);				//500ミリ秒間隔で次のコマへ

	/*
	//アニメーション開始
	AnimationStart(
		&AnimCoin,			//どのアニメーションを再生する？
		AnimationOnce,		//アニメーション継続時間
		100);				//100ミリ秒間隔で次のコマへ

	//アニメーション開始
	AnimationStart(
		&AnimSlash,			//どのアニメーションを再生する？
		AnimationInfinity,	//アニメーション継続時間
		50);				//50ミリ秒間隔で次のコマへ
	:*/

	if (GameDebug == TRUE)
	{
		//シーン名表示
		DrawFormatStringToHandle(
			GameWidth - 200, 0, Color_white,
			fontDefault.Handle,	//このフォントデータを使用
			"%s%s", GameSceneName[NowGameScene], "初期化"
		);

		//適切なシーンの初期化ができているかテスト
		//ScreenFlip();
		//WaitTimer(1000);
	}

	return;
}
//タイトル管理
VOID TitleCtrl(VOID)
{
	TitleProc();	//処理をしてから
	TitleDraw();	//描画する!

	return;
}
//タイトル処理
VOID TitleProc(VOID)
{
	//シーン切り替え後のフレーム数をカウントアップ
	GameSceneFrameCount[NowGameScene]++;

	//フェードインして再生
	FadeInPlayMusic(&TitleBGM, 5000);	//5秒かけてフェードイン

	
	//シーン切り替え
	if (CollRectToMouseDown(TitleButton.c.Coll, MOUSE_INPUT_LEFT) == TRUE	//タイトルボタンのどこかをマウス左ボタンで押したとき
		&& GameSceneFrameCount[NowGameScene] >= GameSceneChangeFrame
		|| KeyClick(KEY_INPUT_SPACE) == TRUE								//スペースキーを押したとき
		&& GameSceneFrameCount[NowGameScene] >= GameSceneChangeFrame)		//かつ、切り替え可能なフレーム数を超えたら
	{
		//効果音
		PlayMusic(ButtonClickSE);

		//音楽停止
		PauseMusic(&TitleBGM);

		//シーン切り替え
		ChangeGameScene = PlayScene;

		//すぐに切り替える
		return;
	}


	return;
}
//タイトル描画
VOID TitleDraw(VOID)
{
	//処理が早いほど奥に書かれる
	DrawGraphic(&TitleBackImage);	//背景画像を描画
	DrawGraphic(&TitleLogo);		//タイトルロゴを描画
	DrawGraphic(&TitleButton);		//タイトルボタンを描画

	//アニメーションを試しに描く
	//DrawAnimation(&AnimExpl);		//爆発アニメ(1回のみ)
	//DrawAnimation(&AnimCoin);		//コインアニメ(無限)
	//DrawAnimation(&AnimSlash);		//斬撃アニメ(無限)

	//最高スコアを描画
	DrawFormatStringToHandleAlign(
		GetGameWindowCenter().x, 50, Align_AllCenter, Color_black,
		fontJiyu100pt.Handle,	//このフォントデータを使用
		"%s%05d", "最高SCORE:", score.ReadScore
	);

	if (GameDebug == TRUE)
	{
		/*
		//適当に描画
		DrawBox(0, 0, GameWidth, GameHeight, Color_skyblue, TRUE);
		*/

		//シーン名表示
		DrawFormatStringToHandle(
			GameWidth - 200, 0, Color_white,
			fontDefault.Handle,	//このフォントデータを使用
			"%s%s", GameSceneName[NowGameScene], "描画中"
		);

		//マウスポイントの描画
		DrawFormatStringToHandleAlign(
			GetPointMouse().x, GetPointMouse().y, Align_AllCenter, Color_black,
			fontJiyu100pt.Handle,	//このフォントデータを使用
			"Mouse:x%4d/Y%4d", GetPointMouse().x, GetPointMouse().y
		);
	}
	
	
	return;
}

//プレイ初期化
VOID PlayInit(VOID)
{
	//シーンを切り替えたフレーム数を初期化
	GameSceneFrameCount[ChangeGameScene] = 0;

	AnimationStart(
		&AnimMyTriceratops.DINOa,	//どのアニメーションを再生する？
		AnimationInfinity,	//アニメーション継続時間
		250);				//250ミリ秒間隔で次のコマへ

	AnimationStart(
		&AnimEnemyTriceratops.DINOa,	//どのアニメーションを再生する？
		AnimationInfinity,	//アニメーション継続時間
		250);				//250ミリ秒間隔で次のコマへ

	AnimationStart(
		&AnimAnkylosaurus.DINOa,	//どのアニメーションを再生する？
		AnimationInfinity,	//アニメーション継続時間
		250);				//250ミリ秒間隔で次のコマへ

	AnimationStart(
		&AnimPachycephalosaurus.DINOa,	//どのアニメーションを再生する？
		AnimationInfinity,	//アニメーション継続時間
		250);				//250ミリ秒間隔で次のコマへ

	AnimationStart(
		&AnimSeismosaurus.DINOa,	//どのアニメーションを再生する？
		AnimationInfinity,	//アニメーション継続時間
		250);				//250ミリ秒間隔で次のコマへ

	AnimationStart(
		&AnimExpl,			//どのアニメーションを再生する？
		1000,				//アニメーション継続時間
		500);				//500ミリ秒間隔で次のコマへ

	if (GameDebug == TRUE)
	{
		//シーン名表示
		DrawFormatStringToHandle(
			GameWidth - 200, 0, Color_white,
			fontDefault.Handle,	//このフォントデータを使用
			"%s%s", GameSceneName[NowGameScene], "初期化"
		);

		//適切なシーンの初期化ができているかテスト
		//ScreenFlip();
		//WaitTimer(1000);
	}

	return;
}
//プレイ管理
VOID PlayCtrl(VOID)
{
	PlayProc();	//処理をしてから
	PlayDraw();	//描画する!

	return;
}
//プレイ処理
VOID PlayProc(VOID)
{
	score.ScorePoint++;

	//シーン切り替え後のフレーム数をカウントアップ
	GameSceneFrameCount[NowGameScene]++;

	//音楽再生
	PlayMusic(PlayBGM);


	//敵の処理
	{
		for (int i = 0; i < EnemyOneTimeMax; i++)
		{
			if (Enemy[i].DINOa.g.c.IsDraw == TRUE)
			{
				//当たり判定再計算
				Enemy[i].DINOa.g.c.Coll.left = Enemy[i].DINOa.g.c.Pos.x + Enemy[i].Ajust.left;
				Enemy[i].DINOa.g.c.Coll.top = Enemy[i].DINOa.g.c.Pos.y + Enemy[i].Ajust.top;
				Enemy[i].DINOa.g.c.Coll.right = Enemy[i].DINOa.g.c.Pos.x + Enemy[i].DINOa.g.c.Width - Enemy[i].Ajust.right;
				Enemy[i].DINOa.g.c.Coll.bottom = Enemy[i].DINOa.g.c.Pos.y + Enemy[i].DINOa.g.c.Height - Enemy[i].Ajust.bottom;
				
				//敵の移動
				Enemy[i].DINOa.g.c.Pos.x -= Enemy[i].XSpeed;

				//敵が左端まで行ったら描画を消す
				if (Enemy[i].DINOa.g.c.Pos.x + Enemy[i].DINOa.g.c.Width <= 0)
				{
					Enemy[i].DINOa.g.c.IsDraw = FALSE;
				}

				//敵を越したらスコアアップ
				if (Enemy[i].IsJumpOver == FALSE && Enemy[i].DINOa.g.c.Pos.x < AnimMyTriceratops.DINOa.g.c.Pos.x)
				{
					score.ScorePoint += 100;
					Enemy[i].IsJumpOver = TRUE;
				}

				//自分と敵が当たったらゲームオーバー
				if (AnimMyTriceratops.DINOa.g.c.Coll.left <= Enemy[i].DINOa.g.c.Coll.right
					&& AnimMyTriceratops.DINOa.g.c.Coll.top <= Enemy[i].DINOa.g.c.Coll.bottom
					&& AnimMyTriceratops.DINOa.g.c.Coll.right >= Enemy[i].DINOa.g.c.Coll.left
					&& AnimMyTriceratops.DINOa.g.c.Coll.bottom >= Enemy[i].DINOa.g.c.Coll.top)
				{
					//ゲームオーバーフラグ
					IsGameOverFlg = TRUE;

					//爆発アニメーション
					AnimExpl.g.c.Pos.x = (AnimMyTriceratops.DINOa.g.c.Pos.x + Enemy[i].DINOa.g.c.Pos.x) / 2;
					AnimExpl.g.c.Pos.y = (AnimMyTriceratops.DINOa.g.c.Pos.y + Enemy[i].DINOa.g.c.Pos.y) / 2;

					//恐竜のアニメーションを描画しないようにする
					AnimMyTriceratops.DINOa.g.c.IsDraw = FALSE;
					Enemy[i].DINOa.g.c.IsDraw = FALSE;

					//ジャンプ効果音
					PlayMusic(ExplSE);
					/*
					//音楽停止
					PauseMusic(&PlayBGM);

					//最高得点更新
					if (score.ScorePoint > score.ReadScore)
					{
						//最高得点書き出し
						fopen_s(&score.Scorefp, ScoreDataPath, "w");
						fprintf_s(score.Scorefp, "%d", score.ScorePoint);
						fclose(score.Scorefp);
					}

					if (AnimExpl.a.IsAnimStartFlg == FALSE)
					{
						ChangeGameScene = ResultScene;
					}
					*/
				}
			}
		}

		//敵が出てくる時間を計算
		EnemyCreateTime += fps.Deltatime;

		//スコアを見て敵が出てくる時間を調整
		if (score.ScorePoint < 2000) { EnemyCreateTimeMAX = 8.0f; }
		else if (score.ScorePoint < 5000) { EnemyCreateTimeMAX = 5.0f; }
		else if (score.ScorePoint < 7500) { EnemyCreateTimeMAX = 3.0f; }
		else if (score.ScorePoint < 10000) { EnemyCreateTimeMAX = 1.0f; }

		//敵を生成
		if (EnemyCreateTime >= EnemyCreateTimeMAX)
		{
			//一度に出る敵の数は制限する
			for (int i = 0; i < EnemyOneTimeMax; i++)
			{
				if (Enemy[i].DINOa.g.c.IsDraw == FALSE)
				{
					//4種から選ぶ
					switch (GetRand(3))
					{
					case 0:
						Enemy[i] = AnimEnemyTriceratops;
						break;
					case 1:
						Enemy[i] = AnimAnkylosaurus;
						break;
					case 2:
						Enemy[i] = AnimPachycephalosaurus;
						break;
					case 3:
						Enemy[i] = AnimSeismosaurus;
						break;
					default:
						break;
					}

					//ループを抜ける
					break;
				}
			}

			//敵生成時間を元に戻す
			EnemyCreateTime = 0.0f;
		}

	}

	//自分の処理
	{
		//当たり判定再計算
		{
			AnimMyTriceratops.DINOa.g.c.Coll.left = AnimMyTriceratops.DINOa.g.c.Pos.x + AnimMyTriceratops.Ajust.left;
			AnimMyTriceratops.DINOa.g.c.Coll.top = AnimMyTriceratops.DINOa.g.c.Pos.y + AnimMyTriceratops.Ajust.top;
			AnimMyTriceratops.DINOa.g.c.Coll.right = AnimMyTriceratops.DINOa.g.c.Pos.x + AnimMyTriceratops.DINOa.g.c.Width - AnimMyTriceratops.Ajust.right;
			AnimMyTriceratops.DINOa.g.c.Coll.bottom = AnimMyTriceratops.DINOa.g.c.Pos.y + AnimMyTriceratops.DINOa.g.c.Height - AnimMyTriceratops.Ajust.bottom;
		}

		//スペースキーか上でジャンプ
		if (KeyPressFrame(KEY_INPUT_SPACE) > 0 && AnimMyTriceratops.IsJump == FALSE
			|| KeyPressFrame(KEY_INPUT_UP) > 0 && AnimMyTriceratops.IsJump == FALSE)
		{
			AnimMyTriceratops.IsJump = TRUE;
			AnimMyTriceratops.JumpBeforeY = AnimMyTriceratops.DINOa.g.c.Pos.y;	//ジャンプ前の位置を取っておく
			AnimMyTriceratops.JumpTime = 0;						//ジャンプ時間初期化
			AnimMyTriceratops.DINOa.g.c.Pos.y--;					//ちょっと上に飛ばす

			//ジャンプ効果音
			PlayMusic(JumpSE);
		}

		//ジャンプ中の時
		if (AnimMyTriceratops.IsJump == TRUE)
		{
			AnimMyTriceratops.JumpTime += JumpUpSpeed;
			AnimMyTriceratops.DINOa.g.c.Pos.y = AnimMyTriceratops.JumpBeforeY - sin(AnimMyTriceratops.JumpTime * DX_PI / 180.0f) * AnimMyTriceratops.JumpPower;

			//地面についたら
			if (AnimMyTriceratops.DINOa.g.c.Pos.y + AnimMyTriceratops.DINOa.g.c.Height >= Ground)
			{
				AnimMyTriceratops.DINOa.g.c.Pos.y = Ground - AnimMyTriceratops.DINOa.g.c.Height;
				AnimMyTriceratops.IsJump = FALSE;
			}
		}


		//右を押していたら右に進む
		if (KeyPressFrame(KEY_INPUT_RIGHT) > 0 || KeyPressFrame(KEY_INPUT_D) > 0)
		{
			AnimMyTriceratops.DINOa.g.c.Pos.x += AnimMyTriceratops.XSpeed;

			//右画面端以上にはいけない
			if (AnimMyTriceratops.DINOa.g.c.Pos.x + AnimMyTriceratops.DINOa.g.c.Width >= GameWidth)
			{
				AnimMyTriceratops.DINOa.g.c.Pos.x = GameWidth - AnimMyTriceratops.DINOa.g.c.Width;
			}
		}


		//左を押したら左に進む
		if (KeyPressFrame(KEY_INPUT_LEFT) > 0 || KeyPressFrame(KEY_INPUT_A) > 0)
		{
			AnimMyTriceratops.DINOa.g.c.Pos.x -= AnimMyTriceratops.XSpeed;

			//左画面端以上にはいけない
			if (AnimMyTriceratops.DINOa.g.c.Pos.x <= 0)
			{
				AnimMyTriceratops.DINOa.g.c.Pos.x = 0;
			}
		}


		//下を押したら避ける
		if (KeyPressFrame(KEY_INPUT_DOWN) > 0 && IsAvoidFlg == FALSE && StiffnessTime >= 5.0f
			|| KeyPressFrame(KEY_INPUT_S) > 0 && IsAvoidFlg == FALSE && StiffnessTime >= 5.0f)
		{
			//避けるフラグ
			IsAvoidFlg = TRUE;

			//避ける効果音
			PlayMusic(AvoidSE);

			//硬直時間
			StiffnessTime = 0;

			//アニメーションを初期化
			AnimationStart(
				&AnimAvoid,			//どのアニメーションを再生する？
				900,				//アニメーション継続時間
				300);				//100ミリ秒間隔で次のコマへ

			AnimAvoid.g.c.Pos.x = AnimMyTriceratops.DINOa.g.c.Pos.x;
			AnimAvoid.g.c.Pos.y = AnimMyTriceratops.DINOa.g.c.Pos.y - 20;

			AnimMyTriceratops.DINOa.g.c.IsDraw = FALSE;
		}
		
		//避けるアニメーション中
		if (AnimAvoid.a.IsAnimStartFlg == TRUE)
		{
			//キャラの当たり判定をなくす
			AnimMyTriceratops.DINOa.g.c.Coll.left = 0;
			AnimMyTriceratops.DINOa.g.c.Coll.top = 0;
			AnimMyTriceratops.DINOa.g.c.Coll.right = 0;
			AnimMyTriceratops.DINOa.g.c.Coll.bottom = 0;
		}

		//避けるアニメーションが終わったら
		if (AnimAvoid.a.IsAnimStartFlg == FALSE && IsAvoidFlg == TRUE)
		{
			IsAvoidFlg = FALSE;
			AnimMyTriceratops.DINOa.g.c.IsDraw = TRUE;
		}

		//避ける硬直時間
		StiffnessTime += fps.Deltatime;
	}


	if (AnimExpl.a.IsAnimStartFlg == FALSE)
	{
		//音楽停止
		PauseMusic(&PlayBGM);

		//最高得点更新
		if (score.ScorePoint > score.ReadScore)
		{
			//最高得点書き出し
			fopen_s(&score.Scorefp, ScoreDataPath, "w");
			fprintf_s(score.Scorefp, "%d", score.ScorePoint);
			fclose(score.Scorefp);
		}

		ChangeGameScene = ResultScene;
	}

	return;
}
//プレイ描画
VOID PlayDraw(VOID)
{
	//背景移動
	TitleBackImage.c.Pos.x -= 1;	//背景
	BackImageTurn.c.Pos.x -= 1;		//背景反転

	//背景の位置をを右に戻す
	if (TitleBackImage.c.Pos.x + TitleBackImage.c.Width <= 0) { TitleBackImage.c.Pos.x = BackImageTurn.c.Pos.x + BackImageTurn.c.Width; }
	if (BackImageTurn.c.Pos.x + BackImageTurn.c.Width <= 0) { BackImageTurn.c.Pos.x = TitleBackImage.c.Pos.x + TitleBackImage.c.Width; }

	//草原移動
	for (int i = 0; i < BackGrassNum; i++)
	{
		BackGrass[i].c.Pos.x -= 10;
	}

	//草原の位置を右に戻す
	for (int i = 0; i < BackGrassNum; i++)
	{
		if (BackGrass[i].c.Pos.x + BackGrass[i].c.Width <= 0)
		{
			if (i == 0)
			{
				//0の時だけは特殊
				BackGrass[i].c.Pos.x = BackGrass[BackGrassNum - 1].c.Pos.x + BackGrass[BackGrassNum - 1].c.Width;
			}
			else
			{
				//それ以外の時は一つ左の画像の右に並べ直す
				BackGrass[i].c.Pos.x = BackGrass[i - 1].c.Pos.x + BackGrass[i - 1].c.Width;
			}
		}
	}

	//背景描く
	DrawGraphic(&TitleBackImage);	//背景画像を描画
	DrawTurnGraph(BackImageTurn.c.Pos.x, BackImageTurn.c.Pos.y, BackImageTurn.Handle, TRUE);	//背景反転

	//草原描画
	for (int i = 0; i < BackGrassNum; i++)
	{
		//ゲーム画面に映りこむ位置なら
		if (BackGrass[i].c.Pos.x < GameWidth)
		{
			DrawGraphic(&BackGrass[i]);
		}
	}

	//敵描画
	{
		for (int i = 0; i < EnemyOneTimeMax; i++)
		{
			DrawAnimation(&Enemy[i].DINOa);
		}
	}

	//自分描画
	{
		DrawAnimation(&AnimMyTriceratops.DINOa);
	}

	//自分と敵が当たったらゲームオーバー
	if (IsGameOverFlg == TRUE)
	{
		DrawAnimation(&AnimExpl);		//爆発アニメ(1回のみ)
	}

	//避けることが可能か描画
	if (StiffnessTime >= 5.0f)
	{
		DrawFormatStringToHandleAlign(
			GetGameWindowCenter().x, 150, Align_AllCenter, Color_skyblue,
			fontJiyu100pt.Handle,	//このフォントデータを使用
			"%s", "下入力で避けれる"
		);
	}
	else
	{
		DrawFormatStringToHandleAlign(
			GetGameWindowCenter().x, 150, Align_AllCenter, Color_pink,
			fontJiyu100pt.Handle,	//このフォントデータを使用
			"%s%.1f", "クールタイム:",5.0f - StiffnessTime
		);
	}

	//避ける
	if (IsAvoidFlg == TRUE)
	{
		DrawAnimation(&AnimAvoid);		//避けるアニメ(1回のみ)
	}

	//スコアを描画
	DrawFormatStringToHandleAlign(
		GetGameWindowCenter().x, 50, Align_AllCenter, Color_black,
		fontJiyu100pt.Handle,	//このフォントデータを使用
		"%s%05d", "SCORE:", score.ScorePoint
	);


	if (GameDebug == TRUE)
	{
		//シーン名表示
		DrawFormatStringToHandle(
			GameWidth - 200, 0, Color_white,
			fontDefault.Handle,	//このフォントデータを使用
			"%s%s", GameSceneName[NowGameScene], "描画化"
		);

		//地面を描画
		DrawLine(0, Ground, GameWidth, Ground, GetColor(128, 0, 0), 5);

		//マウスポインタを描画
		DrawFormatStringToHandleAlign(
			GetPointMouse().x, GetPointMouse().y, Align_AllCenter, Color_black,
			fontJiyu100pt.Handle,	//このフォントデータを使用
			"Mouse:x%4d/Y%4d", GetPointMouse().x, GetPointMouse().y
		);
	}


	return;
}

//リザルト初期化
VOID ResultInit(VOID)
{
	//画像エフェクト開始
	GraphicFxStart(
		&GameoverLogo,		//どの画像にエフェクトをかける？
		GraFxFadeInOut,		//どんなエフェクトをかける？
		GraFxInfinity,		//エフェクト無限継続
		1000);				//1000ミリ秒間隔

	GraphicFxStart(
		&NewrecordLogo,		//どの画像にエフェクトをかける？
		GraFxFadeInOut,		//どんなエフェクトをかける？
		GraFxInfinity,		//エフェクト無限継続
		1000);				//1000ミリ秒間隔

	//TitleBackImage.c.Pos.x = 0;		//背景

	if (GameDebug == TRUE)
	{
		//シーン名表示
		DrawFormatStringToHandle(
			GameWidth - 200, 0, Color_white,
			fontDefault.Handle,	//このフォントデータを使用
			"%s%s", GameSceneName[NowGameScene], "初期化"
		);

		//適切なシーンの初期化ができているかテスト
		//ScreenFlip();
		//WaitTimer(1000);
	}

	//シーンを切り替えたフレーム数を初期化
	GameSceneFrameCount[ChangeGameScene] = 0;

	return;
}
//リザルト管理
VOID ResultCtrl(VOID)
{
	ResultProc();	//処理をしてから
	ResultDraw();	//描画する!

	return;
}
//リザルト処理 
VOID ResultProc(VOID)
{
	//シーン切り替え後のフレーム数をカウントアップ
	GameSceneFrameCount[NowGameScene]++;

	//音楽再生
	PlayMusic(ResultBGM);

	if (KeyClick(KEY_INPUT_SPACE) == TRUE									//スペースキーを押したとき
		&& GameSceneFrameCount[NowGameScene] >= GameSceneChangeFrame)		//かつ、切り替え可能なフレーム数を超えたら
	{
		//効果音
		PlayMusic(ButtonClickSE);

		//音楽停止
		PauseMusic(&ResultBGM);

		//シーン切り替え
		ChangeGameScene = TitleScene;

		//すぐに切り替える
		return;
	}

	return;
}
//リザルト描画
extern VOID ResultDraw(VOID)
{	
	//処理が速いほど奥に書かれる

	DrawGraphic(&TitleBackImage);	//背景画像を描画
	DrawTurnGraph(BackImageTurn.c.Pos.x, BackImageTurn.c.Pos.y, BackImageTurn.Handle, TRUE);	//背景反転を描画

	DrawGraphic(&GameoverLogo);		//ゲームオーバーロゴを描画
	DrawFormatStringToHandleAlign(
		GetGameWindowCenter().x, 50, Align_AllCenter, Color_black,
		fontJiyu100pt.Handle,	//このフォントデータを使用
		"%s%05d", "SCORE:", score.ScorePoint
	);

	//最高得点なら
	if (score.ScorePoint > score.ReadScore)
	{
		DrawGraphic(&NewrecordLogo);	//ニューレコードロゴを描画
	}


	if (GameDebug == TRUE)
	{
		//シーン名表示
		DrawFormatStringToHandle(
			GameWidth - 200, 0, Color_white,
			fontDefault.Handle,	//このフォントデータを使用
			"%s%s", GameSceneName[NowGameScene], "描画化"
		);
	}


	return;
}