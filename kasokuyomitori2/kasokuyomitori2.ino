#include <SPI.h>                          //spi通信のライブラリを呼び出す。

#define cs 10                             //cs(チップセレクト)を10ピンに定義する

void setup() {
  pinMode(cs,OUTPUT);                     //spiライブラリの関数を使いspi通信の仕様を決定する
  SPI.setBitOrder(MSBFIRST);              //最上位ビットから転送する
  SPI.setClockDivider(SPI_CLOCK_DIV4);    //クロック分周比を設定する
  SPI.setDataMode(SPI_MODE3);             //転送モードを設定する
  SPI.begin();                            //spiを初期化する
  Serial.begin(115200);                   //データ転送レートを指定する
  delay(100);
}
byte yomitori(byte address) {             //SPI通信でデータを読み取る関数yomitoriを定義(アドレスは16進数)
  digitalWrite(cs, LOW);                  //spi通信を始める合図
  SPI.transfer(address | 0x80);           //ほしいデータの入っているアドレスを指定する
  byte data = SPI.transfer(0);            //byte型の関数dataにアドレスの後に続くデータ1バイトを格納する
  digitalWrite(cs, HIGH);                 //spi通信を終える合図
  return data;                            //yomitoriにdataの値を返す
}

void loop(){
  byte datax1 = yomitori(0x3B);           //datax1にx方向加速度のデータ上位8ビットを格納
  byte datax2 = yomitori(0x3C);           //datax2にx方向加速度のデータ下位8ビットを格納
  int  dataX = datax1 <<8 | datax2;       //datax1の値を8ビット左シフトしdatax2の値と論理和をとってdataXに格納
  /*if(dataX & 0x80){
    dataX = (dataX - 65535)/17700;                //最上位のビットが符号ビットのためそれを反映する
  }
  else{
    dataX=dataX/17700;
  }*/
  byte datay1 = yomitori(0x3D);           //Y,Z方向加速度についても同様の処理を行う
  byte datay2 = yomitori(0x3E);           
  int  dataY = datay1 <<8 | datay2;
  /*if(dataY & 0x80){
    dataY = (dataY - 65535)/17700;   
  } 
  else{
    dataY=dataY/17700;
  }*/
  byte dataz1 = yomitori(0x3F);           
  byte dataz2 = yomitori(0x40);           
  int  dataZ = dataz1 <<8 | dataz2;
 /*if(dataZ & 0x80){
    dataZ = (dataZ - 65535)/17700;   
  }
  else{
    dataZ=dataZ/17700;
  }
  */
  dataX=dataX/170;
  dataY=dataY/170;
  dataZ=dataZ/170;
    Serial.print("          x            ");
    Serial.print(dataX);
    Serial.print("          y            ");
    Serial.print(dataY);
    Serial.print("          z            ");
    Serial.println(dataZ);
  }
