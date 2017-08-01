long rings[4] = {33600, 37800, 63600, 66000};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  Serial.println("Test");
  Serial.println("At 08:20 " + String(getNextAlarm( 8, 20, 15)));
  Serial.println("At 09:30 " + String(getNextAlarm( 9, 30, 0)));
  Serial.println("At 15:00 " + String(getNextAlarm( 15, 00, 0)));
  Serial.println("At 18:30 " + String(getNextAlarm( 18, 30, 0)));
  Serial.println("==========================");
  Serial.println(33600L / 3600);
  Serial.println((33600L % 3600) / 60);

 
}

void loop() {
  // put your main code here, to run repeatedly:

}

long getNextAlarm(long hours1, long minutes1, long seconds1) {

   /* local variable declaration */
   String myString;
   long timenow = 0;
   long result = rings[0];
   int i;
   timenow = hours1*3600 + minutes1*60 + seconds1;
   for(i = 0; i < 4; i = i + 1){
    Serial.println(String(timenow) + " >> " + String(i) + " >> " + rings[i]);
    if(timenow < rings[i]){
      result = rings[i];
      Serial.println("Found!..");
      break;
    }
   }
   return  result;
}
 



