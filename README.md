# Tricera Run!!!

## 背景
・ゲーム制作に興味があり、基礎から学び、ある程度のプログラミング処理を覚えることができるDxライブラリを用いた。

## ゲーム概要
自キャラクターを操作し、敵キャラクターをジャンプや避けて生存し続けて高スコアを目指すゲームです。

![スクリーンショット 2024-06-13 213018](https://github.com/Hikaze48/TriceratopsRun/assets/172498055/e7a3ee94-ddd8-4192-afd5-f66d1b771b9a)
![スクリーンショット 2024-06-13 213040](https://github.com/Hikaze48/TriceratopsRun/assets/172498055/6a8f1393-0715-4fe2-b908-5c18cade342d)
![スクリーンショット 2024-06-13 213057](https://github.com/Hikaze48/TriceratopsRun/assets/172498055/4852b83a-b5fd-422f-9ef9-659a256bc601)


## 基本操作
方向キー:キャラ移動  
SPACE:ジャンプ  
下方向キー:避ける（クールダウン5秒）  

## 使用方法
・Visual Studio 2022にて開発されました。
・ビルドする際にはDXライブラリが必要です。  
・プロジェクト内にリポジトリ内のファイルを置く  
・プロジェクト内にfontフォルダ、graphicフォルダ、musicフォルダを作成する  
・fontフォルダにJiyucho.ttfを置く  
・プロジェクト内にgame.ico（自作）を置く（ソリューションエクスプローラーのリソースファイルにgame.icoとResource.rcとJiyucho.tftを追加）  
・graphicフォルダに以下を置く  
1. coin.png  
2. Enemy_Big_kyoryu1.png  
3. Enemy_Big_kyoryu2.png  
4. Enemy_Big_kyoryu3.png  
5. Enemy_Big_kyoryu4.png  
6. explosion.png  
7. GameoverLogo.png(自作)  
8. My_Big_kyoryu1.png  
9. My_Big_kyoryu1_avoid.png  
10. NewrecordLogo.png(自作)  
11. slash.png  
12. StartButton.png
13. TitleBack.jpg  
14. TitleLogo.png(自作)  
15. weed.png  

・musicフォルダ内にはbgmフォルダとseフォルダを作成する  
・bgmフォルダに以下を置く
1. maou_05_halzion.mp3  
2. maou_14_shining_star.mp3  
3. maou_19_12345.mp3

・seフォルダに以下を置く
1. avoidSE.mp3  
2. buttonClickSE.mp3  
3. explSE.mp3  
4. jumpSE.mp3  

# ライセンス
## 使用した素材
・使用しているファイル名は利用しやすいように変更しています。この作品の制作には、下記の素材を使用させていただきました。  
- フォント
  - font/Jiyucho.ttf 「じゆうちょうフォント TrueType Edition」　よく飛ばない鳥様 https://yokutobanaitori.web.fc2.com/index_bottom.html

- 背景・エフェクトグラフィック・キャラクター
  - graphic/coin.png ← pipo-btleffect007.png 「戦闘用エフェクトアニメーション画像」 ぴぽや様 http://piposozai.blog76.fc2.com
  - graphic/explosion.png ← pipo-btleffect003.png 「戦闘用エフェクトアニメーション画像」 ぴぽや様 http://piposozai.blog76.fc2.com
  - graphic/slash.png ← pipo-btleffect001.png 「戦闘用エフェクトアニメーション画像」 ぴぽや様 http://piposozai.blog76.fc2.com
  - graphic/Enemy_Big_kyoryu1.png ← $Big_kyouryu1.png 「ツクールMV規格_恐竜キャラチップ（歩行グラ）」 あ行。アワラギ様 https://harumaki.hiyamugi.com/
  - graphic/Enemy_Big_kyoryu2.png ← $Big_kyouryu2.png 「ツクールMV規格_恐竜キャラチップ（歩行グラ）」 あ行。アワラギ様 https://harumaki.hiyamugi.com/
  - graphic/Enemy_Big_kyoryu3.png ← $Big_kyouryu3.png 「ツクールMV規格_恐竜キャラチップ（歩行グラ）」 あ行。アワラギ様 https://harumaki.hiyamugi.com/
  - graphic/Enemy_Big_kyoryu4.png ← $Big_kyouryu4.png 「ツクールMV規格_恐竜キャラチップ（歩行グラ）」 あ行。アワラギ様 https://harumaki.hiyamugi.com/
  - graphic/My_Big_kyoryu1.png ← $Big_kyouryu1.png 「ツクールMV規格_恐竜キャラチップ（歩行グラ）」 あ行。アワラギ様 https://harumaki.hiyamugi.com/
  - graphic/My_Big_kyoryu1_avoid.png ← $Big_kyouryu1.png 「ツクールMV規格_恐竜キャラチップ（歩行グラ）」 あ行。アワラギ様 https://harumaki.hiyamugi.com/
  - graphic/StartButton.png ← 001_01_click.png 「フリー素材：ボタン台素材 その9」　サイト｜空想曲線
　ＵＲＬ｜https://kopacurve.blog.fc2.com/
  - graphic/TitleBack.jpg　「木々の背景（緑 グリーン）無料イラスト/夏49502」 サイト｜素材GOOD
  ＵＲＬ｜https://sozai-good.com/
  - graphic/weed.png 「草のフリーイラスト素材」 サイト｜イラスト緑花（RYOKKA） ＵＲＬ｜https://illust-ryokka.jp/

- 音楽
  - music/bgm/maou_05_halzion.mp3 「ハルジオン」 魔王魂様 https://maou.audio/
  - music/bgm/maou_14_shining_star.mp3 「シャイニングスター」 魔王魂様 https://maou.audio/
  - music/bgm/maou_19_12345.mp3 「12345」 魔王魂様 https://maou.audio/  
  ● 音楽：魔王魂  
  ● 音楽：まおうだましい  
  ● 音楽：MaouDamashii  

- SE
  - music/se/avoidSE.mp3 ← ちょこっと触る.mp3「ちょこっと触る」 サイト｜効果音ラボ ＵＲＬ｜https://soundeffect-lab.info/
  - music/se/buttonClickSE.mp3 ← 決定ボタンを押す13.mp3「決定ボタンを押す13」 サイト｜効果音ラボ ＵＲＬ｜https://soundeffect-lab.info/
  - music/se/explSE.mp3 ← 爆発1.mp3「爆発1」 サイト｜効果音ラボ ＵＲＬ｜https://soundeffect-lab.info/
  - music/se/jumpSE.mp3 ← ニュッ2.mp3「ニュッ2」 サイト｜効果音ラボ ＵＲＬ｜https://soundeffect-lab.info/  

- DX Library Copyright (C) 2001-2021 Takumi Yamada.  

<details>
<summary>DXライブラリの使用しているライセンスです。広げると表示されます。</summary>

libjpeg Copyright (C) 1991-2013, Thomas G. Lane, Guido Vollbeding.
   this software is based in part on the work of the Independent JPEG Group


   libpng Copyright (C) 2004, 2006-2012 Glenn Randers-Pehrson.
   zlib Copyright (C) 1995-2012 Jean-loup Gailly and Mark Adler.


   libtiff Copyright (c) 1988-1997 Sam Leffler
   libtiff Copyright (c) 1991-1997 Silicon Graphics, Inc.

   Permission to use, copy, modify, distribute, and sell this software and
   its documentation for any purpose is hereby granted without fee, provided
   that (i) the above copyright notices and this permission notice appear in
   all copies of the software and related documentation, and (ii) the names of
   Sam Leffler and Silicon Graphics may not be used in any advertising or
   publicity relating to the software without the specific, prior written
   permission of Sam Leffler and Silicon Graphics.

   THE SOFTWARE IS PROVIDED "AS-IS" AND WITHOUT WARRANTY OF ANY KIND,
   EXPRESS, IMPLIED OR OTHERWISE, INCLUDING WITHOUT LIMITATION, ANY
   WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.

   IN NO EVENT SHALL SAM LEFFLER OR SILICON GRAPHICS BE LIABLE FOR
   ANY SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY KIND,
   OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
   WHETHER OR NOT ADVISED OF THE POSSIBILITY OF DAMAGE, AND ON ANY THEORY OF
   LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
   OF THIS SOFTWARE.


   libogg Copyright (C) 2002-2009 Xiph.org Foundation

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:

   - Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

   - Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

   - Neither the name of the Xiph.org Foundation nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE FOUNDATION
   OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


   Opus audio codec
   Copyright 2001-2011 Xiph.Org, Skype Limited, Octasic,
    Jean-Marc Valin, Timothy B. Terriberry,
    CSIRO, Gregory Maxwell, Mark Borgerding,
    Erik de Castro Lopo

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:

   - Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

   - Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

   - Neither the name of Internet Society, IETF or IETF Trust, nor the
   names of specific contributors, may be used to endorse or promote
   products derived from this software without specific prior written
   permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER
   OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


   Opusfile
   Copyright (c) 1994-2013 Xiph.Org Foundation and contributors

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:

   - Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

   - Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

   - Neither the name of the Xiph.Org Foundation nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE FOUNDATION
   OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


   Mersenne Twister
   Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:

   1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

   2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

   3. The name of the author may not be used to endorse or promote products
   derived from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
   IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
   OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
   IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
   INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
   NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
   THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


   Bullet Copyright (c) 2003-2006 Erwin Coumans.

</details>
