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

void viewScript(){
  int i = 0;
  if(server.hasArg("n")){
    File f = SPIFFS.open("/"+server.arg("n"), "r");
    
    server.sendHeader("Content-Length", (String)f.size());
    server.send(200, "text/plain", "");
    
    while(f.available() && i<sizeof(data_websiteBuffer)){
      data_websiteBuffer[i] = f.read();
      i++;
      if(i >= sizeof(data_websiteBuffer)){
        server.sendContent_P(data_websiteBuffer, i);
        i = 0;
      }
    }
  }
  if(i > 0) server.sendContent_P(data_websiteBuffer, i);
}

//format bytes
String formatBytes(size_t bytes){
  if (bytes < 1024){
    return String(bytes)+" B";
  } else if(bytes < (1024 * 1024)){
    return String(bytes/1024.0)+" KB";
  } else if(bytes < (1024 * 1024 * 1024)){
    return String(bytes/1024.0/1024.0)+" MB";
  } else {
    return String(bytes/1024.0/1024.0/1024.0)+" GB";
  }
}

void getScriptList() {
  Dir dir = SPIFFS.openDir("");
  String output;
  output += "{";
  output += "\"totalBytes\":"+(String)fs_info.totalBytes+",";
  output += "\"usedBytes\":"+(String)fs_info.usedBytes+",";
  output += "\"list\":[ ";
  while(dir.next()){
    File entry = dir.openFile("r");
    String filename = String(entry.name()).substring(1);
    output += '{';
    output += "\"n\":\""+filename+"\",";  //name
    output += "\"s\":\""+formatBytes(entry.size())+"\"";          //size
    output += "},";
    entry.close();
  }
  output = output.substring(0, output.length()-1);
  output += "]}";
  server.send(200, "text/json", output);
}

void setup() {

  EEPROM.begin(4096);
  
  WiFi.mode(WIFI_STA);
  WiFi.softAP("pwned","deauther");

  Serial.begin(BAUD_RATE);
  delay(2000);
  Serial.println();

  SPIFFS.begin();
  //SPIFFS.format();
  SPIFFS.info(fs_info);

  server.onNotFound([](){ server.send(404, "text/html", data_getError404()); });
  
  server.on("/upload.html",[](){ server.send(200, "text/html", data_getUploadHTML()); });
  server.on("/style.css",[](){ server.send(200, "text/css", data_getStyleCSS()); });
  server.on("/functions.js",[](){ server.send(200, "text/javascript", data_getFunctionsJS()); });
  server.on("/list.json", getScriptList);
  server.on("/view", viewScript);
  server.on("/",[](){ server.send(200, "text/html", data_getIndexHTML()); });

  //handle upload
  server.on("/upload", HTTP_POST, [](){
    server.sendHeader("Location", "/", true);
    server.send ( 302, "text/plain", "");
  },[](){
    HTTPUpload& upload = server.upload();
    if(upload.totalSize > 0){
      File fsUploadFile;
      
      String filename = upload.filename;
      if(!filename.startsWith("/")) filename = "/"+filename;
        
      Serial.println("uploading: "+filename+" ("+ (String)upload.totalSize+ "b)...");
        
      fsUploadFile = SPIFFS.open(filename, "a");
      
      fsUploadFile.write(upload.buf, upload.currentSize);
      //Serial.write(upload.buf, upload.currentSize);
      
      fsUploadFile.close();
      Serial.println("upload done!");
      yield();
    }
  });
    
  server.begin();

  Serial.println("started");
}
  
void loop() {
  server.handleClient();
}
