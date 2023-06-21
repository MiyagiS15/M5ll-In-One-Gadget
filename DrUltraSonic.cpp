#include "DrUltraSonic.h"
#include"AppControl.h"
#include"Arduino.h"
#include "M5All-In-One-Gadget.h"

DrUltraSonic::DrUltraSonic(int echo_pin, int trig_pin){
m_echo_pin = echo_pin;
m_trig_pin = trig_pin;
}

double measureReturnTime(){
    {
  double t; //ｔはμ秒単位
  double distance = -1;
  
  /*超音波の発生*/
  digitalWrite(TRIG_PIN,HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN,LOW);

  /*返ってくるまでの時間測定*/
  t = pulseIn(ECHO_PIN,HIGH); //ECHOピンのパルスがHIGHになった時間を変数tに格納
  if(t >= 0){
    distance = (340.0/1000000) * t * 0.5 * 100;//m→cmなので100倍する  
    Serial.print(distance);
    Serial.println("[cm]");
  }
  return distance;
}
}