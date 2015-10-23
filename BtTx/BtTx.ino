  /*
SimpleSend
This sketch transmits a short text message using the VirtualWire library
connect the Transmitter data pin to Arduino pin 12
*/
int direct;
int fort;
int fire;
int a1;
int a2;
char inf[4];
int b1; //fort
int b2; //fort
int b3; //lazer fire
int TimePre;
int TimeNow;
int ServoCount;
int ServoTer;
#include <SoftwareSerial.h>   // �ޥε{���w

// �w�q�s���Ť��Ҳժ��ǦC��
SoftwareSerial BT(8, 9); // �����}, �ǰe�}
#include <VirtualWire.h>
#include "I2Cdev.h"
#include "MPU6050.h"
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#endif  

MPU6050 accelgyro;
int16_t ax, ay, az;
int16_t gx, gy, gz;
#define OUTPUT_READABLE_ACCELGYRO
#define LED_PIN 13
bool blinkState = false;
void setup()
{

	BT.begin(9600);//bluetooth baud rate  	
	Serial.begin(38400);
	#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
	Wire.begin();
	#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
	Fastwire::setup(400, true);
	#endif  
	accelgyro.initialize();

	// Initialize the IO and ISR
	vw_setup(2000); // Bits per sec
	pinMode(2, INPUT_PULLUP);
	pinMode(3, INPUT_PULLUP);
	pinMode(4, INPUT_PULLUP);
	pinMode(5, INPUT_PULLUP);
	TimePre=millis();
}
void loop(){
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  //button=digitalRead(2);
  a1=digitalRead(2);  // high �e�i , low ��h
  a2=digitalRead(3);  //�}��
  
  //button
  if (a1 == HIGH && a2 == LOW) //button forward
    inf[0]='2';
  else if (a1 == LOW && a2 == LOW) //button back
    inf[0]='1';
  else            //button stop
    inf[0]='0';
  
  //direct
  if (ay >= 7000) //right
    inf[1]='1';
  else if (ay <=-7000) //left
    inf[1]='0';
  else
    inf[1]='2'; //go
    
  //fort
  TimeNow=millis();
  b1=digitalRead(4);
  b2=digitalRead(5);
  if (b1 ==HIGH && b2 == LOW)
  	inf[2]='2';
  else if (b1 ==LOW && b2 == LOW)
  	inf[2]='1';
  else
  	inf[2]='0';  //b2=low, then random 
  
  //fire
/*  
b3=digitalRead(4);
  if (b3 == LOW)
  	inf[3]='1';
  else
  	inf[3]='0';
*/  	

//  BT.print(inf[0]);  
//  BT.print(inf[1]);  
//  BT.print(inf[2]);
  BT.print(inf);
  Serial.println(inf);
  delay(100);
  
}
