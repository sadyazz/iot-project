#define PIR_PIN D7
#define LED_PIN D1

int buzzer = D2;
int smokeA0 = A0;

int motion_state = LOW;       // trenutno stanje pin-a senzora pokreta
int prev_motion_state = LOW;  // prethodno stanje pin-a senzora pokreta

int sensorThres = 600;

#define DO_PIN D6
#define LDR_LED D3

#define LED_ALONE_PIN D5

int i =0;


void setup() {
  //pir
  Serial.begin(9600);                 // Inicijalizacija serijske komunikacije
  pinMode(PIR_PIN, INPUT);  // Konfiguracija pin-a senzora pokreta kao ulaznog
  pinMode(LED_PIN, OUTPUT);           // Konfiguracija pin-a LED-a kao izlaznog

  //mq2
  pinMode(buzzer, OUTPUT);
  pinMode(smokeA0, INPUT);

  //ldr
  pinMode(DO_PIN, INPUT);
  pinMode(LDR_LED, OUTPUT);

  pinMode(LED_ALONE_PIN, OUTPUT);
}

void loop() {

  //pir
  prev_motion_state = motion_state;               // Čuvanje prethodnog stanja
  motion_state = digitalRead(PIR_PIN);  // Čitanje novog stanja

  if (motion_state == HIGH) {  // Ako se detektuje pokret
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
  //delay(100);

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
