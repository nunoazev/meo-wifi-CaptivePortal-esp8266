#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266Ping.h> // biblioteca -> https://github.com/dancol90/ESP8266Ping


//wifi
const char* ssid     = "MEO-WiFi";
const char* password = "";

//meo login captive
const String MEOUSR  = "";
const String MEOPASS  = "";

//gerada aqui -> https://www.grc.com/fingerprints.htm
const String fingerprint  = "50:FE:E2:67:16:26:3C:D0:64:8F:23:43:5D:B2:82:56:A4:5F:03:B0";



void setup() {


  Serial.begin(115200);
  delay(10);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  HTTPClient http;    //Declare object of class HTTPClient

  http.begin("https://servicoswifi.apps.meo.pt/HotspotConnection.asmx/Login?username=" + MEOUSR + "&password=" + MEOPASS + "&navigatorLang=pt&callback=foo", fingerprint);    //Specify request destination
  http.addHeader("Content-Type", "application/javascript; charset=utf-8");  //Specify content-type header
  String payload = http.getString();                  //Get the response payload
  Serial.println(payload);    //Print request response payload
  http.end();  //Close connection

}

void loop() {

  Serial.print("Pinging host ");

  if (Ping.ping("www.google.com")) {
    Serial.println("Success!!");
  } else {
    Serial.println("Error :(");
  }

}
