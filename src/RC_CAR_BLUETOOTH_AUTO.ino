#include <Servo.h>

// --- PIN CONFIGURATIONS ---
const int IN4 = 3; 
const int IN3 = 7; 
const int IN2 = 8; 
const int IN1 = 9;  

const int ENA = 5; // PWM Speed
const int ENB = 6; // PWM Speed

const int Echo = 2;
const int Trig = 4;
const int SERVO_PIN = 12; 

// --- SYSTEM OBJECTS & VARIABLES ---
Servo radarServo;

bool automatic = false; // false = manualMode, true = autoMode
bool ultrasonicEnable = false; 
bool obstracleDetected = false; 
char command;

int currentSpeed = 175; 
const int SPEED_ECO = 115;
const int SPEED_NORMAL = 175;
const int SPEED_RACING = 255;

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(Echo, INPUT);
  pinMode(Trig, OUTPUT);
  
  radarServo.attach(SERVO_PIN);
  radarServo.write(90); 
  
  Serial.begin(9600); 
  stopCar();
}

void loop() {
  // Check for incoming Bluetooth mode shifts or speed changes
  if (Serial.available() > 0) {
    command = Serial.read();
    
    if (command == 'E')      { currentSpeed = SPEED_ECO; } 
    else if (command == 'N') { currentSpeed = SPEED_NORMAL; } 
    else if (command == 'X') { currentSpeed = SPEED_RACING; }
    else if (command == 'T') { ultrasonicEnable = !ultrasonicEnable; }
    else if (command == 'U') { 
      automatic = !automatic; // Flip the switch between manual and auto
      stopCar();
      radarServo.write(90); 
    }
  }

  // --- RUN SEPARATED MODES ---
  if (automatic) {
    autoMode();
  } else {
    manualMode();
  }
}

// ========================================================
// MODE 1: MANUAL BLUETOOTH CONTROL
// ========================================================
void manualMode() {
  obstracleDetected = false; 
  
  if (ultrasonicEnable) {
    int distance = getDistance();
    if (distance < 20 && distance > 0) {
      stopCar();
      obstracleDetected = true;
    }
  }
  
  // Execute movement based on the last command read in loop
  switch (command) {
    case 'F': if (!obstracleDetected) { moveForward(); } break;
    case 'B': moveBackward(); break;
    case 'L': turnLeft();     break;
    case 'R': turnRight();    break;
    case 'S': stopCar();      break;
  }
}

// ========================================================
// MODE 2: AUTONOMOUS SELF-DRIVING
// ========================================================
void autoMode() {
  int centerDist = getDistance();
  
  if (centerDist < 25 && centerDist > 0) {
    stopCar();
    delay(200);
    
    // Look Left
    radarServo.write(160);
    delay(400); 
    int leftDist = getDistance();
    
    // Look Right
    radarServo.write(20);
    delay(400);
    int rightDist = getDistance();
    
    // Look back Center
    radarServo.write(90);
    delay(200);
    
    // Path Decision
    if (leftDist > rightDist && leftDist > 20) {
      turnLeft();
      delay(500); 
    } 
    else if (rightDist > leftDist && rightDist > 20) {
      turnRight();
      delay(500);
    } 
    else {
      moveBackward();
      delay(600);
      turnRight(); 
      delay(400);
    }
    stopCar();
  } 
  else {
    // Path clear? Keep rolling forward at normal speed
    analogWrite(ENA, SPEED_ECO);
    analogWrite(ENB, SPEED_ECO);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }
}

// --- HELPER SENSOR FUNCTION ---
int getDistance() {
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  
  long duration = pulseIn(Echo, HIGH, 10000); 
  int cm = (duration * 0.0343) / 2;
  return cm;
}

// --- MOTION CONTROL FUNCTIONS ---
void moveForward() {
  analogWrite(ENA, currentSpeed);
  analogWrite(ENB, currentSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void moveBackward() {
  analogWrite(ENA, currentSpeed);
  analogWrite(ENB, currentSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnLeft() {
  analogWrite(ENA, currentSpeed);
  analogWrite(ENB, currentSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnRight() {
  analogWrite(ENA, currentSpeed);
  analogWrite(ENB, currentSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void stopCar() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}