#define IN1 7
#define IN2 6
#define MAX_SPEED 2150 //từ 0-255
#define MIN_SPEED 0

int d3=5; ////////////////////////////////////
int d3f=0;
int ld1=8;
int ld2=9;
int ld3=10;
int ld4=11;
int d0=2;
int d0f=0;
int d1=3;
int d1f=0;
int d2=4;
int d2f=0;
/////////////////////
const int trig = 14; ////////////////////////
const int echo=15; ///////////////////////
const int  sda = 1;
const int scl = 2;
int cambien = 16; ////////////////////
int giatri;
int den = 45;  ///////////////////////////
unsigned long thoigian;
int khoangcach; 

#include "Stepper.h"
const int stepsPerRevolution = 2048;
Stepper myStepper = Stepper(stepsPerRevolution, 8, 10, 9, 11);
Stepper myStepper2 = Stepper(stepsPerRevolution, 8, 10, 9, 11);

#include "RTClib.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F,16,2); //LCD 16x02, địa chỉ I2C là 0X27
RTC_DS1307 rtc;
char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
//////////////////////////////////////////////////////////////////////////////////////////////
#include <SoftwareSerial.h>
SoftwareSerial bt(12,13);
//SoftwareSerial Bluetooth(50,51);
#define led 17

#include <LiquidCrystal.h> //không cần hiển thị lên 
#include "dht.h"
#define dataPin A0      // xác định lại chân
dht DHT;

int temp;
int hum;
                                              //int mucnuoc;   /Value // cảm biến siêu âm
char blt=0;                                             //int khach;    /ON/OF //cảm biến ánh sáng
                                              //char Incoming_value=0;
                                              //pinMode(AA,OUTPUT);//BẬT TẮT ĐÈN
                                              //pinMode(BB,OUTPUT);//DI CHUYỂN
                                              //pinMode(CC,OUTPUT);//BƠM NƯỚC
                                              //pinMode(DD,OUTPUT);//NÂNG HẠ( STEP motor)



void setup() {
 
 Serial.begin(9600); 
Serial.println("Ready");
 bt.begin(9600); 
 bt.println("Ready");
pinMode(led, OUTPUT); 
 digitalWrite(led,LOW);
  
/////////////////////////////////////// 
{
Serial.begin(9600);
pinMode(IN1, OUTPUT);
pinMode(IN2, OUTPUT);
pinMode(d1,INPUT);
pinMode(d2,INPUT);
pinMode(d3,INPUT);
pinMode(d0,INPUT);
pinMode(ld1,OUTPUT);
pinMode(ld2,OUTPUT);
pinMode(ld3,OUTPUT);
pinMode(ld4,OUTPUT);
pinMode(cambien, INPUT);
pinMode(den,OUTPUT);
digitalWrite(den,LOW);
myStepper.setSpeed(10);
myStepper2.setSpeed(10);
}
lcd.begin (16,2);  // initialize the lcd 
  lcd.backlight();//To Power ON the back light
  if (! rtc.begin()) 
  {
    lcd.print("Couldn't find RTC");
    while (1);
  }
if (! rtc.isrunning()) 
  {
    lcd.print("RTC is NOT running!");
  }

  Serial.begin(9600); //Mở cổng Serial ở 9600
  pinMode(trig, OUTPUT); //Chân trig xuất tín hiệu
  pinMode(echo, INPUT); //Chân echo nhận tín hiệu
  
   lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(2,1);
  lcd.init(); //Khởi động LCD
  lcd.backlight(); //Bật đèn nền
  lcd.setCursor(1,0); //Cột 1, hàng 0
}

void motor_1_Dung() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
}
 
void motor_1_Tien(int speed) { //speed: từ 0 - MAX_SPEED
    speed = constrain(speed, MIN_SPEED, MAX_SPEED);//đảm báo giá trị nằm trong một khoảng từ 0 - MAX_SPEED - http://arduino.vn/reference/constrain
    digitalWrite(IN1, HIGH);// chân này không có PWM
    analogWrite(IN2, 255 - speed);
}
 
void motor_1_Lui(int speed) {
    speed = constrain(speed, MIN_SPEED, MAX_SPEED);//đảm báo giá trị nằm trong một khoảng từ 0 - MAX_SPEED - http://arduino.vn/reference/constrain
    digitalWrite(IN1, LOW);// chân này không có PWM
    analogWrite(IN2, speed);
}
////////////////////////////////////////////// 



void loop(){
  { 
{
  if(digitalRead(d0)==HIGH && d0f==0) {
    myStepper2.step(-stepsPerRevolution / 2);
  delay(50); 
  }
  else if(digitalRead(d1)==HIGH && d1f==0) {
myStepper.step(2 * stepsPerRevolution);
  delay(50);
  }
 
  if(digitalRead(d2)==HIGH && d2f==0) {
   
    motor_1_Tien(MAX_SPEED); // motor 1 tiến
  delay(5000);
  }
  if(digitalRead(d3)==LOW && d3f==0) {
     motor_1_Dung();
     delay(10);
  }
}
////////////////////////////////////////////////////////////
{
  digitalWrite(trig,0); //Tắt chân trig
  delayMicroseconds(2); 
  digitalWrite(trig,1); //bật chân trig để phát xung
  delayMicroseconds(10); //Xung có độ rộng là 10 microsecond
  digitalWrite(trig,0);
  thoigian = pulseIn (echo, HIGH);
  khoangcach = int(thoigian / 2 / 29.412); 
  delay(500);
  Serial.print("Khoảng cách: ");
  Serial.print(khoangcach);
  Serial.println("cm");
 
  lcd.setCursor(0,1);
  lcd.print("muc nuoc:");
  lcd.setCursor(11,1);
  lcd.print(khoangcach);
  if (khoangcach < 10)
  {
    lcd.setCursor(12,1);
    lcd.print(" ");
  }
  
  if (khoangcach >= 10 && khoangcach < 100)
  {
    lcd.setCursor(13,1);
    lcd.print(" ");
  }
  {
    DateTime now = rtc.now();
    lcd.setCursor(0, 0);
     lcd.print("TIME  ");
    if(now.hour()<=9)
    {
      lcd.print("0");
      lcd.print(now.hour());
    }
    else {
     lcd.print(now.hour()); 
    }
    lcd.print(':');
    if(now.minute()<=9)
    {
      lcd.print("0");
      lcd.print(now.minute());
    }
    else {
     lcd.print(now.minute()); 
    }
    lcd.print(':');
    if(now.second()<=9)
    {
      lcd.print("0");
      lcd.print(now.second());
    }
    else {
     lcd.print(now.second()); 
    }
    lcd.print("   ");
}
{
  giatri = digitalRead(cambien); //Đọc giá trị digital từ cảm biến và gán vào biến giatri
delay(100);
  if (giatri == 1) //Nếu giá trị đọc từ cảm biến là 1
  {
    Serial.print("Có người ");
    digitalWrite(den,HIGH); //Đèn bật
  }
    if (giatri == 0)                        //else 
  {
    Serial.print("Không có người");
    digitalWrite(den,LOW); //Đèn tắt
  }
  Serial.print("     Giá trị cảm biến là: ");
  Serial.println(giatri);
  Serial.println("  ");
}  
  delay(50);
 
}
}

{
 if(bt.available()>0)
 {
 blt = bt.read();
 Serial.println("00000000000000000");
  if(blt==2)
  {
    digitalWrite(led, LOW);
   Serial.println("222222222");
  }
  else if(blt==3)
  {
    digitalWrite(led, HIGH);
    Serial.println("333333333333");
  }
  if(blt==4)
  {
   
    myStepper.step(2 * -stepsPerRevolution);//myStepper2.step(-stepsPerRevolution / 2);
  delay(50);
  
    
   Serial.println("4444444444");
  }
  else if(blt==5)
  {
   
  myStepper.step(2 * stepsPerRevolution);
  delay(50);
  
   
    Serial.println("55555555555555");
  }
  if(blt==6)
  {
      motor_1_Tien(MAX_SPEED); // motor 1 tiến
  delay(5000);
  
    
   Serial.println("666666666666666");
  }
  else if(blt==7)
  {
     motor_1_Dung();
     delay(10);
   
    Serial.println("77777777777777");
  }
 }
}  
  int readData = DHT.read11(dataPin);
 delay(100); 
  hum = DHT.humidity;
  temp = DHT.temperature;
 


 bt.print(temp);//send distance to MIT App
 bt.print(";");
 bt.print(hum); //send distance to MIT App 
 bt.print(";");
 bt.print(khoangcach);//khoản cách sensor siêu âm
 bt.print(";");
 bt.print(giatri);//
 bt.print(";");
                                                     // bt.print(mucnuoc); //send distance to MIT App value giá trị mức nước
                                                     //bt.println(";");
                                                     // bt.print(khach); //send distance to MIT App ON/OFF Giá trị cảm biến ánh sáng
                                                     //bt.println(";");
                                                     //        }
                                                     //      {
                                                      //            if(Incoming_value=='1BT')
                                                      //            digitalWrite(AA,HIGH);  //Bật đèn
                                                     //             else if(Incoming_value=='0BT')
                                                     //             digitalWrite(AA,LOW);   //TẮT đèn
                                                     //             if(Incoming_value==1DC')
                                                      //            digitalWrite(BB,HIGH);  //Bật cánh quạt nước
                                                     //             else if(Incoming_value=='0BT')
                                                     //             digitalWrite(BB,LOW);    //Tắt cánh quạt nước
                                                     //             if(Incoming_value=1BN')
                                                      //            digitalWrite(CC,HIGH);   //Bật bơm nước
                                                     //             else if(Incoming_value=='0BN')
                                                     //             digitalWrite(CC,LOW);    //Tắt bơm nước
                                                     //             if(Incoming_value=1NH')
                                                      //            digitalWrite(DD,HIGH);    //Chạy step +
                                                     //             else if(Incoming_value==0NH')
                                                     //             digitalWrite(DD,LOW);     //Chạy Step -
 
                                                    //        }
  delay(1000);
}
