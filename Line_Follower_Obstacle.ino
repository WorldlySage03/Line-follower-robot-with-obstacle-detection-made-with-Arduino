/*
* Line Follower Robot with Obstacle Detection
*/


//Right Motor Pin Define
int enA =  10;
int IN1 =  8;
int IN2 = 7;

//Left Motor Pin Define
int IN3 = 6;
int IN4 = 5; 
int enB = 9;


int trig = 4; //output pin
int echo = 3; //input pin
int light = 2; // light

// Sonar Sensor Algo Variable
long timeMicro;
long distanceCm= -1;


// PID Algo Variable
int s[6], total, sensor_position;
int th[6];
int threshold = 450;
float avg;
int position[6] = { 1, 2, 3, 4, 5 };
int set_point = 3;

void setup() {

  Serial.begin(9600);
  
  pinMode(trig, OUTPUT); // Output Pin of Sonar Sensor
  pinMode(echo, INPUT); // Input Pin of Sonar Sensor
  pinMode(light, OUTPUT); // Light Pin
  
  pinMode(enA, OUTPUT); // Motor Driver Pin enA 
  pinMode(IN1, OUTPUT); // Motor Driver Pin in1 
  pinMode(IN2, OUTPUT); // Motor Driver Pin in2 
  pinMode(IN3, OUTPUT); // Motor Driver Pin in3   
  pinMode(IN4, OUTPUT); // Motor Driver Pin in4 
  pinMode(enB, OUTPUT); // Motor Driver Pin enB

}

void irSensorReading(){
  sensor_position = 0;
  total = 0;
  
  for (byte i = 0; i < 5; i++) {
    //snesor data reading from A0, A1, A2, A3, A4
    s[i] = analogRead(i);
    th[i] = s[i];
    // Analog value to digital conversion
    // When sensor is on the Black line Digital Value = 1 otherwise 0
    if (s[i] > threshold) s[i] = 1;  
    else s[i] = 0;
    
    sensor_position += s[i] * position[i];
    total += s[i];

  }
  //display();
  if (total) avg = sensor_position / total;  //average value
}

bool sonarSensorReading(){

  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  
  timeMicro = pulseIn(echo, HIGH); // BuiltIn Function
  //Serial.println( timeMicro);
  distanceCm = timeMicro / 29 / 2; // MicroSecToCm
  //Serial.println(String(distanceCm)+" D");
  if(distanceCm <= 15){
    digitalWrite(light, HIGH);
     return false;
  }
  
  digitalWrite(light, LOW);
  return true;
}

void sensor_reading() {
  
   if(sonarSensorReading()){
     irSensorReading();
   }
   else{
    motor(0,0); // Stop the motors
    delay(50);
    while(!sonarSensorReading()){
      motor(0,0);
      digitalWrite(light, HIGH);
    }
    irSensorReading();
   }
  //display();
}

void display(){
  for (byte i = 0; i < 5; i++) {
      Serial.print(String(s[i]) + " ");

  }
   Serial.println("");
  for (byte i = 0; i < 5; i++) {
      Serial.print(String(th[i]) + " ");

  }
  Serial.println("");
}

void PID_LINE_FOLLOW() {

  int kp = 50, kd = 500, PID_Value, P, D;
  float error, previous_error = 0.00;
  int base_speed = 200, left_motor_speed, right_motor_speed, turn_speed = 90;
  char t;

  while (1) {
    sensor_reading();

    error = set_point - avg;
    D = kd * (error - previous_error);
    P = error * kp;
    PID_Value = P + D;
    previous_error = error;

    right_motor_speed = base_speed + PID_Value;  //right motor speed
    left_motor_speed = base_speed - PID_Value;  //left motor speed


    if (s[0] && !s[4]) t = 'l';
    if (s[4] && !s[0]) t = 'r';

    if (total == 0) { 

        if (t != 's') {
           if (t == 'r') motor(turn_speed, -turn_speed); // Turn Right
           else motor(-turn_speed, turn_speed);     // Turn Left
           while (!s[2]) sensor_reading();

        }
    }
    else if (total == 5) { 
      sensor_reading();
      if (total == 5) {
        motor(0, 0);
        while (total == 5) sensor_reading();
      } else if (total == 0) t = 's';
    }


    motor(left_motor_speed, right_motor_speed); 


  }
}

void motor(int l, int r) {
  if (r > 0) {
    Serial.println("R === M === F");
    rightMotorForward();
  } else {
    r = -(r);
    Serial.println("R === M === B");
    rightMotorBackward();

  }
  if (l > 0) {
    Serial.println("L === M === F");
    leftMotorForward();
  } else {
    Serial.println("L === M === B");
    l = -(l);
     leftMotorBackward();
  }

  if (l > 200) l = 200;
  if (r > 200) r = 200;

  analogWrite(enB, l);
  analogWrite(enA, r);
}


void rightMotorForward(){
  digitalWrite(IN1, HIGH); //Right Motor forword Pin 
  digitalWrite(IN2, LOW);  //Right Motor backword Pin 
}
void rightMotorBackward(){
  digitalWrite(IN1, LOW);  //Right Motor forword Pin 
  digitalWrite(IN2, HIGH); //Right Motor backword Pin 
}
void leftMotorForward(){
  digitalWrite(IN3, LOW);  //Left Motor backword Pin 1
  digitalWrite(IN4, HIGH); //Left Motor forword Pin 
}
void leftMotorBackward(){
  digitalWrite(IN3, HIGH);  //Left Motor backword Pin 
  digitalWrite(IN4, LOW); //Left Motor forword Pin 
}

void loop() {
      delay(100);
      PID_LINE_FOLLOW();
}
