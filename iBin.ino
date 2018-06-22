//reset system
#include <SoftReset.h>
//gsm
#include <SoftwareSerial.h>
SoftwareSerial mySerial(3,4);
char incomingByte;
String inputString;
//Ultrasonic variable and pins declaration
int trigPin = 8 ;
int echoPin = 9 ; 
long duration , cm;
//indicators
int full_indicator = 6;
int usable_indicator = 5;

//variables
int i = 0; 

void setup(){     
//HC-SR04 proximity
  pinMode (trigPin, OUTPUT);
  pinMode (echoPin, INPUT);
//indicators
 pinMode (usable_indicator, OUTPUT);
 pinMode (full_indicator, OUTPUT);

  //START SERIAL MONITOR FOR ALL
  Serial.begin(9600);
  //GSM connection serial begin
         mySerial.begin(9600);
      // to check connection to gsm module
      while(!mySerial.available()){
        mySerial.println("AT");
        delay(1000);
        Serial.println("E-GUARD SYSTEM is connecting to network, please wait...");
        }
      Serial.println("Connected!");
      mySerial.println("AT+CMGF=1");  //Set SMS Text Mode mode
      delay(1000);
      mySerial.println("AT+CNMI=1,2,0,0,0");  //procedure, how receiving of new messages from the network
      delay(1000);
      mySerial.println("AT+CMGL=\"REC UNREAD\""); //soma texts
      mySerial.println("AT+CMGD=1,4");
          Serial.println("System Ready");
 //GSM connection serial end here
 Serial.print("\t\t\t\t\t\t\t    \"iBin\" Intelligent bin SYSTEM");
}
 void loop()
  {
  Serial.print(cm);
  Serial.print("\t\t\t");
  Serial.println(" ");
//READ DATA FOR THE ULTRASONIC
digitalWrite ( trigPin, LOW );
delayMicroseconds ( 5 );
digitalWrite ( trigPin, HIGH );
delayMicroseconds ( 10 );
digitalWrite ( trigPin, LOW );
  pinMode ( echoPin, INPUT );
duration = pulseIn( echoPin, HIGH );
// convert the time into a distance
  cm = ( duration / 2 ) / 29.1 ;
  
//Actuator 1 (SMS)
  if ((cm < 5) && (cm > 1))
{
send_sms();
digitalWrite(full_indicator, HIGH);
digitalWrite(usable_indicator, LOW);
 }
  else{
digitalWrite(full_indicator, LOW);
digitalWrite(usable_indicator, HIGH);
  }
  
 delay(3000); //delay 1 second (s) before checking again
  
//Receive text messages
  if(mySerial.available()){
      delay(100);
      // Serial buffer
      while(mySerial.available()){
        incomingByte = mySerial.read();
        inputString += incomingByte;
        }
        delay(10);
        inputString.toUpperCase(); // uppercase the message received
        
         if (inputString.indexOf("HALLO") > -1)
         { 
//////////////////////////////////////////////////////////////////////////
 if ((cm < 5) && (cm > 1))
{
reply2();
delay(500);
soft_restart();
 }
  else{
reply1();
delay(500);
soft_restart();
  }
//////////////////////////////////////////////////////////////////////////    
         }
         
         
         if (inputString.indexOf("RESET") > -1)
         {
          soft_restart();
         }
  }
 //Function definitions
  } 
  void send_sms()
{
  mySerial.println("AT+CMGF=1");    
  delay(1000);
  mySerial.println("AT+CMGS=\"+254706434259\"\r");
  delay(1000);
  mySerial.println("Hi, iBin here. I'm Full of trash and unusable at the moment. Kindly empty me.");
  mySerial.println("Thank you");
  mySerial.println(" ");
  mySerial.print("From: iBin");
  delay(100);
  mySerial.println((char)26);
  delay(1000);
}

void reply1()
{
  mySerial.println("AT+CMGF=1");
  delay(1000); 
  mySerial.println("AT+CMGS=\"+254706434259\"\r"); 
  delay(1000);
   mySerial.println("Hallo");
     mySerial.print("System: : ");
  mySerial.println("Working"); 
   mySerial.print("Status: ");
  mySerial.println("iBin usable");
  mySerial.println("");
  mySerial.print("From: iBin");
  delay(100);
  mySerial.println((char)26);// ASCII code of CTRL+Z
  
  delay(1000);
}

void reply2()
{
  mySerial.println("AT+CMGF=1");
  delay(1000); 
  mySerial.println("AT+CMGS=\"+254706434259\"\r"); 
  delay(1000);
   mySerial.println("Hallo");
     mySerial.print("System: : ");
  mySerial.println("Working"); 
   mySerial.print("Status: ");
  mySerial.println("iBin full");
  mySerial.println("");
  mySerial.print("From: iBin");
  delay(100);
  mySerial.println((char)26);// ASCII code of CTRL+Z
  
  delay(1000);
}
