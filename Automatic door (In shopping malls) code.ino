#include <Servo.h>

#define PIR_PIN 4          // PIR sensor connected to pin 4
#define TRIG_PIN 2         // Ultrasonic sensor trigger pin
#define ECHO_PIN 3         // Ultrasonic sensor echo pin
#define BUZZER_PIN 5       // Buzzer pin
#define SERVO_PIN 6        // Servo motor pin
#define FSR_PIN A0		   // Force sensor connected to A0
#define SWITCH_PIN 7 	   // Slide switch connected to pin A1

Servo doorServo;

void setup() {
    pinMode(PIR_PIN, INPUT);
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(BUZZER_PIN, OUTPUT);
  	pinMode(FSR_PIN, INPUT);
  	pinMode(SWITCH_PIN, INPUT);
    doorServo.attach(SERVO_PIN);
    doorServo.write(0); // Door closed initially
    Serial.begin(9600);
}

int getDistance() {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    return pulseIn(ECHO_PIN, HIGH) * 0.034 / 2; // Convert to cm
}

void loop() {
  	int Switch = digitalRead(SWITCH_PIN);
  	int fsrreading = analogRead(FSR_PIN);
    int motion = digitalRead(PIR_PIN);
    int distance = getDistance();
  	float weight = map(fsrreading, 0, 1023, 0, 10); // Adjusting range based on calibration.

  
    if(Switch == 1){

        if (motion == HIGH && distance < 100 && distance >= 30) { // If motion detected and person is close
            doorServo.write(90); // Open door
          	Serial.println("The person is arriving inside");
            delay(5000);         // Keep door open for 5 seconds
            doorServo.write(0);  // Close door
        }

        else if (motion == LOW && distance < 30) { // If motion detected and person is close
            doorServo.write(90); // Open door
          	Serial.println("The person is standing in front of the door");
        }

        else if (motion == HIGH && distance < 20) { // If motion detected and person is close
            Serial.println("The person is walking inside");
          	doorServo.write(90); // Open door
            delay(5000);         // Keep door open for 5 seconds
            doorServo.write(0);  // Close door
        }
      
      	if(weight >= 8){
          	Serial.print("The weight is :-");
  			Serial.println(weight);
        	digitalWrite(BUZZER_PIN, HIGH); // Sound alarm
            Serial.println("Unauthorized Entry Attempt!");
            delay(1000);
            digitalWrite(BUZZER_PIN, LOW);
      	}
    }
  
  
    else{
		doorServo.write(0);	//Close door
      	if(weight >= 7){
          	Serial.print("The weight is :-");
  			Serial.println(weight);
        	digitalWrite(BUZZER_PIN, HIGH); // Sound alarm
            Serial.println("Unauthorized Entry Attempt!");
            delay(2000);
            digitalWrite(BUZZER_PIN, LOW);
      }
  	}

    delay(500);
}