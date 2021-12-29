#include <Arduino.h>
#include <Wire.h>
#include <Servo.h>
#include <SoftwareSerial.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
 

}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()>0){
    char inChar = Serial.read();
    if (inChar=='0'){
        //EN
        pinMode(7, OUTPUT);
        digitalWrite(7,1);
        //IN1
        pinMode(8, OUTPUT);
        digitalWrite(8,1);
        //IN2
        pinMode(9, OUTPUT);
        digitalWrite(9,1);
        Serial.print("ZERO\n");
        
        //EN
        pinMode(10, OUTPUT);
        digitalWrite(7,1);
        //IN1
        pinMode(11, OUTPUT);
        digitalWrite(11,1);
        //IN2
        pinMode(12, OUTPUT);
        digitalWrite(12,1);
        Serial.print("ZERO\n");      
          
      }
    //U12=12v 电磁铁弹出
    if (inChar=='1'){
        pinMode(7, OUTPUT);
        digitalWrite(7,1);
        pinMode(8, OUTPUT);
        digitalWrite(8,1);
        pinMode(9, OUTPUT);
        digitalWrite(9,0);
        Serial.print("ONE\n"); 
        //delay(500); 
        
        pinMode(10, OUTPUT);
        digitalWrite(10,1);
        pinMode(11, OUTPUT);
        digitalWrite(11,1);
        pinMode(12, OUTPUT);
        digitalWrite(12,0);
        Serial.print("one\n"); 
        delay(500); 
        digitalWrite(9,1);
        Serial.print("zero\n"); 
        digitalWrite(12,1);
        Serial.print("ONE\n"); 
      }
    //U12=-12V 电磁铁吸入
    if (inChar=='2'){
        pinMode(7, OUTPUT);
        digitalWrite(7,1);
        pinMode(8, OUTPUT);
        digitalWrite(8,0);
        pinMode(9, OUTPUT);
        digitalWrite(9,1);
        Serial.print("TWO\n");  
        //delay(500); 
        
        pinMode(10, OUTPUT);
        digitalWrite(10,1);
        pinMode(11, OUTPUT);
        digitalWrite(11,0);
        pinMode(12, OUTPUT);
        digitalWrite(12,1);
        Serial.print("two\n");  
        delay(500); 
        digitalWrite(8,1);
        Serial.print("zero\n");
        digitalWrite(11,1);
        Serial.print("TWO\n");
      }
      /*
      //MAGNET2
     if (inChar=='3'){
        //EN
        pinMode(10, OUTPUT);
        digitalWrite(7,1);
        //IN1
        pinMode(11, OUTPUT);
        digitalWrite(11,1);
        //IN2
        pinMode(12, OUTPUT);
        digitalWrite(12,1);
        Serial.print("zero\n");  
      }
    //U12=12v 电磁铁弹出
    if (inChar=='4'){
        pinMode(10, OUTPUT);
        digitalWrite(7,1);
        pinMode(11, OUTPUT);
        digitalWrite(11,1);
        pinMode(12, OUTPUT);
        digitalWrite(12,0);
        Serial.print("one\n"); 
        delay(500); 
        digitalWrite(12,1);
        Serial.print("zero\n"); 
      }
    //U12=-12V 电磁铁吸入
    if (inChar=='5'){
        pinMode(10, OUTPUT);
        digitalWrite(10,1);
        pinMode(11, OUTPUT);
        digitalWrite(11,0);
        pinMode(12, OUTPUT);
        digitalWrite(12,1);
        Serial.print("two\n");  
        delay(500); 
        digitalWrite(11,1);
        Serial.print("zero\n");
      } 
      */  
  }
}
