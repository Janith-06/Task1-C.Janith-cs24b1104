#include <Servo.h>

#define LDR_PIN A0       // Photoresistor connected to A0
#define TEMP_PIN A2      // Temperature sensor connected to A2
#define SERVO_PIN 13      // Servo motor control pin

Servo curtainServo;

void setup() {
    pinMode(LDR_PIN, INPUT);
    pinMode(TEMP_PIN, INPUT);
    curtainServo.attach(SERVO_PIN);
    Serial.begin(9600);
}

void loop() {
    int lightLevel = analogRead(LDR_PIN);
    int temp = 0.4831*analogRead(TEMP_PIN) - 49.28; // Convert temperature output to Celsius

    Serial.print("Light Level: "); Serial.println(lightLevel);
    Serial.print("Temperature: "); Serial.println(temp);

    // Curtain logic
    if (lightLevel > 300) {  // Too bright
        curtainServo.write(90);  // Close curtain
        Serial.println("Curtain Closed");
      	Serial.println("Too bright");
    }
  
  	else if (temp > 30) {  // Too hot
        curtainServo.write(90);  // Close curtain
        Serial.println("Curtain Closed");
      	Serial.println("Too hot");
    }
  
    else if(temp < 10){	// Too Cold
        curtainServo.write(90);  // Close curtain
        Serial.println("Curtain Closed");
     	Serial.println("Too Cold");
    }

    else {
        curtainServo.write(0);  // Open curtain
        Serial.println("Curtain Open");
    }

    delay(1000);
}
