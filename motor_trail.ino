#include <SoftwareSerial.h>
 
SoftwareSerial loraSerial (2, 3); //rx 2 tx 3
bool flag = true;
int val = 0;
int level_state = 5;
void setup() {
  Serial.begin(9600);
  loraSerial.begin(57600);
  pinMode(LED_BUILTIN, OUTPUT);
  RN2483_init();
   //pinMode(motor_supply,INPUT);
  pinMode(level_state,OUTPUT);
  

}

void loop() {
  if(flag){
    loraSerial.println("radio rx 0");
  }
  flag = false;
  loraSerial.listen();
  while (loraSerial.available() > 0) {
    String loraResponse = loraSerial.readString();
    Serial.println(loraResponse);
  


   val = Serial.read();         // read it and store it in 'val'
 
  if( val == '0' )               // if '0' was received motor is switched off

  {
   digitalWrite(level_state, LOW);    // turn Off motor off
delay(1000);                  // waits for a second   
Serial.println("motor off");
  }

if( val == '1' )               // if '1' was received motor on
 {
    digitalWrite(level_state, HIGH);  // turn ON motor on
    delay(1000);                  // waits for a second
    Serial.println("motor on");
  }
   
flag = true;
 }
 delay(1000); 
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

void sendcmd(String data) {
  Serial.println(data);
  loraSerial.println(data);
  
}

