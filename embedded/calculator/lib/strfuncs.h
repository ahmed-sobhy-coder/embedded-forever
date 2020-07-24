#ifndef __STRFUNCS_H__
#define __STRFUNCS_H__
#include "stdint.h"
#include  "math.h" 
#include "string.h"
/*convert intger number to string of chars*/
int8_t* intToStr(int32_t num);
/*convert float number to string of chars*/
int8_t* floatToStr(double float_num, uint8_t precision);
/*get sting length */
uint8_t strLen(int8_t* string);
/* get get number of chars in string till reaching terminator*/
uint8_t strLenTerm(int8_t* str,int8_t term);
void strCopy(int8_t* str1, int8_t* str2);
//convert string to integer value
int32_t strToInt(int8_t* str);
/*
compare between two strings str1 & str2
if they are matched return 0
if str1>str2  return  1
if str1<str2  return  -1
*/
int8_t strCmp(int8_t* str1, int8_t* str2);
/*check if two strings are matched*/
int8_t strIsContain(int8_t* str1, int8_t* str2);
/* reverse string */
void strRev(int8_t* str);
/* check if the string contains only digits*/
int8_t isStrOfDigits(int8_t* str);
//search int8_tin string
int8_t charSearch(int8_t* str, int8_t ch);
/* convert string to float*/
double strToFloat(int8_t* str);

/*insert new char into string */
void insertChar(int8_t* str, int8_t ch, int8_t index);

/* delete char from string */
void  delChar(int8_t* str, int8_t index);

/*check if two strings are matched*/
int8_t strIsContain(int8_t* str1, int8_t* str2) ; 

/*get the index of str2 in str1*/
int8_t getStrIndex(int8_t* str1, int8_t* str2) ;

/*delete str1 from str2*/
void delStr(int8_t* str1,int8_t*str2) ;

//this function returns 1 if int8_tis in string & return 0 if not
int8_t strIsContainCh(int8_t* str, int8_t ch);

//insert str2 in str1
void insertStr(int8_t* str1, int8_t* str2, uint32_t index);

//convert double number to hex and store the result in string 
int8_t* convDoubleToHexStr(double num,uint8_t precision);

//convert double number to binary and store the result in string 
int8_t* convDoubleToBinStr(double num, uint8_t precision);

/*remove all spaces in string */
void remStrSpace(int8_t*str) ;

/*cout number of str2 in str1*/
int8_t strCountNoStr(int8_t* str1, int8_t* str2) ;

//search all chars before a given index
int8_t searchBefore(int8_t* str,int8_t ch,int8_t index);

#endif






