#include "Scheduler.h"
bool state=HIGH;

class Schedule : public Schedule_if
{
public:
    void execute(void)
    {
      if(state){
        state = LOW;
      }
      else{
        state = HIGH;
      }
      digitalWrite(13, state);
    }

    DWORD getTime(void)
    {
      return 1000;  // call the execute method each 1000ms.
    }

    SchduleType getScheduleType(void)
    {
      return SchduleType::INTERVAL;
    }
};
void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  Scheduler::getInstance()->start(Scheduler::getInstance()->setSchedule(new Schedule()));
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
