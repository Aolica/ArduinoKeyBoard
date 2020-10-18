#include <Arduino.h>

struct stat {     //押されたときの情報を保持するための構造体。
  int ispushed; //PUSH_TRUE:pushed
  //byte semitone //value:0-11 (0:key=C)
  byte octave; //value:0-10
  byte key;  //value:0-11
};

bool IsSharp(byte key) {
  if ((key  > 6 && key % 2 != 0 ) || ( key  < 5 && key % 2 == 0)) {
    return true;
  }
  return false;
}
char KeyNumToAlph(byte num) {
  switch ((num )) {
    case 0:
    case 1:
      return ('C');
      break;
    case 2:
    case 3:
      return ('D');
      break;
    case 4:
      return ('E');
      break;
    case 5:
    case 6:
      return ('F');
      break;
    case 7:
    case 8:
      return ('G');
      break;
    case 9:
    case 10:
      return ('A');
      break;
    case 11:
      return ('B');
      break;
  }
}

void SendKeyData(int type,struct stat data) {
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
