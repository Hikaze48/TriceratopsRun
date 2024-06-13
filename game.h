//ゲーム処理のヘッダファイル
#pragma once

//ヘッダファイル読み込み
#include "DxLib.h"

//マクロ定義
#define GameWidth	1280			//画面の幅
#define GameHeight	720				//画面の高さ
#define GameColor	32				//画面の色
#define GameTitle	"Tricera Run"		//画面タイトル
#define GameVsync	TRUE			//V-Syncを使うならTRUE
#define GameIcon	555				// 画面アイコン

#define GameDebug	FALSE			//デバッグモード

#define GameSceneCount		3		//ゲームシーンの数
#define GameSceneNameMax	20		//ゲームシーン名の文字数MAX

#define GameSceneChangeFrame 60		//ゲームシーンの切り替えを可能にするフレーム数

//スコアのデータパス
#define ScoreDataPath	".\\score.txt"

//地面
#define Ground		700				//地面の高さ
#define JumpValue	350				//ジャンプ力(元は500)
#define JumpUpSpeed 3				//ジャンプの上がるスピード(元は1)

//タイトルで待つ時間
#define TitleWait	1.0f			//秒数
#define ResultWait	3.0f			//秒数

//敵
#define EnemyOneTimeMax 7			//敵の一度に出てこられる量(元は4)

//色系の名前(原色大辞典様を参考→https://www.colordic.org/)

#define Color_black			GetColor(  0,   0,   0)
#define Color_white			GetColor(255, 255, 255)
#define Color_skyblue		GetColor(135, 206, 235)
#define Color_tomato		GetColor(255, 99, 71)
#define Color_lightyellow	GetColor(255, 255, 224)
#define Color_lawngreen		GetColor(124, 252, 0)
#define Color_pink			GetColor(255, 192, 203)
#define Color_yellow		GetColor(255, 255, 0)

//列挙型

//ゲームシーン
enum GameScene {
	TitleScene,		//タイトルシーン
	PlayScene,		//プレイシーン
	ResultScene	//リザルトシーン
};

typedef struct _SCORE
{
	int ScorePoint = 0;			//ゲーム内のスコア
	int ReadScore = 0;		//読み込んだスコア
	FILE* Scorefp = NULL;	//スコアデータのファイルポインタ
}SCORE;

//外部のグローバル変数
extern enum GameScene NowGameScene;		//現在のゲームシーン
extern enum GameScene ChangeGameScene;	//切り替わるゲームシーン
extern SCORE score;

//外部のプロトタイプ宣言

extern VOID GameInit(VOID);			//ゲーム画面初期化
extern HWND GetGameHandle(VOID);	//ゲーム画面のハンドルを取得
extern RECT GetGameWindow(VOID);	//ゲーム画面の矩形を取得

extern POINT GetGameWindowCenter(VOID);	//ゲーム画面の上下左右の中央座標を取得

extern VOID TitleInit(VOID);	//タイトル初期化
extern VOID TitleCtrl(VOID);	//タイトル管理
extern VOID TitleProc(VOID);	//タイトル処理
extern VOID TitleDraw(VOID);	//タイトル描画

extern VOID PlayInit(VOID);		//プレイ初期化
extern VOID PlayCtrl(VOID);		//プレイ管理
extern VOID PlayProc(VOID);		//プレイ処理
extern VOID PlayDraw(VOID);		//プレイ描画

extern VOID ResultInit(VOID);	//リザルト初期化
extern VOID ResultCtrl(VOID);	//リザルト管理
extern VOID ResultProc(VOID);	//リザルト処理
extern VOID ResultDraw(VOID);	//リザルト描画
