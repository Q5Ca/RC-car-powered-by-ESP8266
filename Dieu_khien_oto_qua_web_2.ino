#include "thu_vien_chinh.h"
#include "config.h"



// Cai dat wifi
const char *connect_ssid     = "vvvvv";
const char *connect_password = "lozlozloz";
const char *ssid     = "Control_Car";
const char *password = "dieukhienxe";

void setup() {
  /* Nhung thu can khoi dong:
   *  - Serial
   *  - Software serial hoac khoi dong dieu khien
   *  - wifi
   *  - spiffs
   *  - webserver
   */
   
  Serial.begin(115200);
  Serial.println();
  Serial.println();
//  --------------------------------

//   Khoi dong software serial
//  arduino.begin(9600);
//  #ifdef DEBUG
//  Serial.println("software serial started");
//  #endif
//  -----------------------------


  // Khoi dong dieu khien
  pinMode(c11, OUTPUT);
  pinMode(c12, OUTPUT);
  pinMode(c21, OUTPUT);
  pinMode(c22, OUTPUT);
//  ------------------------------

//  Khoi dong wifi
  #ifdef phat_wifi
    #ifdef DEBUG
    Serial.println("Configuring access point...");
    #endif
    WiFi.softAP(ssid, password);
    #ifdef DEBUG
    Serial.println("Wifi hotspot started");
    Serial.print("Ready! IP address: ");
    Serial.println(WiFi.softAPIP());
    Serial.println();
    #endif
  #endif
  
  #ifndef phat_wifi
    Serial.printf("Connecting to %s\n", connect_ssid);
    if (String(WiFi.SSID()) != String(connect_ssid)) {
      WiFi.mode(WIFI_STA);
      WiFi.begin(connect_ssid, connect_password);
    }
  
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("");
    Serial.print("Ready! IP address: ");
    Serial.println(WiFi.localIP());
    Serial.println();
  #endif
     
//  --------------------------

  //Khoi dong SPIFFS
  SPIFFS.begin();
  #ifdef DEBUG
  Serial.println("SPIFFS started");
  hien_cac_file();
  #endif
//  ----------------------------
  


  // Khoi dong web server
  web_handle();
  da_vao=0;
  server.begin();
  #ifdef DEBUG
  Serial.println("HTTP server started");
  #endif
}

void loop() {
  server.handleClient();
 
}
