#include <ESP8266WiFi.h>
#include "DHT.h"

const char* ssid  = "[WIFI SSID]";
const char* password = "[WIFI Password]";
const char* host = "[Server Address]";
const char* passcode = "[Passcode (must match if code in PHP)]";
const char* device_name = "[Device Name]";

// DHT Settings
#define DHTPIN D4     // what digital pin we're connected to.

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Initialize the temperature/ humidity sensor
DHT dht(DHTPIN, DHTTYPE);

// Time to sleep (in minutes):
const int sleepTimeM = 15;

void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  dht.begin();

}


double Fahrenheit(double celsius)
{
  return 1.8 * celsius + 32;
}

void loop() {

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

    Serial.print("Current humidity = ");
    Serial.print(h);
    Serial.print("%  ");
    Serial.print("temperature = ");
    Serial.print(t); 
    Serial.print("C, ");
    Serial.print(f);
    Serial.println("F");

  // Connect to host
  Serial.print("Connecting to ");
  Serial.println(host);
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("Connection failed!");
    return;
  }

  // Create a URL for the request. Modify YOUR_HOST_DIRECTORY so that you're pointing to the PHP file.
  String url = "/index.php?device_name=";
  url += device_name;
  url += "&temperature=";
  url += t;
  url += "&humidity=";
  url += h;
  url += "&pass=";
  url += passcode;
  

  // This will send the request to the server
  Serial.print("Requesting URL: ");
  Serial.println(url);
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }

  // Read all the lines of the reply from server and print them to Serial
  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

  Serial.println();
  Serial.println("Closing connection");

  // Sleep
  Serial.println("Going to sleep");
  // Deep sleep (uncomment if you want to use deep sleep and have the RTC pin connected)
//  ESP.deepSleep(sleepTimeM * 1000000 * 60);
  delay(900000);  
}
