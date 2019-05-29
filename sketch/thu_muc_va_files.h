#ifndef THU_MUC_VA_FILES_H
#define THU_MUC_VA_FILES_H

#include <FS.h>

#include "config.h"

extern ESP8266WebServer server;

#if DEBUG == 1
void hien_cac_file() {  
  Dir dir = SPIFFS.openDir("/");
  while (dir.next()) {
    Serial.printf("FS file: %s, size :%d\n", (dir.fileName()).c_str(), dir.fileSize());
  }
  Serial.println();
}
#endif

String getContentType(String filename){
  if(server.hasArg("download")) return "application/octet-stream";
  else if(filename.endsWith(".htm")) return "text/html";
  else if(filename.endsWith(".html")) return "text/html";
  else if(filename.endsWith(".css")) return "text/css";
  else if(filename.endsWith(".js")) return "application/javascript";
  else if(filename.endsWith(".png")) return "image/png";
  else if(filename.endsWith(".gif")) return "image/gif";
  else if(filename.endsWith(".jpg")) return "image/jpeg";
  else if(filename.endsWith(".ico")) return "image/x-icon";
  else if(filename.endsWith(".xml")) return "text/xml";
  else if(filename.endsWith(".pdf")) return "application/x-pdf";
  else if(filename.endsWith(".zip")) return "application/x-zip";
  else if(filename.endsWith(".gz")) return "application/x-gzip";
  return "text/plain";
}

bool handleFileRead (String path) {
  #if DEBUG == 1
  Serial.print("handle file read: " + path + " ... ");
  #endif
  if (SPIFFS.exists(path)) {
    File file = SPIFFS.open(path, "r");
    #if DEBUG == 1
    Serial.print("Da mo file; ");
    #endif
    
    server.streamFile (file, getContentType(path));
    #if DEBUG == 1
    Serial.print("Da stream file; ");
    #endif
    
    file.close();
    #if DEBUG == 1
    Serial.print("Da dong file; ");
    #endif
    
    #if DEBUG == 1
    Serial.println("done");
    #endif
    
    return true;
  }
  #if DEBUG == 1
  Serial.println("file not found");
  #endif
  return false;
}


#endif
