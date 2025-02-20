#define pingPin 2        // trig pin of sr04
#define echoPin 3

void setup() {
   Serial.begin(9600); // Starting Serial Terminal
   pinMode(pingPin, OUTPUT); 
   pinMode(echoPin, INPUT);
   pinMode(12, OUTPUT);   // pin12 is used as GND pin for buzzer since Arduino Nano has only two GND pins
   pinMode(A3, OUTPUT);   // pin A3 provides the output on buzzer
   pinMode(5, OUTPUT);    // pin 5 is used for vibration motor
}

void loop() {
   long duration, cm;
   digitalWrite(12, LOW);   // Buzzer GND is always low

   // Send a signal at ping pin at an interval of 0.002 seconds to check for an object
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);    
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);

   duration = pulseIn(echoPin, HIGH);  // Check time using pulseIn function
   cm = microsecondsToCentimeters(duration);   // Function call to find distance

   // Debugging
   // Serial.print(cm);
   // Serial.print("cm");
   // Serial.println();
   // delay(100);

   if (cm < 30 && cm > 20) {
       analogWrite(A3, 255); 
       digitalWrite(5, HIGH);    // Activate vibration motor
       delay(1000); 
       analogWrite(A3, 0); 
       digitalWrite(5, LOW);     // Deactivate vibration motor
       delay(1000); 
   } else if (cm < 20 && cm > 10) {
       analogWrite(A3, 255); 
       digitalWrite(5, HIGH);    // Activate vibration motor
       delay(500); 
       analogWrite(A3, 0); 
       digitalWrite(5, LOW);     // Deactivate vibration motor
       delay(500); 
   } else if (cm < 10 && cm > 0) {
       analogWrite(A3, 255); 
       digitalWrite(5, HIGH);    // Activate vibration motor
       delay(100); 
       analogWrite(A3, 0);
       digitalWrite(5, LOW);     // Deactivate vibration motor
       delay(100); 
   } else {
       analogWrite(A3, 0);       // Do not sound the buzzer
       digitalWrite(5, LOW);     // Deactivate vibration motor
   }
}

// Function to return distance in cm from microseconds
long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}
