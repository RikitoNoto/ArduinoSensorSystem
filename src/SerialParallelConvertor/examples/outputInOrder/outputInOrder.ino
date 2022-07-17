#include <S2P_74HC595.h>

S2P_74HC595 s2p(/*SER*/ 4, /*SRCLK*/ 3, /*SRCLR*/ 5, /*RCLK*/ 6);
BOOL is_fin = FALSE;

void setup(){
    s2p.clearOutput();
    s2p.clear();
    s2p.setSendData(0xFE);
}

void loop(){
    if( (!is_fin) &&
        (s2p.send() == S2P_74HC595::SEND_STATUS::COMPLETE)){
        is_fin = TRUE;
        Serial.println("fin");
    }
}
