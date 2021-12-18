//code by gaganjit Singh Virdi

#include <DS3231.h>
#include <Servo.h>
#include <LiquidCrystal.h> // includes the LiquidCrystal Library 

Servo servo;
Servo servo2;
int state = 0;
DS3231  rtc(SDA, SCL);
LiquidCrystal lcd(12,A3, 4, 5, 6, 7); // Creates an LC object. Parameters: (rs, enable, d4, d5, d6, d7) 
int buzzer = 9;
const int buttonPin = 10;
int buttonState = 0;
int alarm = "05:00:00";
void setup() { 
   Serial.begin(9600);
   
   
   servo.attach(11);
   servo.write(90);
   servo2.attach(13);
   servo2.write(90);
  
   
   rtc.begin(); 
   //rtc.setDOW(TUESDAY);
   //rtc.setTime(19,30,30);
   lcd.begin(16,2); 
   pinMode(buttonPin, INPUT_PULLUP);
 
}
void loop() { 
  if(Serial.available() > 0){ // Checks whether data is comming from the serial port
       state = Serial.read();}. // state is what hols the value that is send from the phone. 
  
   buttonState = digitalRead(buttonPin);
   String time = rtc.getTimeStr();
   lcd.setCursor(0,0);
   lcd.print("Time:  ");
   lcd.print(time);
   lcd.setCursor(0,1);
   lcd.print("Day: ");
   lcd.print(rtc.getDOWStr());
  
         
    if (state == '0') {
 
    Serial.println(" OFF"); // Send back, to the phone, the String "LED: ON"
    servo2.write(0);
    delay(1000);
    servo2.write(90);
    delay(1000);
    state = 0;
        }
        
    if (state == '1') {
 
   
    Serial.println("ON");
    servo.write(180);
    delay(1000);
    servo.write(90);
    delay(1000);
     state = 0;
    
    
       } 
 
    
    
  
  
    
   if(time == alarm){
    int i = 100;
    int g = 1000;
    servo.write(180);
    delay(1000);
    servo.write(90);
    delay(1000);
    
   while(buttonState == HIGH){
         
        lcd.setCursor(0,1);
        lcd.clear();
        lcd.print("Outh jo!!!");
        tone(buzzer,i);
        delay(100);
        noTone(buzzer);
        delay(100);
        i += 50;
        buttonState = digitalRead(buttonPin);
      }
      
   }
   
}