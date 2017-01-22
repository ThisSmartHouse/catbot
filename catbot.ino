#include <Servo.h>

Servo vert; 
Servo hor;

int WIFI_ON_PIN = 10;
int LASER_POWER_PIN = 11;
int VERT_SERVO_PIN = 8;
int HORIZ_SERVO_PIN = 9;
int STATUS_LED_PIN = 13;

void setup() {
  Serial.begin(115200);
  delay(10);
  
  Serial.print("Initializing Coogle-CatToy..");
  pinMode(WIFI_ON_PIN, INPUT);
  pinMode(LASER_POWER_PIN, OUTPUT);
  pinMode(STATUS_LED_PIN, OUTPUT);
  
  digitalWrite(LASER_POWER_PIN, LOW);

  vert.attach(VERT_SERVO_PIN);
  hor.attach(HORIZ_SERVO_PIN);

  vert.write(130);
  hor.write(100);

  Serial.println("complete.");
  
  for(int i = 0; i < 5; i++) {
    digitalWrite(STATUS_LED_PIN, HIGH);
    delay(200);
    digitalWrite(STATUS_LED_PIN, LOW);
    delay(200);   
  }
  
}
   
void loop() { 

  int newVert;
  int newHorz;
  
  if(digitalRead(WIFI_ON_PIN) == HIGH) {

    digitalWrite(STATUS_LED_PIN, HIGH);
    
    if(!vert.attached()) {
      vert.attach(VERT_SERVO_PIN);
    }

    if(!hor.attached()) {
      hor.attach(HORIZ_SERVO_PIN);
    }
    
    Serial.println("Active");
  
    digitalWrite(LASER_POWER_PIN, HIGH);

    newVert = random(130, 150);
    newHorz = random(100, 130);

    Serial.print("Moving vertical: ");
    Serial.println(newVert);

    Serial.print("Moving horizontal: ");
    Serial.println(newHorz);
    
    if(newVert > vert.read()) {
      for(int i = vert.read(); i <= newVert; i++) {
        vert.write(i);
        delay(random(20,50));
      }
    } else {
      for(int i = vert.read(); i >= newVert; i--) {
        vert.write(i);
        delay(random(20, 50));
      }
    }
      
    if(newHorz > hor.read()) {
      for(int i = hor.read(); i <= newHorz; i++) {
        hor.write(i);
        delay(random(20, 50));
      }
    } else {
      for(int i = hor.read(); i >= newHorz; i--) {
        hor.write(i);
        delay(random(20, 50));
      }
    }

    delay(random(2000,5000));
    
    digitalWrite(STATUS_LED_PIN, LOW);
    delay(100);
    digitalWrite(STATUS_LED_PIN, HIGH);
                  
  } else {
    
    digitalWrite(STATUS_LED_PIN, HIGH);
    delay(500);
    digitalWrite(STATUS_LED_PIN, LOW);
    delay(500);
    
    Serial.println("Not active");
    digitalWrite(LASER_POWER_PIN, LOW);
  }
  
}


