//Implementação e aplicação
// Hênio Reis
// 18-04-2020
// Canal Maker IoT

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include "soc/soc.h"              
#include "soc/rtc_cntl_reg.h"
#include "esp_camera.h"
#include "html.h"
          
#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27

#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22

const char* ssid     = "....";
const char* password = "...."; 

String resposta_geral="",comando_geral="",comando="",Par1="",Par2="",Par3="",Par4="",Par5="",Par6="",Par7="",Par8="",Par9="";
byte status_recebido=0,status_comando=1,status_string=1,status_interrogacao=0,status_igualdade=0,status_pontvirgula=0;

WiFiServer server(80);

void Running_parametro()
{
     
  if (comando=="Sendphoto") {
    resposta_geral=sendCapturedTelegram(Par1,Par2);
  } 
  else if (comando=="framesize") { 
    sensor_t * s = esp_camera_sensor_get();  
    if (Par1=="QQVGA")
      s->set_framesize(s, FRAMESIZE_QQVGA);
    else if (Par1=="HQVGA")
      s->set_framesize(s, FRAMESIZE_HQVGA);
    else if (Par1=="QVGA")
      s->set_framesize(s, FRAMESIZE_QVGA);
    else if (Par1=="CIF")
      s->set_framesize(s, FRAMESIZE_CIF);
    else if (Par1=="VGA")
      s->set_framesize(s, FRAMESIZE_VGA);  
    else if (Par1=="SVGA")
      s->set_framesize(s, FRAMESIZE_SVGA);
    else if (Par1=="XGA")
      s->set_framesize(s, FRAMESIZE_XGA);
    else if (Par1=="SXGA")
      s->set_framesize(s, FRAMESIZE_SXGA);
    else if (Par1=="UXGA")
      s->set_framesize(s, FRAMESIZE_UXGA);           
    else 
      s->set_framesize(s, FRAMESIZE_QVGA);     
  } 
  else {
    resposta_geral="Comando não definido!.";
  }
  if (resposta_geral=="") resposta_geral=comando_geral;  
}

void setup() {
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println();

 
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
 
  config.pixel_format = PIXFORMAT_JPEG;

  if(psramFound()){
    config.frame_size = FRAMESIZE_UXGA;
    config.jpeg_quality = 10; 
    config.fb_count = 2;
  } else {
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 12;  
    config.fb_count = 1;
  }
  

  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    delay(1000);
    ESP.restart();
  }


  sensor_t * s = esp_camera_sensor_get();
  s->set_framesize(s, FRAMESIZE_QVGA); 

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("Camera Ready! Use 'http://");
  Serial.print(WiFi.localIP());
  Serial.println("' to connect");

  server.begin();         
}

void loop() {
  resposta_geral="";comando_geral="";comando="";Par1="";Par2="";Par3="";Par4="";Par5="";Par6="";Par7="";Par8="";Par9="";
  status_recebido=0,status_comando=1,status_string=1,status_interrogacao=0,status_igualdade=0,status_pontvirgula=0;
  
   WiFiClient client = server.available();

  if (client) { 
    String currentLine = "";
    camera_fb_t * fb = NULL;
    size_t fb_len   = 0; 

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();             
        
        request_url(c);   
                
        if (c == '\n') {
          if (currentLine.length() == 0) {    
            if (cmd=="Stream") {
              
              fb = esp_camera_fb_get();
              if(!fb) {
                Serial.println("Camera capture failed");
                delay(1000);
                ESP.restart();
              }
              
               fb_len = fb->len;

              client.println("HTTP/1.1 200 OK");
              client.println("Access-Control-Allow-Origin: *");              
              client.println("Access-Control-Allow-Headers: Origin, X-Requested-With, Content-Type, Accept");
              client.println("Access-Control-Allow-Methods: GET,POST,PUT,DELETE,OPTIONS");
              client.println("Content-Type: image/jpeg");
              client.println("Content-Disposition: form-data; name=\"imageFile\"; filename=\"picture.jpg\""); 
              client.println("Content-Length: " + String(fb->len));             
              client.println("Connection: close");
              client.println();
            
                
              client.write((const char *)fb->buf, fb->len);
                
              
              client.println();
              esp_camera_fb_return(fb);
                           
            }
            else {
              
              client.println("HTTP/1.1 200 OK");
              client.println("Access-Control-Allow-Headers: Origin, X-Requested-With, Content-Type, Accept");
              client.println("Access-Control-Allow-Methods: GET,POST,PUT,DELETE,OPTIONS");
              client.println("Content-Type: text/html; charset=utf-8");
              client.println("Access-Control-Allow-Origin: *");
              client.println("Connection: close");
              client.println();
              
              String Data_html="";
              if (comando!="")
                Data_html = resposta_geral;
              else {
                Data_html = String((const char *)INDEX_HTML);
              }
              
              int Indice;
              for (Indice = 0; Indice < Data.length(); Indice = Indice+1000) {
                client.print(Data_html.substring(Indice, Indice+1000));
              } 
              client.println();
            }
                        
            resposta_geral="";
            break;
          } else {
            currentLine = "";
          }
        } 
        else if (c != '\r') {
          currentLine += c;
        }

        if ((currentLine.indexOf("/?")!=-1)&&(currentLine.indexOf(" HTTP")!=-1)) {
          if (comando_geral.indexOf("stop")!=-1) {  
            client.println();
            client.println();
            client.stop();
          }
          currentLine="";
          resposta_geral="";
          Running_parametro();
        }
      }
    }
    delay(1);
    client.stop();
  }
}

String sendCapturedTelegram(String token, String chat_id) {
  const char* url = "api.telegram.org";
  String obtertudo="", corpo = "";

  camera_fb_t * fb = NULL;
  fb = esp_camera_fb_get();  
  if(!fb) {
    Serial.println("Camera capture failed");
    delay(1000);
    ESP.restart();
    return "Camera capture failed";
  }  
  
 
  WiFiClientSecure client;
  
  if (client.connect(url, 443)) {
    Serial.println("Conexão com sucesso!");
    
    String head_corpo = "--Brasil\r\nContent-Disposition: form-data; name=\"chat_id\"; \r\n\r\n" + chat_id + "\r\n--Brasil\r\nContent-Disposition: form-data; name=\"photo\"; filename=\"esp32-cam.jpg\"\r\nContent-Type: image/jpeg\r\n\r\n";
    String head_fim = "\r\n--Brasil--\r\n";

    uint16_t comprimentopicture = fb->len;
    uint16_t comprimentoextra = head_corpo.length() + head_fim.length();
    uint16_t comprimentototal = comprimentopicture + comprimentroextra;
  
    client.println("POST /bot"+token+"/sendPhoto HTTP/1.1");
    client.println("Host: " + String(url));
    client.println("Content-Length: " + String(comprimentototal));
    client.println("Content-Type: multipart/form-data; boundary=Brasil");
    client.println();
    client.print(head_corpo);
  
    uint8_t *Buf_temporario_fb = fb->buf;
    size_t fb_comprimento = fb->len;
    for (size_t i=0;i<fb_comprimento;i=i+1024) {
      if (i+1024<fb_comprimento) {
        client.write(Buf_temporario_fb, 1024);
        Buf_temporario_fb += 1024;
      }
      else if (fb_comprimento%1024>0) {
        size_t restante = fb_comprimento%1024;
        client.write(Buf_temporario_fb, restante);
      }
    }  
    
    client.print(head_fim);
    
    esp_camera_fb_return(fb);
    
    int esperaTime = 10000;  
    long iniciaTime = millis();
    boolean estado = false;
    
    while ((iniciaTime + esperaTime) > millis())
    {
      Serial.print(".");
      delay(100);      
      while (client.available()) 
      {
          char c = client.read();
          if (c == '\n') 
          {
            if (obtertudo.length()==0) estado=true; 
            obtertudo = "";
          } 
          else if (c != '\r')
            obtertudo += String(c);
          if (estado==true) corpo += String(c);
          iniciaTime = millis();
       }
       if (corpo.length()>0) break;
    }
    client.stop();
    Serial.println(corpo);
  }
  else {
    corpo="Conexão com api.telegram.org falhou.";
    Serial.println("Conexão com api.telegram.org falhou!");
  }
  
  return corpo;
}



void request_url(char c)
{
  if (c=='?') {
    status_recebido=1;
  }
  if ((c==' ')||(c=='\r')||(c=='\n')){
    status_recebido=0;
  }
  
  if (status_recebido==1)
  {
    comando_geral=comando_geral+String(c);
    
    if (c=='=') {
      status_comando=0;
    }
    if (c==';') {
      status_string++;
    }
  
    if ((status_comando==1)&&((c!='?')||(status_interrogacao==1))){
      comando=comando+String(c);
    }
    if ((status_comando==0)&&(status_string==1)&&((c!='=')||(status_igualdade==1))){
      Par1=Par1+String(c);
    }
    if ((status_comando==0)&&(status_string==2)&&(c!=';')){
      Par2=Par2+String(c);
    }
    if ((status_comando==0)&&(status_string==3)&&(c!=';')){
      Par3=Par3+String(c);
    }
    if ((status_comando==0)&&(status_string==4)&&(c!=';')){
      Par4=Par4+String(c);
    }
    if ((status_comando==0)&&(status_string==5)&&(c!=';')){
      Par5=Par5+String(c);
    }
    if ((status_comando==0)&&(status_string==6)&&(c!=';')){
      Par6=Par6+String(c);
    }
    if ((status_comando==0)&&(status_string==7)&&(c!=';')){
      Par7=Par7+String(c);
    }
    if ((status_comando==0)&&(status_string==8)&&(c!=';')) {
      Par8=Par8+String(c);
    }
    if ((status_comando==0)&&(status_string>=9)&&((c!=';')||(status_pontvirgula==1))){
      Par9=Par9+String(c);
    }
    
    if (c=='?'){
      status_interrogacao=1;
    }
    if (c=='='){
      status_igualdade=1;
    }
    if ((status_string>=9)&&(c==';')){
      status_pontvirgula=1;
    }
  }
}
