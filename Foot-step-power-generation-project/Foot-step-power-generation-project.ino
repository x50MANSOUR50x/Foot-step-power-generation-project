#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define relay1 5
#define relay2 6
#define relay3 7
#define switch1 2
#define red_led 3
#define blue_led 4

LiquidCrystal_I2C lcd(0x27,16,2);

#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_PIN          10         // Configurable, see typical pin layout above
 
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance


byte accessUID_card1[4] = {0xF1, 0x43, 0x6E, 0x1B};
byte accessUID_card2[4] = {0x33, 0x8D, 0x5D, 0x20};

void setup() {
	Serial.begin(9600);
  lcd.init();                      
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Put your card.");
	while (!Serial);
	SPI.begin();
	mfrc522.PCD_Init();
	delay(4);
	mfrc522.PCD_DumpVersionToSerial();
	Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));

  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);
  
  pinMode(red_led, OUTPUT);
  pinMode(blue_led, OUTPUT);

  digitalWrite(red_led, HIGH);

  pinMode(switch1, INPUT);

}

void loop() { 
	if ( ! mfrc522.PICC_IsNewCardPresent()) {
		return;
	}

	if ( ! mfrc522.PICC_ReadCardSerial()) {
		return;
	}

	if(mfrc522.uid.uidByte[0] == accessUID_card1[0] && mfrc522.uid.uidByte[1] == accessUID_card1[1] && mfrc522.uid.uidByte[2] == accessUID_card1[2] && mfrc522.uid.uidByte[3] == accessUID_card1[3] || mfrc522.uid.uidByte[0] == accessUID_card2[0] && mfrc522.uid.uidByte[1] == accessUID_card2[1] && mfrc522.uid.uidByte[2] == accessUID_card2[2] && mfrc522.uid.uidByte[3] == accessUID_card2[3]){
    digitalWrite(relay1, HIGH);
    digitalWrite(relay2, HIGH);
    digitalWrite(relay3, HIGH);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("The machine");
    lcd.setCursor(0,1);
    lcd.print("is in use.");
    while(digitalRead(switch1) != 1){
        digitalWrite(red_led, LOW);
        digitalWrite(blue_led, HIGH);
    }
    digitalWrite(relay1, LOW);
    digitalWrite(relay2, LOW);
    digitalWrite(relay3, LOW);
    digitalWrite(blue_led, LOW);
    digitalWrite(red_led, HIGH);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Thank you.");
    delay(5000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Put your card.");
  }
  else{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("You are not ");
    lcd.setCursor(0,1);
    lcd.print("subsucribed.");
    delay(3000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("please subscribe");
    lcd.setCursor(0,1);
    lcd.print("to continue.");
    delay(3000);
    lcd.clear();
    lcd.print("Put your card.");

  }

  mfrc522.PICC_HaltA();
}
// #include <SPI.h>
// #include <MFRC522.h>
// #include <Wire.h> 
// #include <LiquidCrystal_I2C.h>

// #define relay1 5
// #define relay2 6
// #define relay3 7
// #define switch1 2
// #define red_led 3
// #define blue_led 4

// LiquidCrystal_I2C lcd(0x27,16,2);

// #define RST_PIN         9          // Configurable, see typical pin layout above
// #define SS_PIN          10         // Configurable, see typical pin layout above
 
// MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance


// byte accessUID_card1[4] = {0xF1, 0x43, 0x6E, 0x1B};
// byte accessUID_card2[4] = {0x33, 0x8D, 0x5D, 0x20};

// void setup() {
// 	Serial.begin(9600);
//   lcd.init();                      
//   lcd.backlight();
//   lcd.setCursor(0,0);
//   lcd.print("Put your card.");
// 	while (!Serial);
// 	SPI.begin();
// 	mfrc522.PCD_Init();
// 	delay(4);
// 	mfrc522.PCD_DumpVersionToSerial();
// 	Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));

//   pinMode(relay1, OUTPUT);
//   pinMode(relay2, OUTPUT);
//   pinMode(relay3, OUTPUT);
  
//   digitalWrite(relay1, LOW);
//   digitalWrite(relay2, LOW);
//   digitalWrite(relay3, LOW);
  
//   pinMode(red_led, OUTPUT);
//   pinMode(blue_led, OUTPUT);

//   digitalWrite(red_led, HIGH);

//   pinMode(switch1, INPUT);

// }

// void loop() { 
// 	if ( ! mfrc522.PICC_IsNewCardPresent()) {
// 		return;
// 	}

// 	if ( ! mfrc522.PICC_ReadCardSerial()) {
// 		return;
// 	}

// 	if(mfrc522.uid.uidByte[0] == accessUID_card1[0] && mfrc522.uid.uidByte[1] == accessUID_card1[1] && mfrc522.uid.uidByte[2] == accessUID_card1[2] && mfrc522.uid.uidByte[3] == accessUID_card1[3] || mfrc522.uid.uidByte[0] == accessUID_card2[0] && mfrc522.uid.uidByte[1] == accessUID_card2[1] && mfrc522.uid.uidByte[2] == accessUID_card2[2] && mfrc522.uid.uidByte[3] == accessUID_card2[3]){
//     digitalWrite(relay1, HIGH);
//     digitalWrite(relay2, HIGH);
//     digitalWrite(relay3, HIGH);
//     lcd.clear();
//     lcd.setCursor(0,0);
//     lcd.print("The mahcine now");
//     lcd.setCursor(0,1);
//     lcd.print("is in use.");
//     while(digitalRead(switch1) != 1){
//         digitalWrite(red_led, LOW);
//         digitalWrite(blue_led, HIGH);
//     }
//     digitalWrite(relay1, LOW);
//     digitalWrite(relay2, LOW);
//     digitalWrite(relay3, LOW);
//     digitalWrite(blue_led, LOW);
//     digitalWrite(red_led, HIGH);
//     lcd.clear();
//     lcd.setCursor(0,0);
//     lcd.print("Thank you.");
//     delay(5000);
//     lcd.clear();
//     lcd.setCursor(0,0);
//     lcd.print("Put your card.");
//   }

//   mfrc522.PICC_HaltA();
// }
