#include "array.h"
#include"stdio.h"

/* delete element from int array */
void  delIntElement(double* nums, int8_t index, int size) {
    uint8_t count;//is used as a counter
    for (count = index; count < size; count++) //start from the index of the required position
    {                                           //to delete, loop size-1 number of time
        nums[count] = nums[count + 1]; //shift elements
    }
}
/* delete element from double array */
void  delDoubleElement(double* fnums, int8_t index, int size) {
    uint8_t count;
    for (count = index; count < size; count++) //start from the index of the required position
                                              //to delete, loop size-1 number of time
    {
        fnums[count] = fnums[count + 1];//shift elements
    }
}
