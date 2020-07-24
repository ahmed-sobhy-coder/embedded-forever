#include "math.h"
uint32_t getPower(uint8_t num,uint8_t power){
  uint32_t mul=1;
  while(power){
    mul*=num;
    power--;
  }
  return mul;
}
double  absolute(double value){
	if(value<0) value = - value ;
	return value;
}
float FLOAT_Approximate(float fnum) {
	float disision_point = 0.5;
	float ftemp;
	ftemp = fnum - (int)fnum;
	if (ftemp >= disision_point) {
		fnum = ((int)fnum) + 1;
	}
	else {
		fnum = (int)fnum;
	}
	return fnum;
}
