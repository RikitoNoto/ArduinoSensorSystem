#ifndef _DHT_H_
#define _DHT_H_

#include "Arduino.h"

static const uint8_t DHT11{11};  /**< DHT TYPE 11 */
static const uint8_t DHT12{12};  /**< DHY TYPE 12 */
static const uint8_t DHT21{21};  /**< DHT TYPE 21 */
static const uint8_t DHT22{22};  /**< DHT TYPE 22 */
static const uint8_t AM2301{21}; /**< AM2301 */

class DHT {
public:
    DHT(uint8_t pin, uint8_t type, uint8_t count = 6);
    void begin(uint8_t usec = 55);
    float readTemperature(bool S = false, bool force = false);
    float convertCtoF(float);
    float convertFtoC(float);
    float computeHeatIndex(bool isFahrenheit = true);
    float computeHeatIndex(float temperature, float percentHumidity,
                            bool isFahrenheit = true);
    float readHumidity(bool force = false);
    bool read(bool force = false);

#ifndef TEST_SOURCE
private:
#endif // TEST_SOURCE

    uint8_t m_pin;
    uint8_t m_type;
    bool is_called_begin;

    float temperature;


};

#endif // _DHT_H_