#include "Dht11.h"

Dht11* dht = nullptr;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  dht = new Dht11(10);
}

void loop() {
  // put your main code here, to run repeatedly:

  if(dht->start()){
    dht->execute();
  
    Serial.print(static_cast<float>(dht->getData())/1000);
    Serial.println("℃");
  }
}
