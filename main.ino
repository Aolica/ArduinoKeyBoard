#include <Wire.h>
#include "Adafruit_MCP23017.h"
#include "header.h"
#define KEYS 24
#define PUSH_TRUE LOW
#define PUSH_FALSE HIGH
Adafruit_MCP23017 mcp1, mcp2;
byte octave = 3; //右端のCのオクターブ
byte semitone = 0; //はじめのkey(key=C)
int buf;
struct keystat keykeystatus[KEYS];

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  mcp1.begin(int(0x00));
  mcp2.begin(0x01);
  for (int i = 0; i <= 15; i++) {
    mcp1.pinMode(i, INPUT);
    mcp1.pullUp(i,HIGH);
    mcp2.pinMode(i, INPUT);
    mcp2.pullUp(i,HIGH);
  }
  for (int i = 0; i < KEYS; i++) {  //キーのステータスの初期化
    keykeystatus[i].ispushed = PUSH_FALSE;
  }
}

// the loop routine runs over and over again forever:
void loop() {
  //////////////////////////////////////////////////////////////////////////////////////////
  //ローカルな設定(octave,semitone)の読み込み処理
  //////////////////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////////////////
  //キーボードの読み込み処理
  //////////////////////////////////////////////////////////////////////////////////////////
  for (int i = 0; i < KEYS; i++) {
    if (i <= 15) {
      buf = mcp1.digitalRead(i);                 //mcp1から読み込む
    } else {
      buf = mcp2.digitalRead(i - 16);            //mcp1をすべて読みこんだらmcp2を読み込む
    }
    if (buf != keykeystatus[i].ispushed) {    //ボタンステータスが変わったら
      if (keykeystatus[i].ispushed  != PUSH_TRUE) {  //押されたときの処理
        keykeystatus[i].ispushed = PUSH_TRUE;
        //keykeystatus[i].semitone = semitone;
        keykeystatus[i].octave   = octave + (byte)(int)((i + semitone) / 12.0);      //オクターブの設定
        keykeystatus[i].key      = (i + semitone) % 12;
        SendKeyData(1,keykeystatus[i]);
      } else {                                 //離されたときの処理
        keykeystatus[i].ispushed = PUSH_FALSE;
        SendKeyData(0,keykeystatus[i]);
      }
    }
  }
  //////////////////////////////////////////////////////////////////////////////////////////
  //つまみの読み込み処理
  //////////////////////////////////////////////////////////////////////////////////////////

  // delay(1);        // delay in between reads for stability
}
