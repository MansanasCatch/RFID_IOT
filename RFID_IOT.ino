 // TECHATRONIC.COM  
 // SPI Library  
 // https://github.com/PaulStoffregen/SPI  
 // MFRC522 Library  
 // https://github.com/miguelbalboa/rfid  
 #include <SPI.h>  
 #include <MFRC522.h>  
 #include <Servo.h>  
 #include <Wire.h>   
 #include <LiquidCrystal_I2C.h>  
 LiquidCrystal_I2C lcd(0x27,16,2);  
 Servo s1;  
 #define SS_PIN 10  
 #define RST_PIN 9  
 #define LED_G 5  //define green LED pin  
 #define LED_R 7  //define red LED  
 #define BUZZER 6 //buzzer pin  
 MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance.  
 //Servo myServo; //define servo name  
 void setup()   
 {  
  Serial.begin(9600);  // Initiate aa serial communication  
  SPI.begin();     // Initiate SPI bus  
  lcd.init();             
  lcd.backlight();  
 ;  
  mfrc522.PCD_Init();  // Initiate MFRC522  
  s1.attach(3); //servo pin  
  // myServo.write(0); //servo start position  
  pinMode(LED_G, OUTPUT);  
  pinMode(LED_R, OUTPUT);  
  pinMode(BUZZER, OUTPUT);  
  noTone(BUZZER);  
  Serial.println("Put your card to the reader...");  
  Serial.println(); 
  lcd.clear();
  lcd.setCursor(0,0);  
  lcd.print("Tap your card");  
 }  
 void loop()   
 {  
  // Look for new cards  
  if ( ! mfrc522.PICC_IsNewCardPresent())   
  {  
   return;  
  }  
  // Select one of the cards  
  if ( ! mfrc522.PICC_ReadCardSerial())   
  {  
   return;  
  }  
  //Show UID on serial monitor  
  Serial.print("UID tag :");  
  String content= "";  
  byte letter;  
  for (byte i = 0; i < mfrc522.uid.size; i++)   
  {  
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");  
    Serial.print(mfrc522.uid.uidByte[i], HEX);  
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));  
    content.concat(String(mfrc522.uid.uidByte[i], HEX));  
  }  
  Serial.println();  
  Serial.print("Message : ");  
  content.toUpperCase();  
  if (content.substring(1) == "78 F6 A2 89") //change here the UID of the card/cards that you want to give access  
  {  
   Serial.println("Authorized access");  
   Serial.println();    
     tone(BUZZER, 100); 
     delay(500);  
     noTone(BUZZER); 
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("Access Granted");  
     lcd.setCursor(0,1); 
     lcd.print("Opening the Door");  
     digitalWrite(LED_G, HIGH); //Green LED ON  
     s1.write(0);  
     delay(2000);  
     s1.write(90);  
     lcd.setCursor(0,1);  
     lcd.print("Closing the Door");  
     digitalWrite(LED_G, LOW);  //Green LED OFF  
     delay(2000);
     lcd.clear();  
     lcd.setCursor(0,0);  
     lcd.print("Put your card");  
     lcd.setCursor(0,1); 
     lcd.print("");  
  }  
  else   
  {  
   Serial.println("CARD IS INVALID");  
    lcd.clear();
    lcd.setCursor(0,0);  
    lcd.print("CARD IS INVALID");  
    digitalWrite(LED_R, HIGH);   // Red LED ON  
    tone(BUZZER, 300);       // Buzzer ON  
    delay(1000);  
    digitalWrite(LED_R, LOW);  
    noTone(BUZZER);  
     lcd.clear();  
     lcd.setCursor(0,0);  
     lcd.print("Put your card");  
     lcd.setCursor(0,1); 
     lcd.print("");  
  }  
 }  