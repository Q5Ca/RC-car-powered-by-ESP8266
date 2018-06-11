#ifndef THU_VIEN_CHINH_H
#define THU_VIEN_CHINH_H

#include <ESP8266WiFi.h>
//#include <WiFiClient.h>       ?????
#include <ESP8266WebServer.h>


#include "giao_tiep_voi_arduino.h"
#include "thu_muc_va_files.h"`
#include "config.h"

//----------------------------

// Cac ham dieu khien xe di chuyen
#define c11 D0
#define c12 D1
#define c21 D2
#define c22 D3

void dung() {
  #ifdef DEBUG
  Serial.println("Xe dung");
  #endif
  digitalWrite(c11, LOW);
  digitalWrite(c12, LOW);
  digitalWrite(c21, LOW);
  digitalWrite(c22, LOW);
}
void tien() {
  #ifdef DEBUG
  Serial.println("Xe tien");
  #endif
  digitalWrite(c11, HIGH);
  digitalWrite(c12, LOW);
  digitalWrite(c21, HIGH);
  digitalWrite(c22, LOW);
}
void lui() {
  #ifdef DEBUG
  Serial.println("Xe lui");
  #endif
  digitalWrite(c11, LOW);
  digitalWrite(c12, HIGH);
  digitalWrite(c21, LOW);
  digitalWrite(c22, HIGH);
}
void xoay_trai() {
  #ifdef DEBUG
  Serial.println("Xe xoay trai");
  #endif
  digitalWrite(c11, HIGH);
  digitalWrite(c12, LOW);
  digitalWrite(c21, LOW);
  digitalWrite(c22, HIGH);
}
void xoay_phai() {
  #ifdef DEBUG
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

//------------------------------------------------


// Cac ham webserver
ESP8266WebServer server(80);   // Khoi tao web server

void handleControl() {
  if (!server.hasArg("dieu_khien")) {
    #ifdef DEBUG
    Serial.println("BAG ARGS");
    #endif
    return;
  }

  String lenh_dieu_khien = server.arg("dieu_khien");
  if (lenh_dieu_khien == "tien") tien();
  else if (lenh_dieu_khien == "lui") lui();
  else if (lenh_dieu_khien == "re_trai") re_trai();
  else if (lenh_dieu_khien == "re_phai") re_phai();
  else if (lenh_dieu_khien == "dung") dung();
  else if (lenh_dieu_khien == "xoay_trai") xoay_trai();
  else if (lenh_dieu_khien == "xoay_phai") xoay_phai();
}

int da_vao;
void handle_vaora() {
  String arg = server.arg("cua");
  if (arg == "vao") {
    if (da_vao == 0) {
      #ifdef DEBUG
      Serial.println("Da vao");
      #endif
      handleFileRead("/control.html");
      da_vao = 1;
    }
    else if (da_vao == 1) {
      handleFileRead("/da_co_nguoi.html");
    }
  }
  else if (arg == "ra") {
    #ifdef DEBUG
    Serial.println("Da ra");
    #endif
    handleFileRead("/cua.html");
    da_vao = 0;
  }
}

void web_handle() {
  server.on("/", HTTP_GET, [] () {
    handleFileRead("/cua.html");
  } );
  server.on("/handle_control", HTTP_GET, [] () {
    server.send(200, "text/plain", " OK");
    handleControl();
  });
  server.on("/handle_control", HTTP_POST,[](){
    handle_vaora();
  });
  server.on("/control.html", HTTP_GET, [] () {
    server.send(404, "text/html", "Tinh hack t a ???");
  }); 
  // Xu li file can load
  server.onNotFound ([] {
    if (!handleFileRead(server.uri())) {
      server.send(404, "text/plain", "404:File not found");
    }
  });

}

#endif
