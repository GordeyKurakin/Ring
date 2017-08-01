//Version 1.1 
//Date 17.12.2016

#include <LiquidCrystal.h>  // Лобавляем необходимую библиотеку
LiquidCrystal lcd(7, 6, 5, 4, 3, 2); // (RS, E, DB4, DB5, DB6, DB7)

//Инициализация часов
#include <Wire.h>
#include <RTClib.h>
RTC_DS3231 rtc;

#if defined(ARDUINO_ARCH_SAMD)
  // for Zero, output on USB Serial console, remove line below if using programming port to program the Zero!
   #define Serial SerialUSB
#endif

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
const char* months[] = {"January", "February", "March", "April", "May", "June", "July", "August","September", "October", "November", "December"};
long rings[] = {32400,34800,35400,37800,38400,40800,41700,44100,45000,47400,48600,51000,51900,54300,54900,57300,57900,60300,60900,63300,63600,66000};
long nextAlarm;
DateTime tt;  //variable of type DateTime

void setup(){ 
  lcd.begin(16, 2); // Задаем размерность экрана
  Serial.println("LCD started.");
  
  lcd.clear();
  lcd.setCursor(0, 0);  
  lcd.print("Gordey Ring Auto");
  lcd.setCursor(0, 2);  
  lcd.print("ver. 1.1");
  delay(3000);
  // Start serial port
  Serial.begin(57600); 
  
  // Wait while RTC starts
  if (! rtc.begin()) { 
    Serial.println("Couldn't find RTC");
    while (1);   // sketch halts in an endless loop
  }
  Serial.println("Time set 1");
  
  // Wait while RTC starts
  if (! rtc.begin()) { 
    Serial.println("Couldn't find RTC");
    while (1);   // sketch halts in an endless loop
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // set the RTC date & time - to the time this sketch was compiled
    // rtc.adjust(DateTime(__DATE, TIME__));
 
    // set the RTC date & time - to any time you choose example 
    //rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));      // would set to January 21, 2014 at 3:00:00 (3am)
    Serial.println("Time set 1");
    rtc.adjust(DateTime(2017, 2, 27, 20, 15, 00));   // would set to February 28, 2015 at 14:50:00 (2:50pm)
  }

  //rtc.adjust(DateTime(2016, 10, 23, 12, 5, 00));
  //Serial.println("Time set 2");
  
  pinMode(13, OUTPUT);  //Setting initial alarm
  tt = rtc.now(); // Get current time
  
  //Set up next alarm
  nextAlarm = getNextAlarm(tt.hour(), tt.minute(), tt.second());
  Serial.println("Setting next alarm (seconds): " + String(nextAlarm));
  Serial.println("Setting next alarm: " + String(nextAlarm / 3600) + ":" + String((nextAlarm % 3600) / 60));
  rtc.setAlarm1Simple(nextAlarm / 3600, (nextAlarm % 3600) / 60 );   
}

void loop(){
  
  tt = rtc.now(); // Get current time               

  Serial.print(realtime(tt.hour()));
  Serial.print(':');
  Serial.print(realtime(tt.minute()));
  Serial.print(':');
  Serial.println(realtime(tt.second()));

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
  lcd.print(realtime((nextAlarm % 3600) / 60));
  



  
  delay(1000);

  if (rtc.checkIfAlarm(1)) {      //Give a school ring!
      ring(); 
      
      //Set up next alarm
      nextAlarm = getNextAlarm(tt.hour(), tt.minute(), tt.second());
      Serial.println("Setting next alarm (seconds): " + String(nextAlarm));
      Serial.println("Setting next alarm: " + String(nextAlarm / 3600) + ":" + String((nextAlarm % 3600) / 60));
      rtc.setAlarm1Simple(nextAlarm / 3600, (nextAlarm % 3600) / 60 );   
  }
  else {
      Serial.println("No alarm.");
  }
  
  
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
   if(tt.dayOfTheWeek() == 6 || tt.dayOfTheWeek() == 0){
      lcd.clear();
      lcd.setCursor(4, 0);
      lcd.print("WEEKEND!!!");
   }
   else{
     Serial.println("RING!!!!!!!!!!!!");
     lcd.clear();
     lcd.setCursor(4, 0);
     lcd.print("RING!!!");
     digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
     delay(2000);              // wait for a second
     digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
   } 
}

long getNextAlarm(long hours1, long minutes1, long seconds1) {

   //local variable declaration /
   String myString;
   long timenow = 0;
   long result = rings[0];
   int i;
   timenow = hours1*3600 + minutes1*60 + seconds1 + 10;
   for(i = 0; i < 22; i = i + 1){
    //Serial.println(String(timenow) + " >> " + String(i) + " >> " + rings[i]);
    if(timenow < rings[i]){
      result = rings[i];
      //Serial.println("Found!..");
      break;
    }
   }
   return  result;
}
