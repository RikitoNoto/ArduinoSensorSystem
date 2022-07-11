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
unsigned long micros();

typedef long unsigned int size_t;
#define DEC 10

class Serial_
{
public:
    void begin(unsigned long){};

    size_t print(const char[]){return 0;};
    size_t print(char){return 0;};
    size_t print(unsigned char, int = DEC){return 0;};
    size_t print(int, int = DEC){return 0;};
    size_t print(unsigned int, int = DEC){return 0;};
    size_t print(long, int = DEC){return 0;};
    size_t print(unsigned long, int = DEC){return 0;};
    size_t print(double, int = 2){return 0;};

    size_t println(const char[]){return 0;};
    size_t println(char){return 0;};
    size_t println(unsigned char, int = DEC){return 0;};
    size_t println(int, int = DEC){return 0;};
    size_t println(unsigned int, int = DEC){return 0;};
    size_t println(long, int = DEC){return 0;};
    size_t println(unsigned long, int = DEC){return 0;};
    size_t println(double, int = 2){return 0;};
    size_t println(void){return 0;};
};

extern Serial_ Serial;


#define PIN_INFO_NONE           (0xFF)
#define PIN_WRITE_DO_NOT_CALL   (0xFF)

enum ARDUINO_TYPE
{
    UNO,
};

void setupSpyArduino(ARDUINO_TYPE type=UNO);
void tearDownArduino(void);
bool isPinMode(uint8_t pin, uint8_t mode);
bool isPinOutput(uint8_t pin, uint8_t val);

// bool isPinCalled(uint8_t pin, uint8_t mode = PIN_INFO_NONE);
// bool isPinDigitalWrite(uint8_t pin, uint8_t val = PIN_WRITE_DO_NOT_CALL);

void clearWriteInfo(void);
bool isWriteHigh(uint8_t pin);
bool isWriteLow(uint8_t pin);

void setReadValue(uint8_t pin, int value);




#endif
