#ifndef _MEMORY_UTILITY_H_
#define _MEMORY_UTILITY_H_
#include <DataType.h>

class MemoryUtility
{
public:
    static RESULT memClear(void* ptr, MEMORY_SIZE_T size);
    static RESULT memCopy(void* dst, void* src, MEMORY_SIZE_T size);

};

#endif // _MEMORY_UTILITY_H_