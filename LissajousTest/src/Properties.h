/**
 * Copyright (c) 2014 Tatsuya Ogusu
 * This software is released under the MIT License.
 * http://opensource.org/licenses/mit-license.php
 */
#pragma once

//====================
// constrain
// ここに定数やメモを書く
//====================

//#define TEST_2CH ///< Defineしてたら2chローカル起動テスト
//#define AUDIO_INPUT_TO_DRAW ///< 音声入力描画に反映（作曲時ON, 本番はOFF）

//---------------------------------------------

static const int BUFFER_SIZE = 512;

static const int SAMPLE_RATE = 44100;
//static const int SAMPLE_RATE = 48000;
//static const int SAMPLE_RATE = 96000;

#ifndef TEST_2CH

static const int DEVICE_ID = 3; ///<-------- Aidio Device ID

#ifdef AUDIO_INPUT_TO_DRAW
// 作曲時
static const int INPUT_CHANNELS  = 4 + 4;
static const int OUTPUT_CHANNELS = 4;
static const int INPUT_CH_OFFSET = 4; ///< 1~4ch : Audio Output
static const int NUM_SAMPLES = INPUT_CHANNELS - INPUT_CH_OFFSET; ///< 描画に使用するサンプル配列数
#else
// 本番
static const int INPUT_CHANNELS  = 0;
static const int OUTPUT_CHANNELS = 4 + 4;
static const int INPUT_CH_OFFSET = 4; ///< 1~4ch : Audio Output
static const int NUM_SAMPLES = OUTPUT_CHANNELS - INPUT_CH_OFFSET; ///< 描画に使用するサンプル配列数
#endif

#endif



#ifdef TEST_2CH

// ２chテスト時
static const int DEVICE_ID = 1;

static const int INPUT_CHANNELS  = 0;
static const int OUTPUT_CHANNELS = 8;

static const int INPUT_CH_OFFSET = 4;
static const int NUM_SAMPLES = OUTPUT_CHANNELS - INPUT_CH_OFFSET; ///< 描画に使用するサンプル配列数

#endif


static const int NUM_2D_POINTS = floor(NUM_SAMPLES / 2);
static const int NUM_3D_POINTS = floor(NUM_SAMPLES / 3);

static const bool INIT_DEBUG_MODE = true;

//
// utils
//---------------------------------------------

// マウスポインタ座標を画面サイズで0-1正規化した値を返す
#define debugMouseX ((float)ofGetMouseX()/(float)ofGetWidth())
#define debugMouseY ((float)ofGetMouseY()/(float)ofGetHeight())

// aよりbが大きければb-aを返す（変数更新時のリミッター用）
#define	MIN_NORM(a,b) (((a)<(b))?(a):(b-a))

// 画面中心を取得
#define CENTER_X (ofGetWidth()/2)
#define CENTER_Y (ofGetHeight()/2)


// 処理速度の計測
static clock_t start = 0;
#define START_CLOCK (start = clock())
#define GET_CLOCK(comment) (std::cout<<comment<<clock()-start<<std::endl)

