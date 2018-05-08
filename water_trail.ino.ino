//Open Serial Port and Send HEX Data
#include <SoftwareSerial.h>
SoftwareSerial loraSerial (2, 3); //rx 2 tx 3
byte sensorPin[] = {8, 9, 10};

byte ledPin[] = {11, 12, 13}; 

int motor_supply = 0;

const byte sensors = 3;

int level = 0;
int nodeId = 4;
void setup() {
  loraSerial.begin(57600);
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  RN2483_init();


for(int j = 0; j < sensors; j++)

{

pinMode(sensorPin[j], INPUT);

pinMode(ledPin[j], OUTPUT);

}


  
}

void loop() {

  int motor_supply = digitalRead(5);
  String is = String(motor_supply);
  is = "radio tx " + is;
  sendmsg(is);
  delay(2000);
  
  level = 0;


  
  loraSerial.listen();
  while(loraSerial.available() > 0){
    char loraResponse = loraSerial.read();
    Serial.write(loraResponse);
    
  }

}

void RN2483_init(){
  sendcmd("sys reset");
  sendcmd("radio set mod lora");
  sendcmd("radio set freq 868100000");
  sendcmd("radio set pwr 14");
  sendcmd("radio set sf sf12");
  sendcmd("radio set afcbw 125");
  sendcmd("radio set rxbw 250");
  sendcmd("radio set fdev 5000");
  sendcmd("radio set prlen 8");
  sendcmd("radio set crc on");
  sendcmd("radio set cr 4/8");
  sendcmd("radio set wdt 0");
  sendcmd("radio set sync 12");
  sendcmd("radio set bw 250");
  sendcmd("sys get hweui");
  sendcmd("mac pause");
}

void sendcmd(String data){
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println(data);
  loraSerial.println(data); 
  digitalWrite(LED_BUILTIN, LOW);
}

void sendmsg(String data){
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println(data);
  loraSerial.println(data);
  digitalWrite(LED_BUILTIN, LOW);

    for(int j = 0; j < sensors; j++)

{

if(digitalRead(sensorPin[j]) == LOW)

{

digitalWrite(ledPin[j], HIGH);

level = sensors - j;

}

else

{

digitalWrite(ledPin[j], LOW);

}

}

Serial.println("Water level");

switch(level)

{

case 1:

Serial.println("HIGH");
motor_supply = 0;

break;

case 2:

Serial.println("AVERAGE");

break;

case 3:

Serial.println("LOW");
motor_supply = 1;
break;

default:

Serial.println("WATER LEVEL LOW");

break;

}

delay(50);
}

String strtohex(String data){
  String sh;
  char ch;
  for (int i=0;i<data.length();i++){
    ch = data.charAt(i);
    sh += String(ch,HEX);
  }
  return sh;
}
