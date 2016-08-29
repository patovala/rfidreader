#include <SoftwareSerial.h>  // SoftwareSerial must be included because the library depends on it
#include "./RFID.h"
#define Control1         4  //On / Off
#define PushButtonPin    5  // choose the pin for the Pushbutton

#define TIMEUNLOCKDOOR 6000 // Time unlock door 15s

// Creates an RFID instance in Wiegand Mode
// DATA0 of the RFID Reader must be connected 
// to Pin 2 of your Arduino (INT0 on most boards, INT1 on Leonardo)
// DATA1 of the RFID Reader must be connected
// to Pin 3 of your Arduino (INT1 on most boards, INT0 on Leonrado)
RFID rfid(RFID_WIEGAND, W26BIT);

// Declares a struct to hold the data of the RFID tag
// Available fields:
//  * id (3 Bytes) - card code
//  * valid - validity
RFIDTag tag;

void setup() 
{
    Serial.begin(9600);  // Initializes serial port
    pinMode(Control1, OUTPUT);
    digitalWrite(Control1, HIGH);
    pinMode(PushButtonPin, INPUT);    // declare PushButtonPin as output
    digitalWrite(PushButtonPin, LOW);
    while ( !Serial );   
}

void loop()
{
    if( rfid.available()){
        tag = rfid.getTag();  // Retrieves the information of the tag
        Serial.print("CC = ");  // and prints that info on the serial port
        Serial.println(tag.id, HEX);
        Serial.print("The ID is ");
        if (tag.valid) Serial.println("valid");
        else Serial.println("invalid");
    }
    
    if(Serial.available()){
        int thisChar = Serial.read();
        if(thisChar == 'o'){
            Serial.println("Intentando abrir la puerta");
            digitalWrite(Control1, LOW);
            delay(TIMEUNLOCKDOOR);
            digitalWrite(Control1, HIGH);
        }
    }

    int val = digitalRead (PushButtonPin);  // read input value
    if (val == HIGH) {         // check if the input is HIGH (button released)
         Serial.println("Intentando abrir la puerta desde el switch");
         digitalWrite(Control1, LOW);
         delay(TIMEUNLOCKDOOR);
         digitalWrite(Control1, HIGH);
     }
}