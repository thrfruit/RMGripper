// 引脚5
int ledPin = 5;      
 
//
int val = 0; 
int preVal=0;
//int incomeByte=0; 
String comdata = "";
//const char* num;
void setup()
{
 // 将连接LED的引脚设置为输出模式
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
}
 
void loop()
{
  if(Serial.available()>0){
    delay(1);
    comdata =Serial.readString();
    Serial.print("Serial.readStringUntil: ");
    Serial.println(comdata);
    val=comdata.toInt();
   // incomeByte=Serial.read();
    //Serial.print("Received: ");
    //Serial.println(incomeByte,DEC);
 }
 
  
  
 // clear serial buffer
  while(Serial.read() >= 0){}
 // 数值写入引脚5
 if(val!=preVal){
   analogWrite(ledPin, 255/ val);
   Serial.print("val: ");
   Serial.println(val);
   preVal=val;
  }
  
  
}
