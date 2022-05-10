#ifndef _DHT_11_H_
#define _DHT_11_H_

#include <DataType.h>

class Dht11
{
public:
    Dht11(BYTE datapin_no);
    void start();
private:
};

#endif // _DHT_11_H_