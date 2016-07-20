//--temp_sensor--
#include "DHT.h"
#include <LiquidCrystal.h>
#define DHTPIN 7
#define DHTTYPE AM2301  
DHT dht(DHTPIN, DHTTYPE);

int h = 0;
int t = 0;

//--IR_remote--
#include <IRremote.h>
#include <IRremoteInt.h>
int RECV_PIN = 0;
IRrecv irrecv(RECV_PIN);
decode_results results;

String IR_results = "ffffff";

String IR[]= {"ffa25d", //Power
              "ffe21d", //Menu
              "ff22dd", //Test
              "ff02fd", //+
              "ffc23d", //Return
              "ffe01f", //<<
              "ffa857", //Play
              "ff906f", //>>
              "ff6897", //0
              "ff9867", //-
              "ffb04f", //C
              "ff30cf", //1
              "ff18e7", //2
              "ff7a85", //3
              "ff10ef", //4
              "ff38c7", //5
              "ff5aa5", //6
              "ff42bd", //7
              "ff4ab5", //8
              "ff52ad"}; //9

int sensor_on = 100;

void setup() {
  Serial.begin(9600);
  dht.begin(); //temp_sensor

  irrecv.enableIRIn(); // Start the receiver //IR_sensor
}

void loop() {

  //IR_remote
  
  if (irrecv.decode(&results)){
    String IR_results_temp = String(results.value,HEX);
    if(IR_results_temp != "ffffffff"){
      IR_results = String(results.value,HEX);
    }

    Serial.println(sensor_on);
    
     Serial.println(results.value, HEX);
     irrecv.resume(); // Receive the next value
    }
//    Serial.println(IR_results);
    for(int i = 0; i<20; i++){
       if(IR_results.equals(IR[i])){
        sensor_on = i;
       }
    }

  if(sensor_on==0){
    Serial.println("Power");
  }
  else if(sensor_on==1){
    Serial.println("Menu");
  }
  else if(sensor_on==2){
    Serial.println("Test");
  }
  else if(sensor_on==3){
    Serial.println("+");
  }
  else if(sensor_on==4){
    Serial.println("Return");
  }
  else if(sensor_on==5){
    Serial.println("<<");
  }
  else if(sensor_on==6){
    Serial.println("Play");
  }
  else if(sensor_on==7){
    Serial.println(">>");
  }
  else if(sensor_on==8){
    Serial.println("0");
  }
  else if(sensor_on==9){
    Serial.println("-");
  }
  else if(sensor_on==10){
    Serial.println("C");
  }
  else if(sensor_on==11){
    temp_sensor();
  }
  else if(sensor_on==12){
    Serial.println("2");
  }
  else if(sensor_on==13){
    Serial.println("3");
  }
  else if(sensor_on==14){
    Serial.println("4");
  }
  else if(sensor_on==15){
    Serial.println("5");
  }
  else if(sensor_on==16){
    Serial.println("6");
  }
  else if(sensor_on==17){
    Serial.println("7");
  }
  else if(sensor_on==18){
    Serial.println("8");
  }
  else if(sensor_on==19){
    Serial.println("9");
  }
  else{
    Serial.println("error");
  }
  
}

void temp_sensor() {
  h = dht.readHumidity()*10;
  t = dht.readTemperature()*10;
  if (isnan(t) || isnan(h)) {
    Serial.println("Failed to read from DHT");
  }
  else {
    Serial.print("Temp=");
    Serial.print(t/10);
    Serial.print(".");
    Serial.print(t%10);
    Serial.println(" *C");
    
    Serial.print("Humidity=");
    Serial.print(h/10);
    Serial.print(".");
    Serial.print(h%10);
    Serial.println("% ");
  }
  delay(2000); 
}

