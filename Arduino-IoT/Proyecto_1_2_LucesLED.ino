#include <SPI.h>
#include <WiFiNINA.h>

#include "arduino_secrets.h" 

char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;            // your network key index number (needed only for WEP)

int status = WL_IDLE_STATUS;
//IPAddress server(192,168,3,9);  // numeric IP for APACHE (no DNS)
char server[] = "webapps-ehi-01.000webhostapp.com";

WiFiClient client;

String peticionPHP = "GET /ProyectoTI/backend/setCO2.php?q=";
String peticionPHPCompleta;

int valor;
int vRead = A0;
float co2ppm;

int buzz = 2;
int contadorBuzz = 0;

// LUZ
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#define PIN        6
#define NUMPIXELS 8
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 10 // Time (in milliseconds) to pause between pixels
// LUZ
void setup() {
  pinMode(buzz, OUTPUT);
  
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to WiFi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(5000);
  }
  Serial.println("Connected to WiFi");
  printWifiStatus();

  //LUZ
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
  #endif
  // END of Trinket-specific code.

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  //LUZ
}

int variable;

void loop() {
  if(!client.connected() || status != WL_CONNECTED) {
    setup();
  }
  
  Serial.println("\nStarting connection to server...");
  if (client.connect(server, 80)) {
    Serial.println("connected to server");
    peticionPHPCompleta = peticionPHP + medirCO2() + " HTTP/1.1";
    client.println(peticionPHPCompleta);
    client.println("Host: webapps-ehi-01.000webhostapp.com");
    
    client.println("Connection: close");
    client.println();
    variable++;
  } 

  Serial.print(server);
  Serial.println(peticionPHPCompleta);
  if(co2ppm >= 900 && contadorBuzz == 10){
    alarma();
    } else{
  if(co2ppm >= 900){
    contadorBuzz ++;
    }
  }
  //LUZ
  if(co2ppm >= 900){
    luzRoja();
  } else if(co2ppm >= 750){
    luzAmarilla();
  } else if(co2ppm < 750){
    luzVerde();
  }
  //LUZ
  delay(1000);
}


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

int medirCO2(){
  valor = analogRead(vRead);
  co2ppm = map(valor,0,1023,400,2000);
  Serial.print(co2ppm);
  Serial.println(" PPM DE CO2");

  return(co2ppm);
}

void alarma(){
  contadorBuzz = 0;
  digitalWrite(buzz, HIGH);
  delay(500);
  
  digitalWrite(buzz, LOW);
  delay(250);
  
  digitalWrite(buzz, HIGH);
  delay(500);

  digitalWrite(buzz, LOW);
  delay(250);

  digitalWrite(buzz, HIGH);
  delay(500);
  digitalWrite(buzz, LOW);
}
void luzRoja(){
  pixels.clear(); // Set all pixel colors to 'off'

  for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
    pixels.setPixelColor(i, pixels.Color(255, 0, 0));

    pixels.show();   // Send the updated pixel colors to the hardware.

    delay(DELAYVAL); // Pause before next pass through loop
  }
}
void luzAmarilla(){
  pixels.clear(); // Set all pixel colors to 'off'

  for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
    pixels.setPixelColor(i, pixels.Color(255, 165, 0));

    pixels.show();   // Send the updated pixel colors to the hardware.

    delay(DELAYVAL); // Pause before next pass through loop
  }
}
void luzVerde(){
  pixels.clear(); // Set all pixel colors to 'off'

  for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
    pixels.setPixelColor(i, pixels.Color(0, 255, 0));

    pixels.show();   // Send the updated pixel colors to the hardware.

    delay(DELAYVAL); // Pause before next pass through loop
  }
}
