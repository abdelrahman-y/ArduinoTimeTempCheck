
unsigned long seconds;
int hour = 0; // what hour the program starts with
int minute = 0;
 //We'll start by adding our libraries

#include <LiquidCrystal.h>

#include  <SimpleDHT.h>

//Declaring digital pin no 6 as the dht11 data pin

int  pinDHT11 = 6;
SimpleDHT11 dht11;

//Declaring the lcd pins

const  int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en,  d4, d5, d6, d7);

const int pinone = 8; // the pin that the arduino is reading minit 
const int pintwo = 13; // the pin that the arduino is reading 
const int pinthree = 7; // the pin that the arduino is reading hour
int statemn = 0;
int statehr = 0;
void setup() {
// Don't forget to choose 9600 at the  port screen
  
  Serial.begin(9600);
 
//Telling our lcd to start up
  
  lcd.begin(16, 2);
    lcd.setCursor(0,0);
  lcd.print("TEMP Sensor V2.1");
    lcd.setCursor(0,1);
  lcd.print("By Alsafwa Grp.");
  seconds = 0;
 delay(5000);
 lcd.clear();   
   
}

void loop() {

  //These  serial codes are for getting readings on the port screen aswell as the LCD display,  since they'll offer us a more detailed interface
  statemn = digitalRead(pinone);
  statehr = digitalRead(pinthree);
  Serial.print("Time: ");
Serial.println(seconds);
delay(1); // 1000 milliseconds = 1 second
seconds=seconds+1;

  Serial.println("=================================");
  Serial.println("DHT11 readings...");
  
 
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;

  //This bit will  tell our Arduino what to do if there is some sort of an error at getting readings  from our sensor
  if ((err = dht11.read(pinDHT11, &temperature, &humidity, NULL))  != SimpleDHTErrSuccess) {
    Serial.print("No reading , err="); Serial.println(err);delay(1000);
    return;
  }
  
lcd.setCursor(13,1);
lcd.print(seconds); // display seconds
lcd.print("s");  // 1 second passes


lcd.setCursor(10,1);
lcd.print(minute); // display minutes
lcd.print(":");


lcd.setCursor(7,1);
lcd.print(hour); // display hour
lcd.print(":");



if(statehr == HIGH){ // When switch is pressed it will read HIGH
    
    hour++; // LEFT BUTTON - add a hour

    
    lcd.setCursor(0,0);
    lcd.print("Adjust Hour      ");
}
    else if(statemn == HIGH){ // When switch is pressed it will read HIGH
    
      minute++; //MIDDLE BUTTON - add a minute

      
      lcd.setCursor(0,0);
      lcd.print("Adjust Minute   ");
    }

    
  else{
    lcd.setCursor(0,0);
    lcd.print("[HOUR][MIN][SEC]"); //RIGHT BUTTON - show info 
  }


delay (5000);
lcd.clear();
  Serial.print("Readings: ");
  Serial.print((int)temperature);  Serial.print(" Celcius, ");
  Serial.print((int)humidity); Serial.println("  %");
 
  //Telling our lcd to refresh itself every 0.75 seconds
  
  //Choosing the first line and row
  lcd.setCursor(0,0);
  //Typing Temp:  to the first line starting from the first row
  lcd.print("Temp: ");
  //Typing  the temperature readings after "Temp: " 
  lcd.print((int)temperature);
  //Choosing the second line and first row
  lcd.setCursor(0,1);
  //Typing  Humidity(%): to the second line starting from the first row
  lcd.print("Humidity(%):  ");
  //Typing the humidity readings after "Humidity(%): "
  lcd.print((int)humidity);
  
  
  
  
  delay(5000);
  lcd.clear();
if (seconds >= 60){
  seconds = 0;
  minute = minute + 1;  // count up to a minute
  

  
if (minute >= 60){
minute=0;
hour = hour + 1; // count up to a hour 


 
if (hour == 13){ // clock does not pass 12, after 12, the next number should be 1
hour = 1;


}
}
}
}

