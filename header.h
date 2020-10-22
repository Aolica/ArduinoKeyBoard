#include <Arduino.h>

struct keystat {     //押されたときの情報を保持するための構造体。
  int ispushed; //PUSH_TRUE:pushed
  //byte semitone //value:0-11 (0:key=C)
  byte octave; //value:0-10
  byte key;  //value:0-11
};

bool IsSharp(byte key) {
  if ((key  >= 6 && key % 2 == 0) || ( key  < 5 && key % 2 != 0)) {
    return true;
  }
  return false;
}
char KeyNumToAlph(byte num) {
  switch ((num )) {
    case 0:
    case 1:
      return ('2');
      break;
    case 2:
    case 3:
      return ('3');
      break;
    case 4:
      return ('4');
      break;
    case 5:
    case 6:
      return ('5');
      break;
    case 7:
    case 8:
      return ('6');
      break;
    case 9:
    case 10:
      return ('0');
      break;
    case 11:
      return ('1');
      break;
  }
}

void SendKeyData(int type,struct keystat data) {
  char datas[10];
  /*
  if(data.key + data.semitone > 12){
    data.octave + 1;
  }*/
  sprintf(datas,"%d%c%u%u%u",1,KeyNumToAlph(data.key),IsSharp(data.key),data.octave,type);
  Serial.print(datas);
  
  /*
  Serial.write(1);
  Serial.write(KeyNumToAlph(data.key));
  Serial.write(IsSharp(data.key));
  if (data.key + data.semitone > 12) {
    Serial.write((data.octave + 1));
  } else {
    Serial.write(data.octave);
  }
  Serial.write(data.ispushed);
  */
}

void SendKnobData(int rdirection,int id){
  char datas[5];
  sprintf(datas,"%d%d%d",2,id,rdirection);
  Serial.print(datas);
}

void SendOtherData(int num){
  char datas[3];
  switch(num){
    case 0:
      sprintf(datas,"%d",3);
      break;
    case 1:
      sprintf(datas,"%d",4);
      break;
    default:
      return;
      break;
  }
  Serial.print(datas);
}
