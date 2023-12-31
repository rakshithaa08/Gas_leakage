#include <LiquidCrystal.h>
#include <SoftwareSerial.h> // Library for using serial communication
#include <EEPROM.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);
SoftwareSerial SIM900(2,3); // Pins 10, 11 are used as used as software serial pins TX AND RX RESP
String incomingData;   // for storing incoming serial data
boolean state=0;
String number="";
unsigned char FLAG_ON=0;
int gasValue = A0; // smoke / gas sensor connected with analog pin A1 of the arduino / mega.
int data = 0;

int str=4;
int stp=5;
int stt=6;
int st=0,i;
void pumpon(void);
void pumpoff(void);
void initialise(void);
void callprocess(void);

void setup()
{ 
pinMode(11, OUTPUT);
  lcd.init();
  // Turn on the blacklight and print a message.
  lcd.backlight();
  lcd.setCursor(0,0);
 lcd.print (" Gas Leakage ");
lcd.setCursor(0,1);
lcd.print (" Detector Alarm ");
delay(3000);
lcd.clear();

initialise();  
}

////////////////////////////////////////////////////////////////////////////////////////////
void loop()
{
    digitalWrite(11, LOW);
if(SIM900.available()){
incomingData = SIM900.readString();   
Serial.println(incomingData );
}
data = analogRead(gasValue);
Serial.print("Gas Level: ");
Serial.println(data);
lcd.print ("Gas Scan is ON");
lcd.setCursor(0,1);
lcd.print("Gas Level: ");
lcd.print(data);
delay(1000);
  if ( data > 100) //
  {
   digitalWrite(11,HIGH);
   lcd.clear();
lcd.setCursor(0,0);
lcd.print("Gas Level Exceed");
lcd.setCursor(0,1);
lcd.print("SMS Sent");
delay(1000);
    SIM900.print("AT+CMGS=\"8105097232\"\r"); // Replace it with your mobile number
    delay(100);
    SIM900.print("EXESSIVE GAS LEACKAGE ");   // The SMS text you want to send
    delay(100);
    SIM900.print((char)26);  // ASCII code of CTRL+Z
   SIM900.println();
   delay(5000);
  
  }
  else
{
Serial.print("Gas Level Low");
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Gas Level Normal");
delay(1000);
}
}



void initialise(void)
{
  pinMode(str, OUTPUT); //START RELAY
  pinMode(stp, OUTPUT); //STOP RELAY
  digitalWrite(str, LOW);                                                                  
  digitalWrite(stp, LOW);
    pinMode(stt, OUTPUT); //STOP RELAY
  digitalWrite(st, LOW); 
  Serial.begin(9600); // baudrate for serial monitor
  SIM900.begin(9600); // baudrate for GSM shield
//  //delay(10000);
//  SIM900.print("AT\r");
//  delay(100);
//  SIM900.print("AT+CMGF=1\r");
//  delay(100);
//  SIM900.print("AT+CNMI=2,2,0,0,0\r");
//  delay(100);
//  SIM900.print("AT&W\r");
//  delay(4000);
//  SIM900.println("AT+CMGDA=ALL");
//  delay(100);
//  SIM900.print("AT+CMGS=\"8105097232\"\r"); // Replace it with your mobile number
//  delay(100);
//  SIM900.print("GAS LEACKAGE DETECTOR");   // The SMS text you want to send
//  delay(100);
//  SIM900.print((char)26);  // ASCII code of CTRL+Z
// SIM900.println();

 

}
