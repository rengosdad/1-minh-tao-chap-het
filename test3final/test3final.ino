#include <SPI.h>
#include <MFRC522.h>
#include "Stepper.h"
#include "RTClib.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal.h> 
#include "dht.h"

#define dataPin A0
#define IN1 7
#define IN2 6
#define MAX_SPEED 255   
#define MIN_SPEED 0
#define RST_PIN 46
#define SS_PIN 53
#define den 44//////
#define led 17/////
#define led1 43 

int sang = 45;
int UID[4], i;
int cambien = 16; 
int giatri;
int d3=5; 
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
int ID1[4] = {234, 95, 235, 173};
int ID3[4] = {145, 134, 198, 219  }; //Thẻ mở đèn//////////////
int ID2[4] = {76, 167, 43, 46 };////////////////////////
int a = 0;
int n=1;
int khoangcach; 
int temp;
int hum;
const int trig = 14;
const int echo=15; 
const int  sda = 1;
const int scl = 2;
const int stepsPerRevolution = 2048;
char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
  char blt=0; 
unsigned long time1 = 0;
unsigned long thoigian;
Stepper myStepper = Stepper(stepsPerRevolution, 8, 10, 9, 11);
Stepper myStepper2 = Stepper(stepsPerRevolution, 8, 10, 9, 11); 
MFRC522 mfrc522(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x3F,16,2);
RTC_DS1307 rtc;
SoftwareSerial bt(12,13);
dht DHT;

void setup() 
{
 Serial.begin(9600); 
 Serial.println("Ready");  
 SPI.begin();
 lcd.begin (16,2);    
 mfrc522.PCD_Init(); 
 myStepper.setSpeed(10);
 myStepper2.setSpeed(10);
 lcd.init();
 lcd.backlight();
 lcd.setCursor(2,1);
 lcd.init(); 
 lcd.backlight();
 lcd.setCursor(1,0); 
 pinMode(d1,INPUT);
 pinMode(d2,INPUT);
 pinMode(d3,INPUT);
 pinMode(d0,INPUT);
 pinMode(cambien,INPUT);
 pinMode(echo, INPUT);
 pinMode(ld1,OUTPUT);
 pinMode(ld2,OUTPUT);
 pinMode(ld3,OUTPUT);
 pinMode(ld4,OUTPUT);
 pinMode(den,OUTPUT);
 pinMode(IN1, OUTPUT);
 pinMode(IN2, OUTPUT);
 pinMode(trig, OUTPUT); 
 digitalWrite(den,LOW);
 digitalWrite(led,LOW);
 /////////////////////////////////////////////////////////////
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
//////////////////////////////////////////////////////////////
{

    Serial.begin(9600);   

    pinMode(led1, OUTPUT);
    digitalWrite(led, LOW);
    
    SPI.begin();    
    mfrc522.PCD_Init();

}
}


void loop() 
{
  
  
 if (a==1)
 {
  dennhay();
 }
 if (a==0)
 {
  digitalWrite(den, LOW);
    delay(5);
 }
 if ( ! mfrc522.PICC_IsNewCardPresent()) 
 { 
  return; 
 }
 if ( ! mfrc522.PICC_ReadCardSerial()) 
 {  
  return;  
 }
 Serial.print("UID của thẻ: ");   
 for (byte i = 0; i < mfrc522.uid.size; i++) 
 { 
  Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");   
  UID[i] = mfrc522.uid.uidByte[i];
  Serial.print(UID[i]);
 }
 if (UID[i] == ID1[i]) a++;
 if (a == 2) a=0;
 mfrc522.PICC_HaltA();  
 mfrc522.PCD_StopCrypto1();

 if(digitalRead(d0)==HIGH && d0f==0) 
 {
  myStepper2.step(-stepsPerRevolution / 2);
 }
 else if(digitalRead(d1)==HIGH && d1f==0) 
 {
  myStepper.step(2 * stepsPerRevolution);
 }
 if(digitalRead(d2)==HIGH && d2f==0) 
 {
  motor_1_Tien(MAX_SPEED); 
 }
 if(digitalRead(d3)==LOW && d3f==0) 
 {
  motor_1_Dung();
 }

 digitalWrite(trig,0); 
 delayMicroseconds(2); 
 digitalWrite(trig,1); 
 delayMicroseconds(10); 
 digitalWrite(trig,0);
 thoigian = pulseIn (echo, HIGH);
 khoangcach = int(thoigian / 2 / 29.412); 
 Serial.print("Khoảng cách: ");
 Serial.print(khoangcach);
 Serial.println("cm");
 lcd.setCursor(0,1);
 lcd.print("muc nuoc:");
 lcd.setCursor(11,1);
 lcd.print(khoangcach);
 bt.print(khoangcach);
 bt.print(";");
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

 DateTime now = rtc.now();
 lcd.setCursor(0, 0);
 lcd.print("TIME  ");
 if(now.hour()<=9)
 {
  lcd.print("0");
  lcd.print(now.hour());
 }
 else 
 {
  lcd.print(now.hour()); 
 }
 lcd.print(':');
 if(now.minute()<=9)
 {
  lcd.print("0");
  lcd.print(now.minute());
 }
 else 
 {
  lcd.print(now.minute()); 
 }
 lcd.print(':');
 if(now.second()<=9)
 {
  lcd.print("0");
  lcd.print(now.second());
 }
 else 
 {
  lcd.print(now.second()); 
 }
 lcd.print("   ");
 
 giatri = digitalRead(cambien); 
 if (giatri == 1) 
 {
  Serial.print("Có người ");
  digitalWrite(sang,HIGH); //Đèn tắt
 }
 if (giatri == 0)                       
 {
  Serial.print("Không có người");
   digitalWrite(sang,LOW);
 }
 Serial.print("     Giá trị cảm biến là: ");
 Serial.println(giatri);
 Serial.println("  ");
 //bt.print(giatri);
 //bt.print(";");  
 
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
   myStepper.step(2 * -stepsPerRevolution);
   delay(50);
   Serial.println("4444444444");
  }
  else if(blt==5)
  {   
   myStepper.step(2 * stepsPerRevolution);
   Serial.println("55555555555555");
  }
  if(blt==6)
  {
   motor_1_Tien(MAX_SPEED);
   Serial.println("666666666666666");
  }
  else if(blt==7)
  {
   motor_1_Dung();
   Serial.println("77777777777777");
  }
   }

 int readData = DHT.read11(dataPin);
 hum = DHT.humidity;
 temp = DHT.temperature;
 bt.print(temp);
 bt.print(";");
 bt.print(hum); 
 bt.print(";");

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
{

  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  { 
    return; 
  }
  
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {  
    return;  
  }
  
  Serial.print("UID của thẻ: ");   
  
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  { 
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");   
    UID[i] = mfrc522.uid.uidByte[i];
    Serial.print(UID[i]);
  }

  Serial.println("   ");

  if (UID[i] == ID2[i])
  {
    digitalWrite(led1, HIGH);
    Serial.println("Thẻ mở đèn - ĐÈN ON");
  }
  
  else if (UID[i] == ID3[i])
  {
    digitalWrite(led1, LOW);
    Serial.println("Thẻ tắt đèn - ĐÈN OFF");
  }

  else
  {
    Serial.println("Sai thẻ");
  }
  
  mfrc522.PICC_HaltA();  
  mfrc522.PCD_StopCrypto1();

}
}

void dennhay()
{
 if ( (unsigned long) (millis() - time1) > 50 )
 {
  if ( digitalRead(den) == LOW ) 
  digitalWrite(den, HIGH);
  else digitalWrite(den, LOW );
  time1 = millis();
 }
} 

void motor_1_Dung() 
{
 digitalWrite(IN1, LOW);
 digitalWrite(IN2, LOW);
}
 
void motor_1_Tien(int speed) 
{
 speed = constrain(speed, MIN_SPEED, MAX_SPEED);
 digitalWrite(IN1, HIGH);
 digitalWrite(IN2, HIGH);
}
 
void motor_1_Lui(int speed) 
{
 speed = constrain(speed, MIN_SPEED, MAX_SPEED);
 digitalWrite(IN1, LOW);
 analogWrite(IN2, speed);
}
