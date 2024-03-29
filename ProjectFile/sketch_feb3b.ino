#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <deprecated.h>
#include <require_cpp11.h>
#include "driver/ledc.h"


#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         22         // Configurable, see typical pin layout above
#define SS_PIN          5         // Configurable, see typical pin layout above

#define pirPin 21               // CHANGE PIN NUMBER HERE IF YOU WANT TO USE A DIFFERENT PIN
#define ledPin 4 
#define led2Pin 2 

//pir sensor
long duration, distance;

//sound
// int led = 13;
// int sound_digital = 12;
// int sound_analog = 35;

//buzzer
// const int buzzerPin=2;

//light sensor
int lightPin=13;





MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

void setup() {
	Serial.begin(9600);		// Initialize serial communications with the PC
	while (!Serial);		// Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)

  //pir sensor
  pinMode(pirPin, INPUT);
  
  //led light
  pinMode(ledPin, OUTPUT);
  pinMode(led2Pin,OUTPUT);

  //sound sensor
  // pinMode(led, OUTPUT);
  // pinMode(sound_digital, INPUT);

  //buzzer
  // pinMode(buzzerPin,OUTPUT);

  //light sensor
  pinMode(lightPin,INPUT);
  


	SPI.begin();			// Init SPI bus
	mfrc522.PCD_Init();		// Init MFRC522
	delay(4);				// Optional delay. Some board do need more time after init to be ready, see Readme
	mfrc522.PCD_DumpVersionToSerial();	// Show details of PCD - MFRC522 Card Reader details
	Serial.println("Hold your Student ID Card near to the Scanner..");
  Serial.println();
}

void loop() {

  //pir sensor
  bool motion=digitalRead(pirPin);
  if(motion){
    Serial.println("\nMotion Detected: " + String(motion));
    digitalWrite(ledPin,HIGH);
    delay(1000);
  }else{
    Serial.println("\nMotion Not Detected: "+ String(motion));
    digitalWrite(ledPin,LOW);
    delay(1000);
  }

  //sound sensor

  // int val_digital = digitalRead(sound_digital);
  // int val_analog = analogRead(sound_analog);

  // Serial.print("Analog Signal: "+String(val_analog));
  // Serial.print("\t");
  // Serial.println("Digital Signal "+String(val_digital));

  // if (val_digital == LOW)
  // {
  //   digitalWrite (led, LOW);
  //   delay(1000);
  //   }
  // else
  // {
  //   digitalWrite (led, HIGH);
  //   delay(1000);
  // }

  //light sensor
  bool light=digitalRead(lightPin);
  if (light)
  {
    Serial.println("Light is Deactivated.");
    }
  else
  {
    Serial.println("Light is Activated.");
  }

  digitalWrite(led2Pin, !light);


  delay(3000);
  
  


	// Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
	if ( ! mfrc522.PICC_IsNewCardPresent()) {
		return;
	}

	// Select one of the cards
	if ( ! mfrc522.PICC_ReadCardSerial()) {
		return;
	}

	// Dump debug info about the card; PICC_HaltA() is automatically called
	mfrc522.PICC_DumpToSerial(&(mfrc522.uid));

  Serial.print("Card ID: ");
  String cardID = ""; //store the card's ID
  for (byte i = 0; i< mfrc522.uid.size; i++){
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    cardID.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    cardID.concat(String(mfrc522.uid.uidByte[i], HEX));

  }
  Serial.println();
  cardID.toUpperCase();
  if(cardID.substring(1) == "E3 50 E3 19"  )
  {
      Serial.println("Access Granted");
      Serial.println();
      digitalWrite(ledPin,HIGH);
      
  }
  else {
      Serial.println("Access Denied");
      digitalWrite(ledPin,LOW);
      
  }
  delay(3000);

}