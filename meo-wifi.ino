#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

//wifi
const char* ssid     = "MEO-WiFi";
const char* password = "";

//meo login captive
const String MEOUSR  = "email";
const String MEOPASS  = "password";

//gerada aqui -> https://www.grc.com/fingerprints.htm
const String fingerprint  = "chave";



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

   http.begin("https://wifi.meo.pt/HttpHandlers/HotspotConnection.asmx/Login?usr="+MEOUSR,fingerprint);      //Specify request destination
   http.addHeader("Content-Type", "application/x-www-form-urlencoded");  //Specify content-type header

   int httpCode = http.POST("username="+MEOUSR+"&password="+MEOPASS);   //Send the request
   String payload = http.getString();                  //Get the response payload

   Serial.println(httpCode);   //Print HTTP return code // 200=sucesso
   Serial.println(payload);    //Print request response payload

   http.end();  //Close connection




}

void loop() {



}
