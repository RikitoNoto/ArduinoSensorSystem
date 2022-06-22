#include "Dht11.h"

Dht11* dht = nullptr;
BOOL is_start = FALSE;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  dht = new Dht11(10);
}

void loop() {
  // put your main code here, to run repeatedly:

  if(!is_start)
  {
      if(dht->start())
      {
        is_start = TRUE;
      }
  }
  
  if(is_start)
  {
    switch(dht->execute())
    {
      case Dht11::READ_STATUS::READ_SUCCESS:
        Serial.println(dht->getData());
        Serial.println("success");
        is_start = FALSE;
        break;
      case Dht11::READ_STATUS::READ_FAILURE:
        Serial.println("failure");
        is_start = FALSE;
        break;      
    }
  }
  
}
