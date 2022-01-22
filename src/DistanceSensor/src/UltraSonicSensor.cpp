#include "UltraSonicSensor.h"
#include <Arduino.h>

UltraSonicSensor::UltraSonicSensor()
{
}

UltraSonicSensor::UltraSonicSensor(BYTE trig_pin_no, BYTE echo_pin_no)
{
    this->m_trig_pin_no = trig_pin_no;
    pinMode(this->m_trig_pin_no, OUTPUT);
    pinMode(echo_pin_no, INPUT);
}

/**
 * @brief read sensor value.
 * @param[out] read_distance read distance.
 * @return read status.
 * @retval READING reading value.
 * @retval COMPLETE done read.
 */
UltraSonicSensor::READ_STATUS UltraSonicSensor::read(DISTANCE_MM_T* read_distance)
{
    digitalWrite(this->m_trig_pin_no, HIGH);
}

void UltraSonicSensor::stateIdle(void)
{

}

void UltraSonicSensor::stateOutputTrigger(void)
{

}