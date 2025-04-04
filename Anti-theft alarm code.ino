#define TILT_SENSOR_PIN 2  // Tilt sensor connected to pin 2
#define BUZZER_PIN 10       // Buzzer pin
#define LED_RED_PIN 9      // LED pin
#define FSR_PIN A4      // Force sensor connected to A4
#define LED_GREEN_PIN 8 	// LED pin

void setup() {
    pinMode(TILT_SENSOR_PIN, INPUT);
  	pinMode(FSR_PIN, INPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(LED_RED_PIN, OUTPUT);
  	pinMode(LED_GREEN_PIN, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    int tiltState = digitalRead(TILT_SENSOR_PIN);
  	int fsrreading = analogRead(FSR_PIN);
  	float weight = map(fsrreading, 0, 1023, 0, 10); // Adjusting range based on calibration.
  	Serial.print("The weight is :- ");
  	Serial.println(weight);
  	
  	if (tiltState == HIGH && weight == 5) {  // If the object is tilted but in position.
        digitalWrite(LED_RED_PIN, HIGH);
        Serial.println("Warning! Object moved!");
        delay(1000);  // Alarm duration
    } 
  
  	//Assuming the weight of the securing object is 5 units.
    else if(weight > 5){	//If other object is placed.
      	digitalWrite(BUZZER_PIN, HIGH);
        digitalWrite(LED_RED_PIN, HIGH);
        Serial.println("Warning! Object Replaced!");
        delay(1000);
    }
  
    else if(weight < 5){	//If object is removed.
        digitalWrite(BUZZER_PIN, HIGH);
        digitalWrite(LED_RED_PIN, HIGH);
        Serial.println("Warning! Object removed!");
      	delay(1000);
    }
  
    else {
        digitalWrite(BUZZER_PIN, LOW);
        digitalWrite(LED_RED_PIN, LOW);
    }

    delay(500);
}
