#include "MemoryUtility.h"

BOOL MemoryUtility::memclear(void* ptr, DWORD size)
{
    BOOL result = FALSE;
    BYTE* byte_ptr = (BYTE*)ptr;
    for(DWORD i = 0; i < size; i++)
    {
        byte_ptr[i] = 0;
    }

    return result;
}