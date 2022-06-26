#include "Dht11.h"
#include "RobotLCD.h"
#include "Point.h"
//#include <string>

#define cs   10
#define dc   9
#define rst  8

RobotLCD lcd = RobotLCD(cs, dc, rst);
Dht11* dht = nullptr;
Point<DWORD> *point = new Point<DWORD>(10,10);

void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);

    lcd.begin();
    lcd.setBackgroundColor(Color::COLOR::BLACK);
    dht = new Dht11(7);
}

void loop() {
    // put your main code here, to run repeatedly:

    if(dht->start()){
        dht->execute();

        Serial.print(static_cast<float>(dht->getData())/1000);
        Serial.println("℃");
        char temperature[8] = {'\0'};
        itoa( (dht->getData()/1000), temperature, 10);

        for(int i=0; i<8; i++){
          if(temperature[i] == '\0'){
            temperature[i] = 'C';
            break;
          }
        }
        
        
        lcd.display(temperature, point, Display_if::TEXT_SIZE_SMALL);
    }
}
