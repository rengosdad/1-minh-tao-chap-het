#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9
#define SS_PIN  10
#define led 7
#define den 8
int UID[4], i;
int ID1[4] = {76, 167, 43, 46 };
int ID2[4] = {145, 134, 198, 219  }; 
int ID3[4] = {234, 95, 235, 173};

int n=0;
unsigned long;
unsigned long time1 = 0;
 unsigned long thoigian;

MFRC522 mfrc522(SS_PIN, RST_PIN);








void setup() 
{
 Serial.begin(9600);   
 pinMode(led, OUTPUT);
  pinMode(den, OUTPUT);
 digitalWrite(led, LOW);   
 digitalWrite(den, LOW);   
 SPI.begin();    
 mfrc522.PCD_Init();
}

void loop() 
{
  if (n==1) lednhay();
  if (n==2) digitalWrite(den, LOW);
  if (n==3) n=0;
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

  
 if (UID[i] == ID1[i])
  {
   digitalWrite(led, HIGH);
   Serial.println("Thẻ mở đèn - ĐÈN ON");
  } 
 else if (UID[i] == ID2[i])
  {
   digitalWrite(led, LOW);
   Serial.println("Thẻ tắt đèn - ĐÈN OFF");
  }
 else if (UID[i] == ID3[i])
  {
 // lednhay();
 n++;
   Serial.println("Thẻ chờ - ĐÈN NHÁY");
   
   
  }
 else
  {
   Serial.println("Sai thẻ");
  }
  
 mfrc522.PICC_HaltA();  
 mfrc522.PCD_StopCrypto1();
 
}
void lednhay()
{
 if ( (unsigned long) (millis() - time1) > 50 )
  {
   if ( digitalRead(den) == LOW ) 
   digitalWrite(den, HIGH);
   else digitalWrite(den, LOW );
   time1 = millis();
  }
 delay (10);
}   
