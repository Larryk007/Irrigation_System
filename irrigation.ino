#include <SoftwareSerial.h>

#define solenoid_valve 4
#define watering_pump 6
#define fswitch2 7
#define moisture_sensor A0

int moisture_value;
int moist_percent;
int fswitch_value;
SoftwareSerial sim(2,3);


void setup () {
    sim.begin(9600);
    Serial.begin(9600);
    pinMode(moisture_sensor,INPUT); 
    pinMode(watering_pump,OUTPUT);
    pinMode(solenoid_valve,OUTPUT);
    pinMode(sense_,OUTPUT);
    pinMode(fswitch2, INPUT_PULLUP);
    sim.println("AT+CNMI=1,2,0,0,0");
    delay(100);
    sim.println("AT+CMGF=1");
    delay(100);
    sim.println("AT+CMGS=\"+254712833708\"\r"); // Replace x with mobile number
    delay(100);
    sim.println("System is Active.");// The SMS text you want to send
    delay(100);
    sim.println((char)26); // ASCII code of CTRL+Z
    delay(100);
}


void loop(){
     delayMicroseconds(2);
     delayMicroseconds(10); 
     moisture_value= analogRead(moisture_sensor);
     moist_percent=map(moisture_value,450,1023,100,0);
     fswitch_value=digitalRead(fswitch2);
     
     condition();
     condition2();
}


void sms(){
    sim.println("AT+CNMI=1,2,0,0,0");
    delay(100);
    sim.print("AT+CMGF=1"); 
    delay(100);
    sim.println("AT+CMGS=\"+254712833708\"\r");
    delay(100);
    sim.println("Moisture Content Low, IRRIGATION IS ON");
    delay(100);
    Serial.println("Moisture Content Low, IRRIGATION IS ON");
    delay(100);
    sim.println((char)26); 
    delay(100);
    Serial.println((char)26);
    sim.println();
}

void sms2(){
    sim.println("AT+CNMI=1,2,0,0,0");
    delay(100);
    sim.print("AT+CMGF=1"); 
    delay(100);
    sim.println("AT+CMGS=\"+254712833708\"\r");
    delay(100);
    sim.println("Optimum moisture Level Reached, IRRIGATION COMPLETE"); 
    delay(100);
    Serial.println("Optimum moisture Level Reached, IRRIGATION COMPLETE");
    delay(100);
    sim.println((char)26);
    delay(100);
    Serial.println((char)26);
    //delay(10000);
    sim.println();
}

void sms3(){
    sim.print("AT+CMGF=1"); 
     //delay(2000);
    sim.println("AT+CMGS=\"+254712833708\"\r");// recipient's mobile number
    
    sim.println("Tank Water sufficient"); // message to send
    Serial.println("Tank Water sufficient");
    //delay(10000);
    sim.println((char)26); // End AT command with a ^Z, ASCII code 26
    Serial.println((char)26);
    //delay(10000);
    sim.println();
}


void sms4(){
    sim.print("AT+CMGF=1"); 
   // delay(2000);
    sim.println("AT+CMGS=\"+254712833708\"\r");// recipient's mobile number

    sim.println("Tank Water is low"); // message to send
    Serial.println("Tank Water is low");
    //delay(10000);
    sim.println((char)26); // End AT command with a ^Z, ASCII code 26
    Serial.println((char)26);
    //delay(10000);
    sim.println();
}


void condition(){
    if (moisture_value>750){
      sms();
      digitalWrite(solenoid_valve,LOW);
      digitalWrite(watering_pump,LOW);
      delay(10000);
      digitalWrite(solenoid_valve,HIGH);
      digitalWrite(watering_pump,HIGH);
      delay(10000);
    }
      else if (moisture_value<585){
        sms2();
        digitalWrite(solenoid_valve,HIGH);
        digitalWrite(watering_pump,HIGH);
        delay(1000); 
      }
}

void condition2(){
    if(fswitch_value == HIGH)
    {
      sms4();
      digitalWrite(sense_ ,LOW);
     }
     else
     {
      sms3();
      digitalWrite(sense_ ,HIGH);
      }
}
