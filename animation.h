//アニメーション処理のヘッダファイル
#pragma once

//ヘッダファイル読み込み
#include "DxLib.h"
#include "graphic.h"
#include "game.h"

//エラー
#define AnimationLoadErrCap		"が読み込めませんでした"
#define AnimationLoadErrTitle		"アニメーション読み込みエラー"

//文字列の長さ
#define AnimationPathStrMax	256
#define AnimationErrStrMax	512

//アニメーションファイルのパス
#define GraphicPathTitleAnimExpl	".\\graphic\\explosion.png"
#define AnimExplDivX				5								//爆発アニメの横分割数
#define AnimExplDivY				1								//爆発アニメの縦分割数

#define GraphicPathTitleAnimCoin	".\\graphic\\coin.png"
#define AnimCoinDivX				14								//コインアニメの横分割数
#define AnimCoinDivY				1								//コインアニメの縦分割数

#define GraphicPathTitleAnimSlash	".\\graphic\\slash.png"
#define AnimSlashDivX				5								//斬撃アニメの横分割数
#define AnimSlashDivY				1								//斬撃アニメの縦分割数

#define GraphicPathAnimAvoid		".\\graphic\\My_Big_kyoryu1_avoid.png"
#define AnimAvoidDivX				1								//避けるアニメの横分割数
#define AnimAvoidDivY				3								//避けるアニメの縦分割数

#define GraphicPathAnimMyTriceratops		".\\graphic\\My_Big_kyoryu1.png"
#define AnimMyTriceratopsDivX			3							//自分のトリケラトプスの横分割数
#define AnimMyTriceratopsDivY			1							//自分のトリケラトプスの縦分割数

#define GraphicPathAnimEnemyTriceratops		".\\graphic\\Enemy_Big_kyoryu1.png"
#define AnimEnemyTriceratopsDivX			3						//敵のトリケラトプスの横分割数
#define AnimEnemyTriceratopsDivY			1						//敵のトリケラトプスの縦分割数

#define GraphicPathAnimAnkylosaurus		".\\graphic\\Enemy_Big_kyoryu2.png"
#define AnimAnkylosaurusDivX		3								//敵のアンキロサウルスの横分割数
#define AnimAnkylosaurusDivY		1								//敵のアンキロサウルスの縦分割数

#define GraphicPathAnimPachycephalosaurus		".\\graphic\\Enemy_Big_kyoryu3.png"
#define AnimPachycephalosaurusDivX			3						//敵のパキケファロサウルスの横分割数
#define AnimPachycephalosaurusDivY			1						//敵のパキケファロサウルスの縦分割数

#define GraphicPathAnimSeismosaurus		".\\graphic\\Enemy_Big_kyoryu4.png"
#define AnimSeismosaurusDivX		3								//敵のセイスモサウルスの横分割数
#define AnimSeismosaurusDivY		1								//敵のセイスモサウルスの縦分割数

//アニメーション無限継続(負数なので通常はありえない時間)
#define AnimationInfinity	-99999

//アニメーション1回のみ(負数なので通常はありえない時間)
#define AnimationOnce		-11111

//アニメーション構造体のコア部分
typedef struct _AnimationCore
{
	int NowHandleIndex = -1;		//現在のハンドルの要素数

	int DivX = 0;					//画像の横分割数
	int DivY = 0;					//画像の縦分割数

	int FrameCnt = 0;				//アニメーションのコア時間
	int FrameMax = 0;				//アニメーションのコア時間MAX

	int FrameByFrameCnt = 0;		//アニメのコア送り時間
	int FrameByFrameMax = 0;		//アニメのコア送り時間MAX

	BOOL IsAnimStartFlg = FALSE;	//アニメーション開始フラグ
}AnimationCore;

//アニメーション構造体
typedef struct _Animation
{
	Graphic			g;	//画像
	AnimationCore	a;	//アニメーションコア
	int* Handle;		//ハンドル(メモリを動的確保)
}Animation;

//恐竜
typedef struct _DINO
{
	float JumpBeforeY;			//ジャンプ前の縦の位置
	int JumpTime;				//ジャンプ時間

	double XSpeed;				//横移動の速さ

	RECT Ajust;					//当たり判定（調整）
	double JumpPower;			//ジャンプ力（半径）
	BOOL IsJump = FALSE;		//ジャンプ中？
	BOOL IsJumpOver = FALSE;	//ジャンプで飛び越したか？
	Animation DINOa;			//アニメーション
}DINO;

//外部グローバル変数
extern Animation AnimExpl;						//爆発アニメーション
extern Animation AnimCoin;						//コインアニメーション
extern Animation AnimSlash;						//斬撃アニメーション
extern Animation AnimAvoid;						//避けるアニメーション

extern DINO AnimMyTriceratops;					//自分のトリケラトプスアニメーション
extern DINO AnimEnemyTriceratops;				//敵のトリケラトプスアニメーション
extern DINO AnimAnkylosaurus;					//アンキロサウルスアニメーション
extern DINO AnimPachycephalosaurus;				//パキケファロサウルスアニメーション
extern DINO AnimSeismosaurus;					//セイスモサウルスアニメーション

//extern DINO My;									//自分
extern DINO Enemy[EnemyOneTimeMax];				//敵

//外部プロトタイプ宣言
extern BOOL Animation_Init(VOID);								//読み込み・ハンドル生成
extern VOID Animation_End(VOID);								//後始末
extern VOID AnimationLoadErrMessage(const char* path);			//読み込みエラーメッセージ


extern Animation LoadAnimation(Graphic graphic, int XNum, int YNum);	//アニメーション読み込み
extern VOID DrawAnimation(Animation* animation);						//描画
extern VOID DeleteAnimation(Animation animation);						//解放

extern VOID AnimationStart(Animation* animation, int MillTime, int MillInterval);	//アニメーション開始