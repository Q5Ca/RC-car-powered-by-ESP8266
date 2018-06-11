#ifndef GIAO_TIEP_VOI_ARDUINO_H
#define GIAO_TIEP_VOI_ARDUINO_H


#include "config.h"

//  Neu dung arduino thi moi bien dich
  #ifdef dung_arduino
  #include <SoftwareSerial.h>
  #define RX D1
  #define TX D2
  SoftwareSerial arduino(RX, TX);
  
  #define delay_time 20
  void gui_lenh(String lenh ){
    delay(delay_time);
    arduino.println(lenh);
    #ifdef DEBUG
    Serial.println("da gui lenh: "+lenh);
    #endif
  }
  #endif
//  -------------------------------------


#endif


