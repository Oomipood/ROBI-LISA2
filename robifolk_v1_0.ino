//=====VARIABLES=====
//distance check variables:
const int trigPinLeft = 4;
const int trigPinCenter = 3;
const int trigPinRight = 9;

const int echoPinLeft = 8;
const int echoPinCenter = 2;
const int echoPinRight = 7;
long duration, distance;

//Logics variables
int distLeft;
int distCenter;
int distRight;
const int distStop = 1;
const int distWall = 4;
const int distMax = 800;
const int distMin = 0;
int errorLED = 13;

//Wall counters
int counterLeft = 0;
int counterRight = 0;
int counterCenter = 0;

//Move conters
unsigned long turnLeft = 0;
unsigned long turnRight = 0;

//Motors:
int mot_speed = 255;
int k = 0;
const int mot1f = 5;
const int mot1b = 6;
const int mot2f = 10;
const int mot2b = 11;

//=====INITIALIZATION=====
void setup(){
  pinMode(errorLED, OUTPUT);
  pinMode(trigPinLeft, OUTPUT);
  pinMode(trigPinCenter, OUTPUT);
  pinMode(trigPinRight, OUTPUT);
  
  pinMode(echoPinLeft, INPUT);
  pinMode(echoPinCenter, INPUT);
  pinMode(echoPinRight, INPUT);
  
  delay(2000);
  motors_forward();
}

//=====MAIN PROGRAM=====
void loop(){

  pingLeft();

  if (distLeft <= distWall){
    counterLeft ++;}
    else {
      counterLeft = 0;
    }
    
  pingCenter();

  if (distCenter <= distWall){
    counterCenter ++;}
    else {
      counterCenter = 0;
    }
    
  pingRight();

  if (distRight <= distWall){
    counterRight ++;}
    else {
      counterRight = 0;
    }
     
  mot_speed = 255;
  motors_forward();
  delay(30);
  logics();
  

  
}

//=====FUNCTIONS=====
void logics(){
//===============================  Distance check  =========================
  if (distLeft <= distMin){
    digitalWrite(errorLED, 1);
    //Serial.println("Left distance is 0");
    motors_stop();
    return;
  }
  if (distCenter <= distMin){
    digitalWrite(errorLED, 1);
    //Serial.println("Center distance is 0");
    motors_stop();
    return;
  }
  if (distRight <= distMin){
    digitalWrite(errorLED, 1);
    //Serial.println("Right distance is 0");
    motors_stop();
    return;
  }

//=================================  Counters ===================
 if (counterLeft == 2){
     counterLeft = 0; 
     mot_speed = 255;
     motors_right();
     delay(200);  
 }
  if (counterCenter == 2){
     counterCenter = 0; 
     mot_speed = 255; 
     motors_back();
     delay(200);
     if (turnLeft > turnRight){
         motors_back_right();
         delay(200);
     }
     else {
       motors_back_left();
       delay(250);
       } 
 }
   if (counterRight == 2){
     counterCenter = 0; 
     mot_speed = 255;
     motors_left();
     delay(200);   
 }
  
//================================  Moving ==============
  if (distLeft < distCenter & distRight < distCenter){
    mot_speed = 255;
    motors_forward;
}    
  //Turn left if:
  if (distRight < distCenter & distLeft > distCenter){
    mot_speed = 200;
    motors_left();
    turnLeft ++;
  delay(5);
  }    
  //Turn right if:
  if (distLeft < distCenter & distRight > distCenter){
   mot_speed = 200;
   motors_right();
   turnRight ++;
   delay(5);
 }  
}

int pingLeft(){                  //simple distance check (left)
  digitalWrite(trigPinLeft, 0);
  delayMicroseconds(2);
  digitalWrite(trigPinLeft, 1);
  delayMicroseconds(10);
  digitalWrite(trigPinLeft, 0);
  duration = pulseIn(echoPinLeft, 1);
  distance = duration/58;
  
  distLeft = distance;
}
int pingCenter(){                  //simple distance check (center)
  digitalWrite(trigPinCenter, 0);
  delayMicroseconds(2);
  digitalWrite(trigPinCenter, 1);
  delayMicroseconds(10);
  digitalWrite(trigPinCenter, 0);
  duration = pulseIn(echoPinCenter, 1);
  distance = duration/58;
  
  distCenter = distance;
}
int pingRight(){                  //simple distance check (left)
  digitalWrite(trigPinRight, 0);
  delayMicroseconds(2);
  digitalWrite(trigPinRight, 1);
  delayMicroseconds(10);
  digitalWrite(trigPinRight, 0);
  duration = pulseIn(echoPinRight, 1);
  distance = duration/58;
  
  distRight = distance;
}

void motors_forward(){                    //MOTORS FORWARD FUNCTION
  analogWrite(mot1f, mot_speed);
  analogWrite(mot2f, mot_speed);
  digitalWrite(mot1b, 0);
  digitalWrite(mot2b, 0);
}
void motors_back(){                      //MOTORS BACK FUNCTION
  digitalWrite(mot1f, 0);
  digitalWrite(mot2f, 0);
  analogWrite(mot1b, mot_speed);
  analogWrite(mot2b, mot_speed);
}
void motors_stop() {                      //MOTORS STOP FUNCTION
  digitalWrite(mot1f, 1);
  digitalWrite(mot2f, 1);
  digitalWrite(mot1b, 1);
  digitalWrite(mot2b, 1);
}
void motors_left() {                     //MOTORS LEFT FUNCTION
  analogWrite(mot1f, mot_speed);
  digitalWrite(mot2f, 0);
  digitalWrite(mot1b, 0);
  analogWrite(mot2b, mot_speed);
}
void motors_right() {                    //MOTORS RIGHT FUNCTION
  digitalWrite(mot1f, 0);
  analogWrite(mot2f, mot_speed);
  analogWrite(mot1b, mot_speed);
  digitalWrite(mot2b, 0);
}
void motors_forward_left() {             //FORWARD LEFT FUNCTION
k = mot_speed*0.7;
  analogWrite(mot1f, mot_speed);
  analogWrite(mot2f, k);
  digitalWrite(mot1b, 0);
  digitalWrite(mot2b, 0);
}
void motors_forward_right() {             //FORWARD RIGHT FUNCTION
k = mot_speed*0.8;
  analogWrite(mot1f, k);
  analogWrite(mot2f, mot_speed);
  analogWrite(mot1b, 0);
  analogWrite(mot2b, 0);
}
void motors_back_left() {               //BACK LEFT FUNCTION
k = mot_speed*0.7;
  digitalWrite(mot1f, 0);
  digitalWrite(mot2f, 0);
  analogWrite(mot1b, k);
  analogWrite(mot2b, mot_speed);
}
void motors_back_right() {               //BACK RIGHT FUNCTION
k = mot_speed*0.7;
  digitalWrite(mot1f, 0);
  digitalWrite(mot2f, 0);
  analogWrite(mot1b, mot_speed);
  analogWrite(mot2b, k);
}
