//Program to set up RTC time

#include <LiquidCrystal.h>  // Лобавляем необходимую библиотеку
LiquidCrystal lcd(7, 6, 5, 4, 3, 2); // (RS, E, DB4, DB5, DB6, DB7)

//Инициализация часов
#include <Wire.h>
#include <RTClib.h>
RTC_DS3231 rtc;
long rings[] = {27000,28800,32400,34800,35400,37800,38400,40800,41700,44100,45000,47400,48600,51000,51900,54300,54900,57300,57900,60300,60900,63300,63600,66000,66600,70200};
#if defined(ARDUINO_ARCH_SAMD)
  // for Zero, output on USB Serial console, remove line below if using programming port to program the Zero!
   #define Serial SerialUSB
#endif


DateTime tt;  //variable of type DateTime

void setup(){ 
  lcd.clear();
  lcd.setCursor(0, 0);  lcd.print("Gordey corp.");
  // Start serial port
  Serial.begin(57600); 
  
  // Wait while RTC starts
  if (! rtc.begin()) { 
    Serial.println("Couldn't find RTC");
    while (1);   // sketch halts in an endless loop
  }

  rtc.adjust(DateTime(2017, 5, 4, 13, 14, 30));   // would set to February 28, 2015 at 14:50:00 (2:50pm)
  Serial.println("Time set 1");
  
     
}

void loop(){
  int nextAlarm = getNextAlarm(tt.hour(), tt.minute(), tt.second());
  lcd.clear();
  lcd.setCursor(0, 0);              // Устанавливаем курсор в начало 1 строки  lcd.print("Hello, world!");
  lcd.print(realtime(tt.hour()));
  lcd.print(':');
  lcd.print(realtime(tt.minute()));
  lcd.print(':');
  lcd.print(realtime(tt.second()));
  lcd.setCursor(0, 1);
  lcd.print("Next: ");
  lcd.print((nextAlarm - (nextAlarm % 3600))/3600);
  lcd.print(':');
  lcd.print((nextAlarm % 3600) / 60);
  lcd.print(':');
  lcd.print("00");
}
String realtime(int num1) {

   //local variable declaration 
   String result;
 
   if (num1 < 10)
      result = "0" + String(num1);
   else
      result = num1;
 
   return result; 
}

int secondsOfDay(int hours, int minutes, int seconds) {

   //local variable declaration 
   int result;
 
   result = hours*3600 + minutes*60 + seconds;
 
   return result; 
}

int ring() {

   //local variable declaration

   Serial.println("RING!!!!!!!!!!!!");
   lcd.clear();
   lcd.setCursor(4, 0);
   lcd.print("RING!!!");
   digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
   delay(2000);              // wait for a second
   digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW

}

long getNextAlarm(long hours1, long minutes1, long seconds1) {

   //local variable declaration /
   String myString;
   long timenow = 0;
   long result = rings[0];
   int i;
   timenow = hours1*3600 + minutes1*60 + seconds1 + 10;
   for(i = 0; i < 26; i = i + 1){
    //Serial.println(String(timenow) + " >> " + String(i) + " >> " + rings[i]);
    if(timenow < rings[i]){
      result = rings[i];
      //Serial.println("Found!..");
      break;
    }
   }
   return  result;
}

