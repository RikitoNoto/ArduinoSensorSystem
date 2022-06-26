#ifndef _DHT_11_H_
#define _DHT_11_H_

#include <DataType.h>
#include "DhtBase.h"

class Dht11 : public DhtBase
{
public:
    Dht11(pinno_t datapin_no);
    virtual ~Dht11();
    virtual RESULT start(void);
    virtual READ_STATUS execute(WORD* option=nullptr, WORD option_count=0);
};

#endif // _DHT_11_H_