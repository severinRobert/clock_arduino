#include <IRremote.h>
#include <Wire.h>
#include "DS1307.h"

int latch = 9;  //74HC595  pin 9 STCP
int clockDig = 10; //74HC595  pin 10 SHCP
int data = 8;   //74HC595  pin 8 DS
int D1 = 4; //displayer pin of digit 1
int D2 = 5; //displayer pin of digit 2
int D3 = 6; //displayer pin of digit 3
int D4 = 7; //displayer pin of digit 4
int point = 11;
int delai = 3;
int IrReceiverPin = 12;  // pin of the IR receiver 
int minPlus = 0;
int heurePlus = 0;

DS1307 clock;   // instance of clock
IRrecv irrecv(IrReceiverPin);   // instance of irrecv
decode_results results;     // to store the received button code

unsigned char table[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x00};

void setup() {
  pinMode(latch,OUTPUT);
  pinMode(clockDig,OUTPUT);
  pinMode(data,OUTPUT);
  pinMode(D1,OUTPUT);
  pinMode(D2,OUTPUT);
  pinMode(D3,OUTPUT);
  pinMode(D4,OUTPUT);
  pinMode(point,OUTPUT);
  
  Serial.begin(9600);
  clock.begin();

  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("Starting IR-receiver...");
  irrecv.enableIRIn();
  Serial.println("IR-receiver active");
  digitalWrite(LED_BUILTIN,LOW);
}
void Display(unsigned char num)
{

  digitalWrite(latch,LOW);
  shiftOut(data,clockDig,MSBFIRST,table[num]);
  digitalWrite(latch,HIGH);
  
}
void loop() 
{ 
  if(irrecv.decode(&results)) {
    Serial.println(results.value,HEX);
    switch(results.value) {
      case 0xFF629D:
        heurePlus += 1;
        Serial.println("heures augmentée");
        break;
        
      case 0xFFA857:
        heurePlus -= 1;
        Serial.println("heures diminuée");
        break;
        
      case 0xFFC23D:
        minPlus += 1;
        Serial.println("minutes augmentée");
        break;
        
      case 0xFF22DD:
        minPlus -= 1;
        Serial.println("minutes diminuée");
        break;
        
      default:
        Serial.println("commande non reconnue");
        break;
    }
    if(minPlus == -60) {
      minPlus = 0;
      heurePlus -= 1;
    } else if(minPlus == 60) {
      minPlus = 0;
      heurePlus += 1;
    }
    if(heurePlus == -24 or heurePlus == 24) {
      heurePlus = 0;
    }
    irrecv.resume();
  }
  clock.getTime();/*
  Serial.print(clock.hour);
  Serial.print(":");
  Serial.print(clock.minute);
  Serial.print(":");
  Serial.print(clock.second);
  Serial.print("\n");*/
    
  digitalWrite(D1,LOW);
  digitalWrite(D2,HIGH);
  digitalWrite(D3,HIGH);
  digitalWrite(D4,HIGH);
  digitalWrite(point,LOW);

  int heures = clock.hour + heurePlus;
  int minutes = clock.minute + minPlus;

  if(minutes < 0) {
    minutes = 60 + minutes;
    heures -= 1;
  } else if(minutes >= 60) {
    minutes = minutes - 60;
    heures += 1;
  }
  if(heures < 0) {
    heures = 24 + heures;
  } else if(heures >= 24) {
    heures = heures - 24;
  }
  
  int b2 = heures % 10;
  int b1 = (heures - b2) / 10;
  int b4 = minutes % 10;
  int b3 = (minutes - b4) / 10;
  
  Display(b1);
  delay(delai);
  
  digitalWrite(D1,HIGH);
  digitalWrite(D2,LOW);
  digitalWrite(point,HIGH);
  Display(b2);
  delay(delai);
  
  digitalWrite(point,LOW);
  digitalWrite(D2,HIGH);
  digitalWrite(D3,LOW);
  Display(b3);
  delay(delai);
  
  digitalWrite(D3,HIGH);
  digitalWrite(D4,LOW);
  Display(b4);
  delay(delai);
}
