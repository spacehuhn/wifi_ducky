#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <FS.h>
#include <EEPROM.h>
#include "data.h"

#define BAUD_RATE 115200

ESP8266WebServer server(80);
FSInfo fs_info;
extern char* data_getStyleCSS();
extern char* data_getError404();
extern char* data_getIndexHTML();
extern char* data_getUploadHTML();

void setup() {

  EEPROM.begin(4096);
  
  WiFi.mode(WIFI_STA);
  WiFi.softAP("pwned","deauther");

  Serial.begin(BAUD_RATE);
  delay(2000);
  Serial.println();
  Serial.println();

  SPIFFS.begin();
  SPIFFS.info(fs_info);

  server.onNotFound([](){ server.send(404, "text/html", data_getError404()); });
  
  server.on("/upload.html",[](){ server.send(200, "text/html", data_getUploadHTML()); });
  server.on("/style.css",[](){ server.send(200, "text/css", data_getStyleCSS()); });
  server.on("/functions.js",[](){ server.send(200, "text/javascript", data_getFunctionsJS()); });
  server.on("/list.json", getScriptList);
  server.on("/",[](){ server.send(200, "text/html", data_getIndexHTML()); });
  server.on("/index.html",[](){ server.send(200, "text/html", data_getIndexHTML()); });

  //handle upload
  server.on("/upload", HTTP_POST, [](){
    server.sendHeader("Location", "/", true);
    server.send ( 302, "text/plain", "");
  },[](){
    HTTPUpload& upload = server.upload();
    File fsUploadFile;
    
    //starting upload
    if(upload.status == UPLOAD_FILE_START){
      Serial.println("uploading: "+upload.filename+"...");
      fsUploadFile = SPIFFS.open(upload.filename, "w+");
    }
    
    //while uploading
    else if(upload.status == UPLOAD_FILE_WRITE){
      fsUploadFile.write(upload.buf, upload.currentSize);
    } 

    //finishing upload
    else if(upload.status == UPLOAD_FILE_END){
      fsUploadFile.close();
      Serial.println("upload done!");
    }
     
    yield();
     
  });
    
  server.begin();

  Serial.println("started");
}

void getScriptList() {
  Dir dir = SPIFFS.openDir("");
  String output;
  output += "{";
  output += "\"totalBytes\":"+(String)fs_info.totalBytes+",";
  output += "\"usedBytes\":"+(String)fs_info.usedBytes+",";
  output = "\"list\":[";
  while(dir.next()){
    File entry = dir.openFile("r");
    output += '{';
    output += "\"n\":\""+(String)entry.name()+"\",";
    output += "\"s\":"+(String)entry.size()+",";
    output += "},";
    entry.close();
  }
  output = output.substring(-1);
  output += "]}";
  server.send(200, "text/json", output);
    
}
  
void loop() {
  server.handleClient();
}
