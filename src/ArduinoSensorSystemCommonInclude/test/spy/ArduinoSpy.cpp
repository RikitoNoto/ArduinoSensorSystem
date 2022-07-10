#include <Arduino.h>

Serial_ Serial;


// pinMode
static uint8_t pin_mode_called_pin[PIN_MODE_INDEX_COUNT];
static uint8_t pin_mode_called_mode[PIN_MODE_INDEX_COUNT];

// digitalWrite
static uint8_t pin_write_called_pin[PIN_MODE_INDEX_COUNT];
static uint8_t pin_write_called_value[PIN_MODE_INDEX_COUNT];

// digitalRead
static int pin_read_values[PIN_MODE_INDEX_COUNT];

static bool is_write_high[PIN_MODE_INDEX_COUNT+1];
static bool is_write_low[PIN_MODE_INDEX_COUNT+1];

unsigned long micros()
{
    return 0;
}

void pinMode(uint8_t pin, uint8_t mode)
{
    for(int i=0; i<PIN_MODE_INDEX_COUNT; i++)
    {
        // if called this pin or last of array.
        if( (pin_mode_called_pin[i] == pin) ||
            (pin_mode_called_pin[i] == PIN_INFO_NONE) )
        {
            pin_mode_called_pin[i]  = pin;
            pin_mode_called_mode[i] = mode;

            // if the mode is pull up, set the value of read to high.
            // if(mode == INPUT_PULLUP)
            // {
            //     pin_read_values[pin] = HIGH;
            // }
            break;
        }
    }
}

void digitalWrite(uint8_t pin, uint8_t val)
{
    for(int i=0; i<PIN_MODE_INDEX_COUNT; i++)
    {
        // if called this pin or last of array.
        if( (pin_write_called_pin[i] == pin) ||
            (pin_write_called_pin[i] == PIN_WRITE_DO_NOT_CALL) )
        {
            pin_write_called_pin[i]  = pin;
            pin_write_called_value[i] = val;

            if(val == HIGH)
            {
                is_write_high[pin] = true;
            }
            else if(val == LOW)
            {
                is_write_low[pin] = true;
            }
            break;
        }
    }
}

int digitalRead(uint8_t pin)
{
    return pin_read_values[pin];
}

/**
 * @brief check called the function of pinMode with expected args.
 * @details if mode is PIN_INFO_NONE, do not check mode.
 */
bool isPinCalled(uint8_t pin, uint8_t mode)
{
    // check all pins(pin_mode_called_pin, pin_mode_called_mode)
    for(int i=0; i<PIN_MODE_INDEX_COUNT; i++)
    {
        // if pin called.
        if(pin_mode_called_pin[i] == pin)
        {
            // if set mode.
            if(mode != PIN_INFO_NONE)
            {
                // if mode is same.
                if(pin_mode_called_mode[i] == mode)
                {
                    return true;
                }
                // else is false.
            }
            // mode no set.
            else
            {
                // if pin is same, return true.
                return true;
            }
        }
    }

    return false;
}

/**
 * @brief check called the function of digitalWrite with expected args.
 * @details if val is PIN_WRITE_DO_NOT_CALL, do not check val.
 */
bool isPinDigitalWrite(uint8_t pin, uint8_t val)
{
    // check all pins(pin_write_called_pin, pin_write_called_value)
    for(int i=0; i<PIN_MODE_INDEX_COUNT; i++)
    {
        // if pin called.
        if(pin_write_called_pin[i] == pin)
        {
            // if set mode.
            if(val != PIN_WRITE_DO_NOT_CALL)
            {
                // if mode is same.
                if(pin_write_called_value[i] == val)
                {
                    return true;
                }
                // else is false.
            }
            // mode no set.
            else
            {
                // if pin is same, return true.
                return true;
            }
        }
    }

    return false;
}

void clearWriteInfo(void)
{
    for(int i=0; i<PIN_MODE_INDEX_COUNT; i++)
    {
        is_write_high[i] = false;
        is_write_low[i] = false;
    }
}

bool isWriteHigh(uint8_t pin)
{
    return is_write_high[pin];
}

bool isWriteLow(uint8_t pin)
{
    return is_write_low[pin];
}

void setReadValue(uint8_t pin, int value)
{
    pin_read_values[pin] = value;
}

void setupSpyArduino(void)
{
    for(int i=0; i<PIN_MODE_INDEX_COUNT; i++)
    {
        // reset all the infos of pin mode.
        pin_mode_called_pin[i] = PIN_INFO_NONE;
        pin_mode_called_mode[i] = PIN_INFO_NONE;

        // reset all the pin value of pin output.
        pin_write_called_pin[i] = PIN_WRITE_DO_NOT_CALL;
        pin_write_called_value[i] = PIN_WRITE_DO_NOT_CALL;

        // reset all the pin value of pin input.
        pin_read_values[i] = LOW;

        // reset write info.
        is_write_high[i+1] = false;
        is_write_low[i+1] = false;
    }
}