#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>

const char* ssid="*******";
const char* pass="*******";
bool state = false;
ESP8266WebServer server(8080);
void setup() {
  pinMode(4, OUTPUT);
  digitalWrite(4,HIGH);
  WiFi.begin(ssid,pass);
  Serial.begin(115200);
  while(WiFi.status() !=WL_CONNECTED){
    delay(1000);
    Serial.println(".");
  }
  Serial.print("Ip:");
  Serial.println(WiFi.localIP());
  server.on("/",Connect);
  server.on("/on",On);
  server.on("/off",Off);
  server.onNotFound(NotFound);
  server.begin();
}

void loop() {
  server.handleClient();

}
void Connect()
{
  server.send(200,"text/html",Html(state));
}
void On()
{
  state = true;
  digitalWrite(4,LOW);
  server.send(200,"text/html",Html(state));
}
void Off()
{
  state = false;
  digitalWrite(4,HIGH);
  server.send(200,"text/html",Html(state));
}
void NotFound()
{
  server.send(404,"text/plain","Not found");
}
String Html(bool On)
{
  String ptr = "<!DOCTYPE html>\n";
  ptr += "<html lang='en'>\n";
  ptr += "<head>\n";
  ptr += "<meta charset='UTF-8' />\n";
  ptr += "<meta http-equiv='X-UA-Compatible' content='IE=edge' />\n";
  ptr += "<meta name='viewport' content='width=device-width, initial-scale=1.0' />\n";
  ptr += "<link rel='icon' href='https://cdn-icons-png.flaticon.com/512/92/92031.png'/>\n";
  ptr += "<title>Raven</title>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<div class='cont'>\n";
  ptr += "<h1 class='text'>Raven</h1>\n";
  ptr += "<div class='status'>\n";
  ptr += "<p class='p'>Light Status:</p>\n";
  ptr += "<p class='p-off'>"+ String(On ? "On" : "Off")+"</p>\n";
  ptr += "</div>\n";
  ptr += String(On ? "<a class='link' href='/off'>"+ String(On ? "Off" : "On") +"</a>\n" : "<a class='link' href='/on'>"+ String(On ? "Off" : "On") +"</a>\n");
  ptr += "</div>\n";
  ptr += "<style>\n";
  ptr += "@import url('https://fonts.googleapis.com/css2?family=Poppins&display=swap');\n";
  ptr += "* {margin: 0;padding: 0;box-sizing: border-box;font-family: 'Poppins', sans-serif;}\n";
  ptr += ".cont {display: flex;flex-direction: column;align-items: center;width: 100%;min-height: 100vh;background: linear-gradient(to right, #2ec4b6, black);}\n";
  ptr += ".text {color: white;background: linear-gradient(to right, #c6ffdd, #fbd786, #f7797d);-webkit-background-clip: text;-webkit-text-fill-color: transparent;font-size: 3rem;font-weight: bold;margin-top: 2.5rem;filter: drop-shadow(0px 0px 5px rgba(0, 0, 0, 0.5));}\n";
  ptr += ".p {color: white;font-size: 1.5rem;text-shadow: 0 0 5px black;}\n";
  ptr += ".p-off {color:" +String(On ? "green":"red")+";font-size: 1.5rem;margin-left: 0.3rem;text-shadow: 0 0 5px black;}\n";
  ptr += ".status {display: flex;}\n";
  ptr += ".link {margin-top: 1rem;width: 8rem;padding: 0.6rem;display: flex;justify-content: center;color:"+String(On ? "#011627" : "#fff") +";font-size: 1.2rem;font-weight: bold;border-radius: 0.5rem;text-decoration: none;background:"+String(On ? "#fff" : "#011627")+";transition: 400ms ease-in;}\n";
  ptr += ".link:hover {background:" +String(On ? "#011627" : "#fff")+";color:"+String(On ? "#fff" : "#011627")+ ";}\n";
  ptr += "</style>\n";
  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
  }
