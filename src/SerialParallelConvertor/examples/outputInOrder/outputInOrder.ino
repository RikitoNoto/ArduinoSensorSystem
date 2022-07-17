#include <S2P_74HC595.h>

S2P_74HC595 s2p(/*SER*/ 4, /*SRCLK*/ 3, /*SRCLR*/ 5);
BOOL is_fin = FALSE;
int count = 0;

void setup(){
    s2p.clearOutput();
    s2p.clear();
    s2p.setSendData(0xFE);
}

void loop(){
    if( (!is_fin) &&
        (s2p.send() == S2P_74HC595::SEND_STATUS::COMPLETE)){
//        digitalWrite(3, LOW);
        digitalWrite(6, HIGH);
//        digitalWrite(3, HIGH);
        digitalWrite(6, LOW);
        is_fin = TRUE;
        Serial.println("fin");
    }
}
