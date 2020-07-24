#ifndef __ARRFUNCS_H__
#define __ARRFUNCS_H__
#include "stdint.h"
#include  "math.h" 
void printArr(int32_t* arr, int32_t size);
/*print double array elements */
void printFloatArr(double* arr, int32_t size);

/* delete element from int array */
void  delIntElement(double* nums, int8_t index, int size);
/* delete element from double array */
void  delDoubleElement(double* fnums, int8_t index, int size) ;
#endif
