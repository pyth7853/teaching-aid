/*
SimpleReceive
This sketch displays text strings received using VirtualWire
Connect the Receiver data pin to Arduino pin 11
*/ 

char inf[4];
#include <Servo.h> 
Servo myservo1;  // create servo object to control a servo 
Servo myservo2;  
Servo myservo3; 


int val_1;    // variable to read the value from the analog pin 
int val_2;    
int val_3;    

#include <SoftwareSerial.h>   // �ޥε{���w

// �w�q�s���Ť��Ҳժ��ǦC��
SoftwareSerial BT(8, 9); // �����}, �ǰe�}
void setup()
{
  BT.begin(9600);
  Serial.begin(9600);
  pinMode(13, OUTPUT); 
  Serial.println("Device is ready");

  myservo1.attach(5,500,2400);  // attaches the servo on pin 1 to the servo object 
  myservo2.attach(6,500,2400);  
  myservo3.attach(4,500,2500);  
 
  myservo3.write(val_3);                  // sets the servo position according to the scaled value 
  delay(500);

}

#define leftMotorCC 1675
#define rightMotorCC 725

#define leftMotorAntiCC 725
#define rightMotorAntiCC 1675

#define leftMotorStop 1450
#define rightMotorStop 1450

void forwardJudgeCmd2nd(){
  switch(inf[1]){
    case '2':  //go
      Serial.println("forward_go");
      val_1 = leftMotorCC;
      val_2 = rightMotorCC;
      break;
    case '0':  //left
      Serial.println("forward_left");
     val_1 = leftMotorStop;
      val_2 = rightMotorCC;
      
      break;    
    case '1':  //right
      Serial.println("forward_right");
      val_1 = leftMotorCC;
      val_2 = rightMotorStop;
      break;    
  }
  
      myservo1.writeMicroseconds(val_1);

  
      myservo2.writeMicroseconds(val_2);   
}

void backJudgeCmd2nd(){
  switch(inf[1]){
    case '2':  //go
      Serial.println("back_go");
      val_1 = leftMotorAntiCC;
      val_2 = rightMotorAntiCC;
      break;
    case '0':  //left
      Serial.println("back_left");
      val_1 = leftMotorStop;
      val_2 = rightMotorAntiCC;
      break;    
    case '1':  //right
      Serial.println("back_right");
      val_1 = leftMotorAntiCC;
      val_2 = rightMotorStop;
      break;    
  }
  
      myservo1.writeMicroseconds(val_1);

  
      myservo2.writeMicroseconds(val_2);    
}

byte cmmd[20];
int insize;
void readCmdFromBT(){
    if ((insize=BT.available())>0){
       Serial.print("input size = "); 
       Serial.println(insize);
       for (int i=0; i<insize; i++){
         Serial.print(cmmd[i]=char(BT.read()));
         Serial.print("\n"); 
      }  
        delay(100);
    }

}
int isOdd=1;
void loop(){
  readCmdFromBT();
  
  for (int i = 0; i < 3 ; i++){
    inf[i]=cmmd[i];
  }
      
  
  switch(inf[0]){
    case '2':  //forward
      forwardJudgeCmd2nd();
      break;
    case '0':  //stop
      Serial.println("stop");     
        myservo1.writeMicroseconds(leftMotorStop);
        if(isOdd){
            myservo2.writeMicroseconds(rightMotorStop+200);
            isOdd=0;
        }else{
            myservo2.writeMicroseconds(rightMotorStop-200);
            isOdd=1;
        }
      break;
    case '1':  //back
      backJudgeCmd2nd();
      break;
  }
  if(inf[0]!='0'){
        switch(inf[2]){
        case '0':  //left
           myservo3.writeMicroseconds(0);
          break;
        case '1':  //right
            myservo3.writeMicroseconds(2500);
          break;
        case '2':  //middle
            myservo3.writeMicroseconds(1500);
          break;
        case '3':  //middle
            myservo3.writeMicroseconds(random(500,2500));
          break;   
      }
  }else{
              myservo3.writeMicroseconds(1500);
  }
//  if (inf[0] == '2' || inf[0] == '1'){
//   //SoftwareServo::refresh(2); //update all pin
//   SoftwareServo::refresh(1); //update all pin
//  }

 
    Serial.println(inf);
    if(inf[0]=='a'){
       digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
    }
}                               
/*
#include <SoftwareSerial.h>
#include <Wire.h>`


int LED = 13;
SoftwareSerial I2CBT(8, 9);

void setup() {
  Serial.begin(9600);
  I2CBT.begin(9600);//bluetooth baud rate  
  pinMode(LED, OUTPUT);    
}

///////////////////main///////////////////////////

void loop() {

  byte cmmd[20];
  int insize;
  
  while(1){

//read message from bluetooth

    if ((insize=I2CBT.available())>0){
       Serial.print("input size = "); 
       Serial.println(insize);
       for (int i=0; i<insize; i++){
         Serial.print(cmmd[i]=char(I2CBT.read()));
         Serial.print("\n"); 
      }  
        delay(100);
    }
  } //while
  delay(100);
}

*/
