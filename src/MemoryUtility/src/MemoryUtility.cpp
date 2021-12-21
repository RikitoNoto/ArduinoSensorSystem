#include "MemoryUtility.h"

/**
* @brief clear memory.
* @param[in] ptr pointer to clear.
* @param[in] size size of to clear.
* @return result of clear.
* @retval SUCCESS successful.
* @retval FAIL fail.
*/
RESULT MemoryUtility::memClear(void* ptr, MEMORY_SIZE_T size)
{
    RESULT result = SUCCESS;
    BYTE* byte_ptr = (BYTE*)ptr;
    for(DWORD i = 0; i < size; i++)
    {
        byte_ptr[i] = 0;
    }

    return result;
}

/**
* @brief clear memory.
* @param[in] ptr pointer to clear.
* @param[in] size size of to clear.
* @return result of clear.
* @retval SUCCESS successful.
* @retval FAIL fail.
*/
RESULT MemoryUtility::memCopy(void* _dst, void* _src, MEMORY_SIZE_T size)
{
    RESULT result = SUCCESS;
    BYTE* dst = static_cast<BYTE*>(_dst);
    BYTE* src = static_cast<BYTE*>(_src);

    for(MEMORY_SIZE_T i = 0; i < size ; i++)
    {
        *dst++ = *src++;
    }

    return result;
}