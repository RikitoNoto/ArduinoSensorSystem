#ifndef Arduino_h
#define Arduino_h

#include <stdint.h>

#define HIGH 0x1
#define LOW  0x0

#define INPUT 0x0
#define OUTPUT 0x1
#define INPUT_PULLUP 0x2

void pinMode(uint8_t pin, uint8_t mode);
void digitalWrite(uint8_t pin, uint8_t val);
int digitalRead(uint8_t pin);



#define PIN_MODE_INDEX_COUNT    (32)
#define PIN_INFO_NONE           (0xFF)
#define PIN_WRITE_DO_NOT_CALL   (0xFF)
void setupSpyArduino(void);
bool checkPinCalled(uint8_t pin, uint8_t mode = PIN_INFO_NONE);
bool checkPinDigitalWrite(uint8_t pin, uint8_t val = PIN_WRITE_DO_NOT_CALL);

void setReadValue(uint8_t pin, int value);


#endif
