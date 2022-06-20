#include "Dht11.h"

Dht11* dht = nullptr;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  dht = new Dht11(10);
  dht->start();
}

void loop() {
  // put your main code here, to run repeatedly:
  if(dht->execute() == Dht11::READ_STATUS::READ_SUCCESS)
  {
    Serial.println(dht->getData());
    dht->start();
  }
  else if(dht->execute() == Dht11::READ_STATUS::READ_FAILURE)
  {
    Serial.println("failure");
    dht->start();
  }
}
