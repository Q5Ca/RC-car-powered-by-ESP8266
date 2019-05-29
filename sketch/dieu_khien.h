#ifndef DIEU_KHIEN_H
#define DIEU_KHIEN_H


#include "config.h"
#include "ws.h"

//  Neu dung arduino thi moi bien dich
  #if dung_arduino == 1
    #include <SoftwareSerial.h>
    #define RX D1
    #define TX D2
    SoftwareSerial arduino(RX, TX);

    void init_arduino(){
      arduino.begin(9600);
    }
    
    #define delay_time 20
    void dieu_khien(String lenh ){
      delay(delay_time);
      arduino.println(lenh);
      #if DEBUG == 1
      Serial.println("da gui lenh: "+lenh);
      #endif
//      -----------------------------------------

      
      if (lenh == "tu_lai") ws_server.sendTXT(0, "da_tu_lai");
      else if (lenh == "dung_tu_lai") ws_server.sendTXT(0, "da_dung_tu_lai");
    }
  #endif  // dung_arduino
//  -------------------------------------
  #if dung_arduino == 0
    // Cac ham dieu khien xe di chuyen
    #define c11 D0
    #define c12 D1
    #define c21 D2
    #define c22 D3
    
    void dung() {
      #if DEBUG == 1
      Serial.println("Xe dung");
      #endif
      digitalWrite(c11, LOW);
      digitalWrite(c12, LOW);
      digitalWrite(c21, LOW);
      digitalWrite(c22, LOW);
    }
    void tien() {
      #if DEBUG == 1
      Serial.println("Xe tien");
      #endif
      digitalWrite(c11, HIGH);
      digitalWrite(c12, LOW);
      digitalWrite(c21, HIGH);
      digitalWrite(c22, LOW);
    }
    void lui() {
      #if DEBUG == 1
      Serial.println("Xe lui");
      #endif
      digitalWrite(c11, LOW);
      digitalWrite(c12, HIGH);
      digitalWrite(c21, LOW);
      digitalWrite(c22, HIGH);
    }
    void xoay_trai() {
      #if DEBUG == 1
      Serial.println("Xe xoay trai");
      #endif
      digitalWrite(c11, HIGH);
      digitalWrite(c12, LOW);
      digitalWrite(c21, LOW);
      digitalWrite(c22, HIGH);
    }
    void xoay_phai() {
      #if DEBUG == 1
      Serial.println("Xe xoay phai");
      #endif
      digitalWrite(c11, LOW);
      digitalWrite(c12, HIGH);
      digitalWrite(c21, HIGH);
      digitalWrite(c22, LOW);
    }
    void re_trai() {
      xoay_trai();
      delay(100);
      dung();
    }
    void re_phai() {
      xoay_phai();
      delay(100);
      dung();
    }
    void dieu_khien(String lenh_dieu_khien){
      if (lenh_dieu_khien == "tien") tien();
      else if (lenh_dieu_khien == "lui") lui();
      else if (lenh_dieu_khien == "re_trai") re_trai();
      else if (lenh_dieu_khien == "re_phai") re_phai();
      else if (lenh_dieu_khien == "dung") dung();
      else if (lenh_dieu_khien == "xoay_trai") xoay_trai();
      else if (lenh_dieu_khien == "xoay_phai") xoay_phai();
    }
  #endif  // not dung_arduino
//--------------------------------------------

#endif // DIEU_KHIEN_H


