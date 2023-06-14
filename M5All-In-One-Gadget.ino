#include "M5All-In-One-Gadget.h"
#include <M5Stack.h>
#include <SD.h>

#include "AppControl.h"

AppControl apc;//AppControlクラスをインスタンス化

// BUTTON A（左） の割込み関数
void buttonA_isr()  
{
  //  Serial.println("A interrupt : State[" + String(apc.getState()) + "] Action[" + String(apc.getAction()) + "]");//
    apc.setBtnAFlg(true);//AppControl.cppのvoid AppControl::setBtnAFlg(bool flg)に引数trueを渡してメンバ m_flag_btnA_is_pressed = flg;をtrue（ボタンが押された状態）にしている。
}

// BUTTON B（真ん中） の割込み関数
void buttonB_isr()
{
   // Serial.println("B interrupt : State[" + String(apc.getState()) + "] Action[" + String(apc.getAction()) + "]");
    apc.setBtnBFlg(true);
}

// BUTTON C（右） の割込み関数
void buttonC_isr()
{
    //Serial.println("C interrupt : State[" + String(apc.getState()) + "] Action[" + String(apc.getAction()) + "]");
    apc.setBtnCFlg(true);
}

void setup()
{
    M5.begin();
    Serial.begin(115200);
    // 割込みピンをINPUTに設定
    pinMode(digitalPinToInterrupt(BTN_A_GPIO), INPUT);
    pinMode(digitalPinToInterrupt(BTN_B_GPIO), INPUT);
    pinMode(digitalPinToInterrupt(BTN_C_GPIO), INPUT);
   

    // 割込み設定
    attachInterrupt(digitalPinToInterrupt(BTN_A_GPIO), buttonA_isr, FALLING);//ボタンの割り込み設定　ボタンを押すとbuttonA_isr関数の中身を呼び出して動かす
    attachInterrupt(digitalPinToInterrupt(BTN_B_GPIO), buttonB_isr, FALLING);//ボタンの割り込み設定
    attachInterrupt(digitalPinToInterrupt(BTN_C_GPIO), buttonC_isr, FALLING);//ボタンの割り込み設定
}

void loop()
{
    apc.controlApplication();//7行目でインスタンス化したAppControl.cppのvoid AppControl::controlApplication()でループを回している
}
