#ifndef WS_H
#define WS_H

#include <WebSocketsServer.h>

WebSocketsServer ws_server(81);

void handle_ws(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {

  switch (type) {
    case WStype_DISCONNECTED:
      #if DEBUG == 1
      Serial.printf("[%u] Disconnected!\n", num);
      #endif
      break;
    case WStype_CONNECTED: {
        IPAddress ip = ws_server.remoteIP(num);
        Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);

        // Send message to client
        ws_server.sendTXT(num, "HAPPY DRIVING");
      }
      break;
    case WStype_TEXT:
      extern void dieu_khien(String lenh_dieu_khien);
      String lenh_dieu_khien = (char *)payload;
      dieu_khien(lenh_dieu_khien);
      break;
  }

}

void init_websocket() {
  ws_server.begin();
  ws_server.onEvent(handle_ws);
}

#endif // WS_H
