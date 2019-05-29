#ifndef THU_VIEN_CHINH_H
#define THU_VIEN_CHINH_H

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>


#include "dieu_khien.h"
#include "thu_muc_va_files.h"`
#include "config.h"
#include "ws.h"




ESP8266WebServer server(80);   

int da_vao;
void handle_vaora() {
  String arg = server.arg("cua");
  if (arg == "vao") {
    if (da_vao == 0) {
      #if DEBUG == 1
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
    #if DEBUG == 1
    Serial.println("Da ra");
    #endif
    handleFileRead("/cua.html");
    da_vao = 0;
  }
}

void init_webserver() {
  server.on("/", HTTP_GET, [] () {
    handleFileRead("/cua.html");
  } );
  server.on("/handle_control", HTTP_POST,[](){
    handle_vaora();
  });
  server.on("/control.html", HTTP_GET, [] () {
    server.send(404, "text/html", "Tinh hack t a ???");
  }); 
  // Serve static files
  server.onNotFound ([] {
    if (!handleFileRead(server.uri())) {
      server.send(404, "text/plain", "404:File not found");
    }
  });
  
  
  server.begin();
  da_vao = 0;
}
  
#endif      // THU_VIEN_CHINH_H
