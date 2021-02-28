#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>


const char* ssid = "Balachandran";
const char* password = "Siva@6384";

ESP8266WebServer server(80);
int echopin = D2;
int trigpin = D3;
long duration;
int distance;
int level;
 
void setup() {
  Serial.begin(115200);
  delay(100);
  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);    
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());

  server.on("/", handle_OnConnect);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");

}
void loop() {
  
  server.handleClient();
  handle_OnConnect();
  delay(100);
  
}

void handle_OnConnect() {
  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin, LOW);
  duration = pulseIn(echopin, HIGH);
  distance = duration * 0.034 / 2;
  if (distance>12){
    level=0;}
  else if (distance<=12 and distance>11){
    level=1;}
  else if (distance<=11 and distance>10){
    level=2;}
  else if (distance<=10 and distance>9){
    level=3;}
  else if (distance<=9 and distance>8){
    level=4;}
  else if (distance<=8 and distance>7){
    level=5;}
  else if (distance<=7 and distance>6){
    level=6;}
  else if (distance<=6 and distance>5){
    level=7;}
  else if (distance<=5 and distance>4){
    level=8;}
  server.send(200, "text/html", SendHTML(level));
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(10); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String SendHTML(int a){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<meta http-equiv='refresh' content='2'/>";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>Water Level</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;}\n";
  ptr +="p {font-size: 24px;color: #444444;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<div id=\"webpage\">\n";
  ptr +="<h1>Water Level Detection and Alarm</h1>\n";
  ptr +="<p>Water Level: ";
  ptr +=(int)a;
  ptr +=" meters</p>";
  ptr +="</div>\n";
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}
