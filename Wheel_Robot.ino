//MOTOR ONE
#define enA 5
#define in1 6
#define in2 7

//MOTOR TWO
#define enB 10
#define in3 8
#define in4 9

//IR REMOTE
#include "IRremote.h"
#define receiver 11

IRrecv irrecv(receiver);
decode_results results;

void moveForward(){
  digitalWrite(in1,LOW);
  digitalWrite(in2, HIGH);
  //analogWrite(enA, 80);

  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  //analogWrite(enB, 80); 
}

void moveBackward(){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  //analogWrite(enA, 80);

  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  //analogWrite(enB, 80);
}

void moveBrake(){
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
}

void moveTurn(int i){
  if(i == 1){  //turn right
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
    digitalWrite(in3,LOW);
    digitalWrite(in4,LOW);
    //analogWrite(enA, 90);
    delay(800);
    moveBrake();
  }
  if(i == 2){  //turn left
    digitalWrite(in1,LOW);
    digitalWrite(in2,LOW);
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW);
    //analogWrite(enB, 90);
    delay(800);
    moveBrake();
  }
}
void setSpeed(int irRead){
    Serial.print("set Speed: ");
    Serial.println(irRead);
    if (irRead == 12495){
      analogWrite(enA, 60);
      analogWrite(enB, 60);
      Serial.println("60");
    }
    if (irRead == 6375){
      analogWrite(enA, 90);
      analogWrite(enB, 90);
      Serial.println("90");
    }
    if (irRead == 31365){
      analogWrite(enA, 110);
      analogWrite(enB, 110);
      Serial.println("110");
    }
}

//ADD A BEEPER JUST FOR FUN AS A HORN?
//MAKE LVLS TO THE SPEED USING THE NUMBERS ON REMOTE. 

void setup() {
  irrecv.enableIRIn(); //STARTS RECEIVER
  Serial.begin(9600);

  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  analogWrite(enA, 90);
  analogWrite(enB, 90);
}

void loop() {
  if (irrecv.decode(&results)){
    
    /* print the hex code value on the serial monitor */
    Serial.println(results.value);
    delay(5);

    /* resume function according to hex code */
    irrecv.resume();
    setSpeed(results.value);
  }

  if(results.value == 16748655){
    moveForward();
  }
  if(results.value == 16769055){
    moveBackward();
  }
  if(results.value == 16753245 || results.value == 4294967295){
    moveBrake();
  }
  if(results.value == 16761405){
    moveTurn(1);
  }
  if(results.value == 16720605){
    moveTurn(2);
  }

  results.value = 0;
  /*
   up = 16748655
   down = 16769055
   Func/stop = 16769565
   Power = 16753245
   left = 16720605
   right = 16761405
  */
}
