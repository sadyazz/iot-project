#include <Arduino.h>
#if defined(ESP32)
  #include <WiFi.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>


#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"


#define WIFI_SSID ""
#define WIFI_PASSWORD ""
#define API_KEY ""
#define DATABASE_URL "" 

FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
bool signupOK = false;


#define PIR_PIN D7
#define LED_PIN D1

int buzzer = D2;
int smokeA0 = A0;

int motion_state = LOW; 
int prev_motion_state = LOW;

int sensorThres = 600;

#define DO_PIN D6
#define LDR_LED D3

bool ledStatus = false;

#define LED_ALONE_PIN D5

void setup() {
  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("ok");
    signupOK = true;
  }
  else {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  //pir
  Serial.begin(9600);     
  pinMode(PIR_PIN, INPUT); 
  pinMode(LED_PIN, OUTPUT);  

  //mq2
  pinMode(buzzer, OUTPUT);
  pinMode(smokeA0, INPUT);

  //ldr
  pinMode(DO_PIN, INPUT);
  pinMode(LDR_LED, OUTPUT);

  pinMode(LED_ALONE_PIN, OUTPUT);
}

void loop() {

  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 1000 || sendDataPrevMillis == 0)){
    sendDataPrevMillis = millis();
     Serial.println("Checking LED status from Firebase");
    if (Firebase.RTDB.getBool(&fbdo, "test/led_status")){
      Serial.println("Got LED status from Firebase");
      if (fbdo.dataType() == "boolean") {
            bool receivedStatus = fbdo.boolData();
              Serial.print("Received LED status: ");
            Serial.println(receivedStatus);
            
            if (receivedStatus) {
                digitalWrite(LED_ALONE_PIN, HIGH); 
            } else {
                digitalWrite(LED_ALONE_PIN, LOW);
            }
        }
    }
    else {
        Serial.println("Error getting LED status: " + fbdo.errorReason());
    }
    
    ledStatus = !ledStatus;

    bool led2Status = digitalRead(LED_PIN);
    bool led3Status = digitalRead(LDR_LED);

    Firebase.RTDB.setBool(&fbdo, "test/led2", led2Status);
    Firebase.RTDB.setBool(&fbdo, "test/led3", led3Status);
  }
   
  //pir
  prev_motion_state = motion_state;  
  motion_state = digitalRead(PIR_PIN); 

  if (motion_state == HIGH) { 
     Serial.println("Detektovan pokret! LED se pali");
     digitalWrite(LED_PIN, HIGH);
     delay(5000);
   } else {
     digitalWrite(LED_PIN, LOW);
   }

  //mq2
  int analogSensor = analogRead(smokeA0);

  Serial.print("Pin A0: ");
  Serial.println(analogSensor);
  // Checks if it has reached the threshold value
  if (analogSensor > sensorThres) {
    tone(buzzer, 1000, 200);
  } else {
    noTone(buzzer);
  }
 

   //ldr
   int light_state = digitalRead(DO_PIN);

   if (light_state == HIGH){

     Serial.println("The light is NOT present");
     digitalWrite(LDR_LED, HIGH);
   }
   else{

     Serial.println("The light is present");
     digitalWrite(LDR_LED, LOW);
   }
  
}
