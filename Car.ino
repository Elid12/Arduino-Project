#include <Servo.h> //servo motor library

//DECLARING THE LDR SENSOR
int LDR = 0;//ldr uses pin A0
int LDRValue = 0;//variable to store LDR value

//DECLARING THE GREEN LED
int LED = 2;//led uses pin 2

//DECLARING THE MOTOR DRIVER
//right motor
int In1 = 7;//uses pin 7, controlls direction of motor
int In2 = 8;//uses pin 8
int ENA = 5;//uses pin ~5, controlls speed of motor

//left motor
int In3 = 12;//uses pin 12
int In4 = 13;//uses pin 13
int ENB = 6;//uses pin ~6

int SPEED = 150;//motor's speed

//DECLARING THE SERVO MOTOR
Servo sg90;//the used servo motor

//DECLARING THE ULTRASENSOR
#define trig 4//uses pin 4
#define echo 3//uses pin ~3

int duration, distance;/*duration of the traveling sound &
the calculated distance of an object*/

void forward()//function that moves motors forward
{
   //right motor moves forward
  digitalWrite(In1,LOW);
  digitalWrite(In2,HIGH);
  analogWrite(ENA,SPEED);

  //left motor moves forward
  digitalWrite(In3,HIGH);
  digitalWrite(In4,LOW);
  analogWrite(ENB,SPEED);
}

void stops()//function that stops motors 
{
   //right motor stops
  digitalWrite(In1,LOW);
  digitalWrite(In2,LOW);

  //left motor stops
  digitalWrite(In3,LOW);
  digitalWrite(In4,LOW);
}

void backward()//function that moves motors backwards
{
  //right motor moves backward
  digitalWrite(In1,HIGH);
  digitalWrite(In2,LOW);

  //left motor moves backward
  digitalWrite(In3,LOW);
  digitalWrite(In4,HIGH);
}

void right()//function that moves motors right direction
{
   //right motor moves right
  digitalWrite(In1,HIGH);
  digitalWrite(In2,LOW);
  analogWrite(ENA,SPEED);

  //left motor moves right
  digitalWrite(In3,HIGH);
  digitalWrite(In4,LOW);
  analogWrite(ENB,SPEED);
}

void left()//funcion that moves motors left direction
{
   //right motor moves left
  digitalWrite(In1,LOW);
  digitalWrite(In2,HIGH);
  analogWrite(ENA,SPEED);

  //left motor moves left
  digitalWrite(In3,LOW);
  digitalWrite(In4,HIGH);
  analogWrite(ENB,SPEED);
}

int sonar()//function that calculates the distance of an object
{
  digitalWrite(trig,LOW);/*giving a short LOW pulse to ensure a
  clean HIGH pulse*/
  delayMicroseconds(2);

  digitalWrite(trig,HIGH);/*sensor triggered by a HIGH pulse for 
  10 microseconds*/
  delayMicroseconds(10);
  digitalWrite(trig,LOW);

  duration = pulseIn(echo,HIGH);/*echo receiving a high pulse 
  which is the time of the reflected wave*/
  distance = (duration/2)/29.1;//converting time into a distance(cm)

  return distance;
}

int sonarR()//distance from the right side of the servo
{
    digitalWrite(trig,LOW);
    delayMicroseconds(2);

    digitalWrite(trig,HIGH);
    delayMicroseconds(10);
    digitalWrite(trig,LOW);

    int durationR = pulseIn(echo,HIGH);
    int distanceR = (durationR/2)/29.1;

    return distanceR;
}

int sonarL()//distance from the left side of the servo
{
    digitalWrite(trig,LOW);
    delayMicroseconds(2);

    digitalWrite(trig,HIGH);
    delayMicroseconds(10);
    digitalWrite(trig,LOW);

    int durationL = pulseIn(echo,HIGH);
    int distanceL = (durationL/2)/29.1;

    return distanceL;
}

int lookRight()//servo turns right direction
{
  delay(500);
  sg90.write(50);//servo turns an angle of 50
  delay(500);

  int disR = sonarR();
  delay(100);
  
  return disR;
}

int lookLeft()//servo turns left direction
{
  delay(500);
  sg90.write(180);
  delay(500);

  int disL = sonarL();

  return disL;
}

void setup() {
  // put your setup code here, to run once:

  //Initializing the LDR Sensor
  pinMode(LDR,INPUT);

  //Initializing the LED
  pinMode(LED,OUTPUT);

  //Initializing the right motor
  pinMode(In1,OUTPUT);
  pinMode(In2,OUTPUT);
  pinMode(ENA,OUTPUT);
  //Initializing the left motor
  pinMode(In3,OUTPUT);
  pinMode(In4,OUTPUT);
  pinMode(ENB,OUTPUT);

  //Initializing the servo pin
  sg90.attach(9);//pin ~9

  //Initializing the ultrasensor
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);

  sg90.write(100);
  delay(2000);

  distance = sonar();
  delay(100);
  distance = sonar();
  delay(100);
  distance = sonar();
  delay(100);
  distance = sonar();
  delay(100);
  
  Serial.begin(9600);//serial's speed(9600 bit/sec of info)  
}

void loop() {
  // put your main code here, to run repeatedly:

  //Reading the LDR value
  LDRValue = analogRead(LDR);
  Serial.println(LDRValue);
  delay(500);

  if((LDRValue >= 600) && (LDRValue <850))
  {
    digitalWrite(LED,HIGH);//led is on
    forward();
    delay(50);
    
    sonar();

    int dL = 0;//distance left
    int dR = 0;//distance right

    if(distance <= 20)
    {
      stops();
      delay(200);
      backward();
      delay(200);
      stops();
      delay(200);
      right();
      delay(200);
      
    }
    else
    {
      delay(500);
      sg90.write(115);//servo is neither turned right not left
      forward();
    }
  }
  else
  {
    digitalWrite(LED,LOW);//led is off
    stops();//motors are stopped
  }
}

