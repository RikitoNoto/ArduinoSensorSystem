#ifndef _DATA_TYPE_H_
#define _DATA_TYPE_H_

typedef unsigned char BYTE;         // 1byte
typedef unsigned short WORD;        // 2byte
typedef unsigned long DWORD;        // 4byte
typedef unsigned long long QWORD;   // 8byte

typedef enum{ FALSE = 0, TRUE = 1 } BOOL;
typedef enum{ FAIL = FALSE, SUCCESS = TRUE } RESULT;

typedef DWORD MEMORY_SIZE_T; // memory size
typedef MEMORY_SIZE_T SIZE_T; // utilty size

#endif // _DATA_TYPE_H_