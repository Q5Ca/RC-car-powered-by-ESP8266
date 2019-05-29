#include "thu_vien_chinh.h"
#include "config.h"

void setup() {
  /* Initialize
   *  - Serial
   *  - Software serial 
   *  - wifi
   *  - spiffs
   *  - webserver
   */
   
  Serial.begin(115200);
  Serial.println();
  Serial.println();
//  ------------------------------------------------------------------


// Init software serial to communicate with arduino uno
  #if dung_arduino == 1
    init_arduino();
    #if DEBUG == 1
    Serial.println("software serial started");
    #endif
   #endif 

// Not use uno
  #if dung_arduino == 0
    pinMode(c11, OUTPUT);
    pinMode(c12, OUTPUT);
    pinMode(c21, OUTPUT);
    pinMode(c22, OUTPUT);
  #endif  
//  ------------------------------------------------------------------


//  Init wifi
  #if phat_wifi == 1
    #if DEBUG == 1
    Serial.println("Configuring access point...");
    #endif
    WiFi.softAP(ssid, password);
    #if DEBUG == 1
    Serial.println("Wifi hotspot started");
    Serial.print("Ready! IP address: ");
    Serial.println(WiFi.softAPIP());
    Serial.println();
    #endif
  #endif
  
  #if phat_wifi == 1
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
//  ------------------------------------------------------------------


  // Init SPIFFS
  SPIFFS.begin();
  #if DEBUG == 1
  Serial.println("SPIFFS started");
  hien_cac_file();
  #endif
//  ------------------------------------------------------------------
  



  // Khoi dong web server
  init_webserver();
  #if DEBUG == 1
  Serial.println("web server started");
  #endif
//  ------------------------------------------------------------------


//  Init websocket server
  init_websocket();
  #if DEBUG == 1
  Serial.println("websocket server started");
  #endif  
}

void loop() {
  // Hande HTTP requests and websocket
  server.handleClient();
  ws_server.loop();
}
