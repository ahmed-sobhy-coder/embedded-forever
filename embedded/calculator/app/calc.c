#include "calc.h"
static int8_t class0[5] = { '!', '~','-','+','\0' }; // unary operators
static int8_t class1[4] = { '*', '/', '%', '\0' };  //  arithmetic operatos
static int8_t class2[3] = { '+', '-', '\0' };//arithmetic operators
static int8_t class3[3] = { '<', '>', '\0' }; //logical operatos
static int8_t class4[4] = { '&','^','|','\0' };//bitwise operators
static int8_t class5[2] = { '=','\0' };//bitwise operators
#define SIZE 30
#define PRECISION 4
uint8_t numOpers = 0;  //flag to count number of operators in string, this variable is going to be used by extractnums function to help it to place number in nums array
uint8_t hex;    //hex=1 means print the result as hexadecimal
uint8_t bin;    //bin=1 means print the result as binary
uint8_t ascii;  //means get the accii code of char
uint8_t clr;
ERROR_TYPE ER;   //it is enum has all types of errors 
/*check if given character is operator*/
int8_t isOperator(int8_t oper)
{
    int8_t result = 0; //return -1 means it is not valid operator
    if ((strIsContainCh(class0, oper) == 1) ||   //in case char is in class0 string
        (strIsContainCh(class1, oper) == 1) ||  //in case char is in class1 2tring
        (strIsContainCh(class2, oper) == 1) ||    //in case char is in class1 string
        (strIsContainCh(class3, oper) == 1) ||   //in case char is in class3 string
        (strIsContainCh(class4, oper) == 1)      //in case char is in class4 string
        )
    {
        result = 1; // result 1 means it is valid operator
    }
    return result;   //return result
}
/*
  check if the given operator is unary opertor
  -unary operators are +,-,!,~
*/
int8_t isUnary(int8_t* str, int8_t index) {//check if '-' is minus or sub operator
    int result;// returns 1 if it is minus operator , and 0 if it is sub operator 
    /* if the character before '-' is valid opertor, '-' is unary minus */
    /*if '-' exists at the begining of string, it is unary minus*/
    if (((strIsContainCh(class0, str[index]) == 1) && (str[index - 1] == -1)) || // in case the char is unary operator and the previous char is unary operator
        ((strIsContainCh(class0, str[index]) == 1) && (str[index - 1] == -2)) || // in case the char is unary operator and the previous char is even operator
        ((strIsContainCh(class0, str[index]) == 1) && (index == 0)) //in case the first char is unary operator
        )
    {
        result = 1;//return it is unary minus
    }
    else
    {
        result = 0;//it is sub operator 
    }
    return result; //return the result
}
/* check if the given char is digit*/
uint8_t isDigitChar(int8_t ch)
{
    uint8_t result = 0;   //result 0 means by it is not digit char, 1 it is digit char
    if ((ch >= '0') && (ch <= '9')) //if ch is bewteen 0 and 9
    {
        result = 1; //it is digit
    }
    return result; //reuturn result
}
/*
optimize expression
for ex: ++4 str will be 4
    ex: -+4 str will be -4
*/
void strOptimize(int8_t* str)
{
    uint8_t count = 0;    //is used as a counter
    while (str[count] != '\0')  //loop all chars except null
    {
        if (str[count] == '+' && str[count + 1] == '+' && count == 0)  /* in case of ++ */
        {
            delChar(str, count + 1);/*delete '+' opertor*/
            delChar(str, count); /*delete '+' opertor*/
            count = 0; //reset counter
            continue;     //skip current loop
        }
        else if (str[count] == '+' && str[count + 1] == '+')  /* in case of ++ */
        {
            delChar(str, count + 1);/*delete '+' opertor*/
            count = 0; //reset counter
            continue;     //skip current loop
        }
        else if (str[count] == '+' && str[count + 1] == '-')  /* in case of +- */
        {
            delChar(str, count);  /*delete '+' opertor*/
            count = 0; //reset counter
            continue;     //skip current loop
        }
        else if (str[count] == '-' && str[count + 1] == '+') /* in case of -+ */
        {
            delChar(str, count + 1);   /*delete '+' opertor*/
            count = 0; //reset counter
            continue;     //skip current loop
        }
        else	if (str[count] == '-' && str[count + 1] == '-')   /* in case of -- */
        {
            str[count] = '+';     /*replace the first '+' with '-'*/
            delChar(str, count + 1);   /*delete the second '+' opertor*/
            count = 0; //reset counter
            continue;    //skip current loop
        }



        else if (str[count] == '+' && count == 0) /* in case of + is in the first index */
        {
            delChar(str, count);   /*delete '+' opertor*/
            count = 0; //reset counter
            continue;    //skip current loop
        }
        else if (str[count] == '(' && str[count + 1] == '+')
        {
            delChar(str, count + 1);   /*delete '+' opertor*/
            count = 0; //reset counter
            continue;    //skip current loop
        }
        else if (isOperator(str[count]) && str[count + 1] == '+')
        {
            delChar(str, count + 1);   /*delete '+' opertor*/
            count = 0; //reset counter
            continue;    //skip current loop		
        }
        count++; //increment counter
    }
}
/*
  -extract operators from string
  -place operator in opers array and also place $ in opers to indicate that this place is for number
*/
void extractOpers(int8_t* str, int8_t* opers)
{
    int8_t count1 = 0;//is used a s counter for all chars in string
    int8_t count2 = 0;//is used as a counter
    int8_t digit = 1;//flag to indicate that the next place if for digit not operator
                     //by default it it is 1 which means by default the next place if for digit  
                     //digit 0 means we have counted that number number and reserved it is place in opers and is waiting to next number
                     //digit=1 means place $ in opers to indicate it is place for number  
    numOpers = 0;
    while (str[count1] != '\0')  //loop all chars except null
    {
        while ((strIsContainCh(class0, str[count1]) == 1) && isUnary(str, count1))  //if it is unary operator
        {
            if (str[count1] == '-')  //if it is unary '-'
            {
                opers[count2] = '$'; //$ in opers means this place is for number 
                count2++;   //make counter2 poits to next place to place a new operator or $
                digit = 0; //digit 0 means we have counted that number number and reserved it is place in opers and is waiting to next number                          
            }
            else       /* it may be ! or ~ */
            {
                opers[count2] = str[count1];   //store operator
                str[count1] = -1; //replace operator with -1, it is indicator to exctractnums function that this place is for operator
                numOpers++; //increase numbre of opers
                count2++;   //make counter2 poits to next place to place a new operator or $
                digit = 1;//digit 0 means we have counted that number number and reserved it is place in opers and is waiting to next number
                           //digit=1 means place $ in opers to indicate it is place for number  
                        //digit=1 means place $ in opers to indicate it is place for number  						   
            }
            count1++;  //get the next character
        }
        if ((strIsContainCh(class1, str[count1]) == 1) ||     //in case it is * / % operator
            ((strIsContainCh(class2, str[count1]) == 1) &&    // in case it is + or -  operators
                (isUnary(str, count1) == 0))  //it is not a unary operator
            )
        {
            if (str[count1] == '*' && str[count1 + 1] == '*') // in case it is power operator
            {
                opers[count2] = POWER; //store operator in opers array
                delChar(str, count1 + 1); //delete * operator 
            }
            else       /*it may be + - * /  */
            {
                opers[count2] = str[count1];//in case it is ascii operator,store opertor in opers array
            }
            str[count1] = -2;  //replace operator with -2, it is indicator to exctractnums function that this place is for operator
            numOpers++;  //increase number of operators
            count2++;  //make counter2 poits to next place to place a new operator or $
            digit = 1;   //digit=1 means place $ in opers to indicate it is place for number                
        }
        else  if ((strIsContainCh(class3, str[count1]) == 1) && (strIsContainCh(class3, str[count1 + 1]) == 1))  // opers like >> or <<  operators

        {
            if (str[count1] == '>')opers[count2] = SHRIGHT;   //store operator in opers array
            else if (str[count1] == '<')opers[count2] = SHLEFT;   //store operator in opers array

            str[count1] = -2;//replace operator with -2, it is indicator to exctractnums function that this place is for operator
            delChar(str, count1 + 1);  //delete > or <
            numOpers++;  //increase number of operators           
            count2++; //make counter2 poits to next place to place a new operator or $
            digit = 1;      //digit=1 means place $ in opers to indicate it is place for number                    
        }
        else  if ((strIsContainCh(class3, str[count1]) == 1) &&  //in case >= or <= or ==
            (str[count1 + 1] == '='))
        {
            if (str[count1] == '>')opers[count2] = GREATER_THEN_EQUAL;  //store operator in opers array
            else if (str[count1] == '<')opers[count2] = LESS_THEN_EQUAL;  //store operator in opers array
            str[count1] = -2;//replace operator with -2, it is indicator to exctractnums function that this place is for operator
            delChar(str, count1 + 1); //delete = operator
            numOpers++;    //increase number of operators         
            count2++;   //make counter2 poits to next place to place a new operator or $
            digit = 1;  //digit=1 means place $ in opers to indicate it is place for number         
        }
        else  if (strIsContainCh(class3, str[count1]) == 1)/* in case > < operators  */
        {
            if (str[count1] == '>')opers[count2] = str[count1]; //store operator in opers array
            else if (str[count1] == '<')opers[count2] = str[count1];  //store operator in opers array
            str[count1] = -2; //replace operator with -2, it is indicator to exctractnums function that this place is for operator
            numOpers++;       //increase number of operators
            count2++;  //make counter2 poits to next place to place a new operator or $
            digit = 1;  //digit=1 means place $ in opers to indicate it is place for number    
        }
        else  if ((str[count1] == '=') && ((str[count1 + 1] == '=')))//in case == operator
        {
            opers[count2] = EQUALITY;  //store operator in opers array
            str[count1] = -2; //replace operator with -2, it is indicator to exctractnums function that this place is for operator
            delChar(str, count1 + 1);  //delete = operator
            numOpers++;      //increase number of operators
            count2++;  //make counter2 poits to next place to place a new operator or $            
            digit = 1;//digit=1 means place $ in opers to indicate it is place for number
        }
        else  if ((str[count1] == '!') && ((str[count1 + 1] == '=')))//in case != operator
        {
            opers[count2] = NOTEQUAL;  //store operator in opers array
            str[count1] = -2; //replace operator with -2, it is indicator to exctractnums function that this place is for operator
            delChar(str, count1 + 1);  //delete = operator
            numOpers++;   //increase number of operators            
            count2++;   //make counter2 poits to next place to place a new operator or $
            digit = 1;  //digit=1 means place $ in opers to indicate it is place for number            
        }
        else  if ((str[count1] == '&') && ((str[count1 + 1] == '&')))   //in case && operator
        {
            opers[count2] = LOGICAND;  //store operator in opers array
            str[count1] = -2;  //replace operator with -2, it is indicator to exctractnums function that this place is for operator
            delChar(str, count1 + 1); //delete & operator
            numOpers++;     //increase number of operators
            digit = 1;   //digit=1 means place $ in opers to indicate it is place for number  
            count2++;  //make counter2 poits to next place to place a new operator or $
        }
        else  if ((str[count1] == '|') && ((str[count1 + 1] == '|')))//in case || operators
        {
            opers[count2] = LOGICOR;   //store operator in opers array
            str[count1] = -2; //replace operator with -2, it is indicator to exctractnums function that this place is for operator
            delChar(str, count1 + 1);   //delete '|' operator
            numOpers++;    //increase number of operators
            digit = 1;    //digit=1 means place $ in opers to indicate it is place for number  
            count2++;//make counter2 poits to next place to place a new char
        }
        else  if (strIsContainCh(class4, str[count1]) == 1)//in case &,|,^ operator
        {
            opers[count2] = str[count1];   //store operator in opers array
            str[count1] = -2;   //replace operator with -2, it is indicator to exctractnums function that this place is for operator
            numOpers++;    //increase number of operators
            digit = 1;   //digit=1 means place $ in opers to indicate it is place for number  
            count2++; //make counter2 poits to next place to place a new char
        }
        if (digit == 1) {  //in case it is number
            if (str[count1 + 1] == '!' || str[count1 + 1] == '~')  //in case the next operator 
            {
                digit = 0; //digit 0 means we have counted that number number and reserved it is place in opers and is waiting to next number
            }
            else
            {
                opers[count2] = '$';  //$ in opers means this place is for number 
                count2++; //make counter2 poits to next place to place a new operator or $
                digit = 0; //digit 0 means we have counted that number number and reserved it is place in opers and is waiting to next number
            }
        }
        count1++; //increment count1 to get the next char
    }
    opers[count2] = '\0';  //terminate string with null
}
/*
   extract alls number in string and put them nums array taking into consideration their places in string
   -nums will be filled with numbers
*/
void extractnums(int8_t* str, double* nums, int8_t* opers) {
    int8_t count = 0;//points to next int8_tin string
    int8_t nextNum = 0;//points to next num
    int8_t index = 0;//index to the place to hold number
    int8_t nPers = numOpers;//to store number of operators
    while (str[count] != '\0')//loop all chars except nul
    {
        while ((str[count] == -1)) //it is logical not operator '!' or betwise not  
        {
            nextNum = count + 1;//get the number after ! operator,nextNum points to next number, 
            count++;//skip that operator
            nPers--;//decrease number of operators
        }
        if ((str[count] == -2))//it may be any operator except logical not or betwise not
        {
            str[count] = '\0'; //replace operator with null
            while (opers[index] != '$')//loop until find '$' which means it is a valid index to store number
            {
                nums[index] = 0;//fill invalid places with zeros,
                index++;//increment counter
            }
            nums[index] = strToFloat(str + nextNum);//store the number 
            nextNum = count + 1;//get the number after operator,nextNum points to next number 
            index++;//increment counter 3 to get a new place to hold the new number
            nPers--;//decrease number of operators
        }
        /*store the last number*/
        if (nPers == 0)//if numbr of operators is 0
        {
            while (opers[index] != '$')//loop until find '$' which means it is a valid index to store number
            {
                nums[index] = 0; //fill invalid places with zeros,
                index++; //increment counter
            }
            nums[index] = strToFloat(str + nextNum);//store the last number
            break;//stop looping
        }
        count++;//increment counter
    }
}

/*   check if the number if float or integer */
int8_t isFloat(double num) {
    uint8_t result = 0;   // initially we suppose it is integer
    double fpart;    //take the float part of the numbr
    if (num < 0)      //if the number is negative
    {
        num = num * -1;      //make the number positive
    }
    fpart = num - ((int32_t)num); //take the float part of number 
    if (fpart > 0.0)//if the float part is greater than 0
    {
        result = 1;  //it is float number 
    }
    return result; //return the result 
}

/*
  this function does all arithamtic and logic operations , it has two parameters
  -nums array : array which has all numbers in string

*/
double strCalc(double* nums, int8_t* opers)
{
    int8_t c1 = 0;    //initial value for counter c1
    uint8_t len = strLen(opers);//get string length 
    double result;//store the result of operation into result variable 
   /*  loop all unary operators from right to left*/
    for (c1 = strLen(opers) - 1; c1 >= 0; c1--)
    {
        if (opers[c1] == '!')  //in case it is not operator
        {
            result = !nums[c1 + 1];    //do operation in the number after unary operator
            nums[c1] = result;         //store the result in place of unary operator  in nums array
            delChar(opers, c1);        //delete unary operator in opers array which means we have done out calculation 
            delDoubleElement(nums, c1 + 1, len); //delete the place after unary operator which is for  number
            len = strLen(opers); //get the length of opers string
            c1 = len; //reiniialize c1 to loop from the begining
        }
        if (opers[c1] == '~')   //in case it is betwise not operator
        {
            if (isFloat(nums[c1 + 1]) == 1)   // bitwise not is not valid with float number
            {
                ER = INVALID_OPERAND;    //indicate it is an error       
				break;   //    stop looping, there is error

            }
            else
            {
                result = ~((int32_t)(nums[c1 + 1])); //do operation in the number after unary operator
                nums[c1] = result; //store the result in place of unary operator  in nums array
                delChar(opers, c1 + 1); //delete unary operator in opers array which means we have done out calculation 
                delDoubleElement(nums, c1 + 1, len);   //delete the place after unary operator which is for  number
                len = strLen(opers); //get the length of opers string
                c1 = len; //reiniialize c1 to loop from the begining
            }

        }
    }
    /* loop all arithmatice and logic operators from left to rigth*/
    for (c1 = 0; (c1 < strLen(opers)) && (ER == NO_ERROR); c1++)
    {
        if (opers[c1] == POWER)   //in case it is power operator
        {
            result = getPower(nums[c1 - 1], nums[c1 + 1]);   //do power operation to numbers before and after ** operator
            nums[c1 - 1] = result;    //stroe the result into the first number before operator
            delChar(opers, c1 + 1); //delete $ after operator because we have done our calculation in the number after operator
            delChar(opers, c1);//delete   operator itsel
            delDoubleElement(nums, c1 + 1, len);   //delete number after operator place in nums array
            delDoubleElement(nums, c1, len);       //delete operatore place  in nums array
            len -= 2;         //string length has been decreased by two
            c1 = 0;     //resets counter to the begining after string changes
        }
    }
    /*loop all operators from left to rigth*/
    for (c1 = 0; (c1 < strLen(opers)) && (ER == NO_ERROR); c1++)
    {
        if (opers[c1] == '*')  //in case it multiplication operation
        {
            result = nums[c1 - 1] * nums[c1 + 1];  //do mul operation to numbers before and after * operator
            nums[c1 - 1] = result;  //stroe the result into the first number before operator
            delChar(opers, c1 + 1);//delete $ after operator because we have done our calculation in the number after operator
            delChar(opers, c1);    //delete   operator itsel
            delDoubleElement(nums, c1 + 1, len);    //delete number after operator place in nums array
            delDoubleElement(nums, c1, len);  //delete operatore place  in nums array
            len -= 2;    //string length has been decreased by two
            c1 = 0;    //resets counter to the begining after string changes
        }
        if (opers[c1] == '/')   //in case it is division operator
        {
            result = nums[c1 - 1] / nums[c1 + 1]; //do division operation to numbers before and after ** operator
            nums[c1 - 1] = result;  //stroe the result into the first number before operator
            delChar(opers, c1 + 1);//delete $ after operator because we have done our calculation in the number after operator
            delChar(opers, c1);     //delete   operator itsel
            delDoubleElement(nums, c1 + 1, len);   //delete number after operator place in nums array
            delDoubleElement(nums, c1, len); //delete operatore place  in nums array
            len -= 2;    //string length has been decreased by two
            c1 = 0;    //resets counter to the begining after string changes
        }
        if (opers[c1] == '%')   //in case it is reminder operation
        {
            if ((isFloat(nums[c1 - 1]) == 1) || (isFloat(nums[c1 + 1]) == 1))   //numbers before and after reminder operator must be integers
            {
                ER = INVALID_OPERAND; //if one of operands is integers rise invalid operand error
                break;         //    stop looping, there is error
            }
            else
            {
                result = (int32_t)nums[c1 - 1] % (int32_t)nums[c1 + 1];//do reminer operation beetween numbers before and after operator 
                nums[c1 - 1] = result; //stroe the result into the first number before operator
                delChar(opers, c1 + 1);  //delete $ after operator because we have done our calculation in the number after operator
                delChar(opers, c1);   //delete   operator itsel
                delDoubleElement(nums, c1 + 1, len);    //delete number after operator place in nums array
                delDoubleElement(nums, c1, len);  //delete operatore place  in nums array
                len -= 2;    //string length has been decreased by two
                c1 = 0;     //resets counter to the begining after string changes
            }

        }
    }
    /*loop all operators from left to rigth*/
    for (c1 = 0; (c1 < strLen(opers)) && (ER == NO_ERROR); c1++)
    {
        if (opers[c1] == '+') //in case it is add operation 
        {
            result = nums[c1 - 1] + nums[c1 + 1]; // do add operation between numebers after and before plus operator 
            nums[c1 - 1] = result;  //stroe the result into the first number before operator
            delChar(opers, c1 + 1);  //delete $ after operator because we have done our calculation in the number after operator
            delChar(opers, c1);   //delete operator itsel
            delDoubleElement(nums, c1 + 1, len);  //delete number after operator place in nums array
            delDoubleElement(nums, c1, len); //delete operatore place  in nums array
            len -= 2;     //string length has been decreased by two
            c1 = 0;    //resets counter to the begining after string changes
        }
        if (opers[c1] == '-') // in case it is subtract operator 
        {
            result = nums[c1 - 1] - nums[c1 + 1]; // do sub opertion beteween numbers after and before sub opertor 
            nums[c1 - 1] = result;  //stroe the result into the first number before operator
            delChar(opers, c1 + 1);  //delete $ after operator because we have done our calculation in the number after operator
            delChar(opers, c1);   //delete operator itsel
            delDoubleElement(nums, c1 + 1, len);   //delete number after operator place in nums array
            delDoubleElement(nums, c1, len);   //delete operatore place  in nums array
            len -= 2;    //string length has been decreased by two
            c1 = 0;     //resets counter to the begining after string changes
        }
    }
    /*loop all operators from left to rigth*/
    for (c1 = 0; (c1 < strLen(opers)) && (ER == NO_ERROR); c1++)
    {
        if (opers[c1] == SHRIGHT)  // in case it is shift rigth opertion
        {
            if ((isFloat(nums[c1 - 1]) == 1) || (isFloat(nums[c1 + 1]) == 1))
            {
                ER = INVALID_OPERAND; //if one of operands is integers rise invalid operand error
                break;    //    stop looping, there is error
            }
            else
            {
                result = (int32_t)nums[c1 - 1] >> (int32_t)nums[c1 + 1]; //do shift operation between nunbers after and before 
                nums[c1 - 1] = result; //stroe the result into the first number before operator
                delChar(opers, c1 + 1); //delete $ after operator because we have done our calculation in the number after operator
                delChar(opers, c1);  //delete operator itsel
                delDoubleElement(nums, c1 + 1, len);   //delete number after operator place in nums array
                delDoubleElement(nums, c1, len);   //delete operatore place  in nums array
                len -= 2;    //string length has been decreased by two
                c1 = 0;       //resets counter to the begining after string changes
            }

        }
        if (opers[c1] == SHLEFT) // in case it shift left operation 
        {
            if ((isFloat(nums[c1 - 1]) == 1) || (isFloat(nums[c1 + 1]) == 1))
            {
                ER = INVALID_OPERAND; //if one of operands is integers rise invalid operand error
                break;      //    stop looping, there is error

            }
            else
            {
                result = (int32_t)nums[c1 - 1] << (int32_t)nums[c1 + 1]; //do shift left operation bwtween numbers before and after operaor 
                nums[c1 - 1] = result; //stroe the result into the first number before operator
                delChar(opers, c1 + 1); //delete $ after operator because we have done our calculation in the number after operator
                delChar(opers, c1);    //delete operator itsel
                delDoubleElement(nums, c1 + 1, len);   //delete number after operator place in nums array
                delDoubleElement(nums, c1, len);   //delete operatore place  in nums array
                len -= 2;    //string length has been decreased by two
                c1 = 0;      //resets counter to the begining after string changes
            }

        }
    }
    /*loop all operators from left to rigth*/
    for (c1 = 0; (c1 < strLen(opers)) && (ER == NO_ERROR); c1++)
    {
        if (opers[c1] == GREATER_THEN_EQUAL) // in case it is >=, greater than or equal operation 
        {

            result = (nums[c1 - 1] >= nums[c1 + 1]); //do operation between numbers before and after operator 
            nums[c1 - 1] = result; //stroe the result into the first number before operator
            delChar(opers, c1 + 1);  //delete $ after operator because we have done our calculation in the number after operator
            delChar(opers, c1);   //delete operator itsel
            delDoubleElement(nums, c1 + 1, len);   //delete number after operator place in nums array
            delDoubleElement(nums, c1, len);   //delete operatore place  in nums array
            len -= 2;   //string length has been decreased by two
            c1 = 0;     //resets counter to the begining after string changes
        }
        if (opers[c1] == LESS_THEN_EQUAL) //in case it less than or equal opertion 
        {

            result = (nums[c1 - 1] <= nums[c1 + 1]);//do operation between numbers before and after operator 
            nums[c1 - 1] = result; //stroe the result into the first number before operator
            delChar(opers, c1 + 1); //delete $ after operator because we have done our calculation in the number after operator
            delChar(opers, c1);  //delete operator itsel
            delDoubleElement(nums, c1 + 1, len);   //delete number after operator place in nums array
            delDoubleElement(nums, c1, len);   //delete operatore place  in nums array
            len -= 2;    //string length has been decreased by two
            c1 = 0;       //resets counter to the begining after string changes
        }
        if (opers[c1] == '>') //in case it greater operation 
        {

            result = nums[c1 - 1] > nums[c1 + 1];//do operation between numbers before and after operator 
            nums[c1 - 1] = result; //stroe the result into the first number before operator
            delChar(opers, c1 + 1); //delete $ after operator because we have done our calculation in the number after operator
            delChar(opers, c1);   //delete operator itsel
            delDoubleElement(nums, c1 + 1, len);    //delete number after operator place in nums array
            delDoubleElement(nums, c1, len);   //delete operatore place  in nums array
            len -= 2;   //string length has been decreased by two
            c1 = 0;     //resets counter to the begining after string changes
        }
        if (opers[c1] == '<')  // in case it is less than operation 
        {

            result = nums[c1 - 1] < nums[c1 + 1];//do operation between numbers before and after operator 
            nums[c1 - 1] = result;   //stroe the result into the first number before operator
            delChar(opers, c1 + 1); //delete $ after operator because we have done our calculation in the number after operator
            delChar(opers, c1);   //delete operator itsel
            delDoubleElement(nums, c1 + 1, len);  //delete number after operator place in nums array
            delDoubleElement(nums, c1, len);     //delete operatore place  in nums array
            len -= 2;    //string length has been decreased by two
            c1 = 0;      //resets counter to the begining after string changes
        }
    }
    /*loop all operators from left to rigth*/
    for (c1 = 0; (c1 < strLen(opers)) && (ER == NO_ERROR); c1++)
    {
        if (opers[c1] == EQUALITY) //in case it is == operation  
        {

            result = nums[c1 - 1] == nums[c1 + 1];//do operation between numbers before and after operator 
            nums[c1 - 1] = result;  //stroe the result into the first number before operator
            delChar(opers, c1 + 1);  //delete $ after operator because we have done our calculation in the number after operator
            delChar(opers, c1);    //delete operator itsel
            delDoubleElement(nums, c1 + 1, len); //delete number after operator place in nums array
            delDoubleElement(nums, c1, len);   //delete operatore place  in nums array
            len -= 2;    //string length has been decreased by two
            c1 = 0;      //resets counter to the begining after string changes
        }
        if (opers[c1] == NOTEQUAL) // in case it is != operation 
        {

            result = nums[c1 - 1] != nums[c1 + 1]; //do operation between numbers before and after operator 
            nums[c1 - 1] = result;//stroe the result into the first number before operator
            delChar(opers, c1 + 1); //delete $ after operator because we have done our calculation in the number after operator
            delChar(opers, c1);    //delete operator itsel
            delDoubleElement(nums, c1 + 1, len); //delete number after operator place in nums array
            delDoubleElement(nums, c1, len);  //delete operatore place  in nums array
            len -= 2;   //string length has been decreased by two
            c1 = 0;     //resets counter to the begining after string changes
        }
    }
    /*loop all operators from left to rigth*/
    for (c1 = 0; (c1 < strLen(opers)) && (ER == NO_ERROR); c1++)
    {
        if (opers[c1] == '&') // in case  it bitwise & operator 
        {
            if ((isFloat(nums[c1 - 1]) == 1) || (isFloat(nums[c1 + 1]) == 1))
            {
                ER = INVALID_OPERAND; //if one of operands is integers rise invalid operand error
                break;    //    stop looping, there is error
            }
            else
            {
                result = (int32_t)nums[c1 - 1] & (int32_t)nums[c1 + 1]; //do operation between numbers before and after operator 
                nums[c1 - 1] = result;  //stroe the result into the first number before operator
                delChar(opers, c1 + 1); //delete $ after operator because we have done our calculation in the number after operator
                delChar(opers, c1);    //delete operator itsel
                delDoubleElement(nums, c1 + 1, len);  //delete number after operator place in nums array
                delDoubleElement(nums, c1, len);   //delete operatore place  in nums array
                len -= 2;   //string length has been decreased by two
                c1 = 0;      //resets counter to the begining after string changes
            }

        }
    }
    /*loop all operators from left to rigth*/
    for (c1 = 0; (c1 < strLen(opers)) && (ER == NO_ERROR); c1++)
    {
        if (opers[c1] == '^') // in case it is xor operation 
        {
            if ((isFloat(nums[c1 - 1]) == 1) || (isFloat(nums[c1 + 1]) == 1))
            {
                ER = INVALID_OPERAND; //if one of operands is integers rise invalid operand error
                break;  //    stop looping, there is error
            }
            else
            {
                result = (int32_t)nums[c1 - 1] ^ (int32_t)nums[c1 + 1];
                nums[c1 - 1] = result;   //stroe the result into the first number before operator
                delChar(opers, c1 + 1);  //delete $ after operator because we have done our calculation in the number after operator
                delChar(opers, c1);   //delete operator itsel
                delDoubleElement(nums, c1 + 1, len);  //delete number after operator place in nums array
                delDoubleElement(nums, c1, len);   //delete operatore place  in nums array
                len -= 2;    //string length has been decreased by two
                c1 = 0;       //resets counter to the begining after string changes
            }

        }
    }
    /*loop all operators from left to rigth*/
    for (c1 = 0; (c1 < strLen(opers)) && (ER == NO_ERROR); c1++)
    {
        if (opers[c1] == '|') // in case it is or operation 
        {
            if ((isFloat(nums[c1 - 1]) == 1) || (isFloat(nums[c1 + 1]) == 1))
            {
                ER = INVALID_OPERAND; //if one of operands is integers rise invalid operand error
                break;  //stop looping, there is error
            }
            else
            {
                result = (int32_t)nums[c1 - 1] | (int32_t)nums[c1 + 1]; //do operation between numbers before and after operator 
                nums[c1 - 1] = result;  //stroe the result into the first number before operator
                delChar(opers, c1 + 1); //delete $ after operator because we have done our calculation in the number after operator
                delChar(opers, c1);   //delete operator itsel
                delDoubleElement(nums, c1 + 1, len); //delete number after operator place in nums array
                delDoubleElement(nums, c1, len);   //delete operatore place  in nums array
                len -= 2;   //string length has been decreased by two
                c1 = 0;      //resets counter to the begining after string changes
            }

        }
    }
    /*loop all operators from left to rigth*/
    for (c1 = 0; (c1 < strLen(opers)) && (ER == NO_ERROR); c1++)
    {
        if (opers[c1] == LOGICAND) // in case it is && operation 
        {

            result = nums[c1 - 1] && nums[c1 + 1]; //do operation between numbers before and after operator 
            nums[c1 - 1] = result;   //stroe the result into the first number before operator
            delChar(opers, c1 + 1); //delete $ after operator because we have done our calculation in the number after operator
            delChar(opers, c1);    //delete operator itsel
            delDoubleElement(nums, c1 + 1, len);  //delete number after operator place in nums array
            delDoubleElement(nums, c1, len);    //delete operatore place  in nums array
            len -= 2;    //string length has been decreased by two
            c1 = 0;       //resets counter to the begining after string changes
        }
    }
    /*loop all operators from left to rigth*/
    for (c1 = 0; (c1 < strLen(opers)) && (ER == NO_ERROR); c1++)
    {
        if (opers[c1] == LOGICOR) //in case it is || operation 
        {

            result = (nums[c1 - 1] || nums[c1 + 1]); //do operation between numbers before and after operator 
            nums[c1 - 1] = result;   //stroe the result into the first number before operator
            delChar(opers, c1 + 1); //delete $ after operator because we have done our calculation in the number after operator
            delChar(opers, c1);   //delete operator itsel
            delDoubleElement(nums, c1 + 1, len);  //delete number after operator place in nums array
            delDoubleElement(nums, c1, len);   //delete operatore place  in nums array
            len -= 2;     //string length has been decreased by two
            c1 = 0;        //resets counter to the begining after string changes
        }
    }


    return nums[0];     //return first element in nums array which has the final result
}

/*
  this function is used to do operations in the previous result
  it simply remove ans string from expression and replaces it with the previous value
*/
ERROR_TYPE handleAns(int8_t* str, double* nums, uint8_t prev)
{
    uint8_t index;    //index of ans  in expression
    if (ER == NO_ERROR)
    {
        if ((strIsContain(str, "ans")) || (strIsContain(str, "ANS") == 1))
        {
            if (prev == 1)
            {
                while (strIsContain(str, "ans") == 1)   //if the expression contains ans
                {
                    index = getStrIndex(str, "ans");   //get the index of ans
                    delStr(str, "ans");  //delete ans string
                    insertStr(str, floatToStr(nums[0], 4), index);   //replace ans with previous value
                }
                while (strIsContain(str, "ANS") == 1) //in case it is capital ANS 
                {
                    index = getStrIndex(str, "ANS");     //remove capital ANS
                    delStr(str, "ANS"); //delete ANS string 
                    insertStr(str, floatToStr(nums[0], 4), index);//replace ans with previous value
                }
            }
            else
            {
                ER = INVALID_NO_PREV;   //no previous result to be replaced
            }
        }
    }
    return ER;//return error type
}

/*handle all () in string */
ERROR_TYPE handleParenthesis(int8_t* str)
{
    double fnums[SIZE];//array to store numbers
    int8_t opers[SIZE]; //array to store operators
    int8_t cpy[SIZE];//holds all chars after ')' char
    int8_t firstBraceIndx;//index of the roud brace
    int8_t SecondBraceIndx;//index of the roud brace
    int8_t* ptr;//pointer to float string
    uint8_t count1 = 0;//is used as counter
    uint8_t count2 = 0;//is used as counter,//is counter for next char in cpy string to be stored in original string  
    if (ER == NO_ERROR)
    {
        while (strIsContainCh(str, ')') == 1) //loop until all ')' is removed from string 
        {
            SecondBraceIndx = charSearch(str, ')');//get the index of ')'
            firstBraceIndx = searchBefore(str, '(', SecondBraceIndx - 1);//get the index of '('
            if (firstBraceIndx >= 0)//if the index of '(' is in string
            {
                strCopy(cpy, str + SecondBraceIndx + 1);//copy the string after ')' operator into cpy array
                str[SecondBraceIndx] = '\0';//replace ')' with null		
                extractOpers(str + firstBraceIndx + 1, opers);//extract all operators from the new string
                extractnums(str + firstBraceIndx + 1, fnums, opers);//extract all numbers
                ptr = floatToStr(strCalc(fnums, opers), 3);//ptr is point to float string , the float result is evaluated from strCalc function
                count1 = firstBraceIndx;//count is used as a counter and initially has the index of '('
                while (str[count1] != '\0')//delate all chars between '(' and ')' include also '(' and ')'
                {
                    delChar(str, firstBraceIndx);//delete character
                }

                count1 = 0;//reset counter to store the float result of the previous string
                while (ptr[count1] != '\0')
                {
                    insertChar(str, ptr[count1], firstBraceIndx + count1);//insert float string in the original string
                    count1++;//increment counter
                }
                while (cpy[count2] != '\0')//insert all chars which are after ')' in the original string
                {
                    insertChar(str, cpy[count2], firstBraceIndx + count1);//insert the string after ')'
                    count1++;//increment count1
                    count2++;//increment count2
                }
                count2 = 0;//reinitialize count2 to 0 which is counter for next char in cpy string to be stored in original string  
            }
            else
            {
                ER = INVALID_BRACES;//error in braces
                break;
            }
        }
        if (strIsContainCh(str, '(') == 1)   //if '(' is in string without ')'
        {
            ER = INVALID_BRACES;//error in braces
        }
    }
    return ER;  //return type of error
}
/*
  if the user want the result to be in hexa or binary, this function only activates flag hex and bin
  and removes hex and bin strings from expresion
*/
ERROR_TYPE typeConverstionandle(int8_t* str, double* preValue, uint8_t prev)
{
    if (ER == NO_ERROR)
    {

        if (strIsContain(str, "hex("))  //make the result of this string expression to be in sex
        {
            if (strIsContain(str, ")") && (str[charSearch(str, ')') + 1] == '\0'))
            {
                delStr(str, "hex"); //delete "hex" string from expression
                prev = 1;  //s
                hex = 1;
            }
            else
            {
                ER = INVALID_CONVERSION;
            }
        }
        else if (strIsContain(str, "hex") == 1)  /* make the previous resut hex*/
        {
            if ((prev == 1) && (strLen(str) == 3))
            {
                delStr(str, "hex"); //delete "hex" string from expression
                hex = 1;//activate hex flag
            }
            else
            {
                ER = INVALID_CONVERSION;
            }
        }
        else if (strIsContain(str, "bin("))  //make the result of this string expression to be in sex
        {
            if (strIsContain(str, ")") && (str[charSearch(str, ')') + 1] == '\0'))
            {
                delStr(str, "bin"); //delete "bin" string from expression
                prev = 1;
                bin = 1;
            }
            else
            {
                ER = INVALID_CONVERSION;
            }
        }
        else if (strIsContain(str, "bin") == 1)  /* make the previous resut hex*/
        {
            if ((prev == 1) && (strLen(str) == 3))
            {
                delStr(str, "bin"); //delete "bin" string from expression
                bin = 1;//activate hex flag 
            }
            else
            {
                ER = INVALID_CONVERSION;
            }
        }
    }
    return ER;
}
/* check if the given char is between a and z or bwtween A and Z*/
uint8_t isChar(int8_t ch)
{
    uint8_t result = 0; //the which will be returned is stored in result
                   //0  means it is not valid char
                   //1  means it is valid char
    if (((ch >= 'a') && (ch <= 'z')) || (((ch >= 'A') && (ch <= 'Z')))) //if char is between a and z or bwtween A and Z
    {
        result = 1;  //1  means it is valid char
    }
    return result; //return the result
}
/*
  this function returns 1 when there is digit or ans/ANS string after opertor
  return 0 if not

*/
uint8_t isValidOper(int8_t* str)
{
    uint8_t result = 0;   //return 0 it means invalid string after operator
    uint8_t count = 0;    //is used as counter
	if(strIsContain(str,"ans")||(strIsContain(str,"ANS")))   //if after opertor ans/ANS is valid
	{
			  result=1;   //return 1 means it is valid string after opertor 
	}
	else //there is no ans/ANS string after operator, now check if there is any digit
	{
	     while (str[count] != '\0')           //loop all chars except null
    {
        if (isDigitChar(str[count]))         //if there is any digit after opertor it is valid string after operator
        {
            result = 1;  //return 1 means it is valid string after opertor 
            break;    //if digit found stop looping 

        }
        count++;      //get next character
    }
	}

    return result;    //return result
}
ERROR_TYPE strRules(int8_t* str)
{
    uint8_t count = 0; //is used as counter
    uint8_t oneTimeCountr = 0;
    for (oneTimeCountr = 0; oneTimeCountr < 1; oneTimeCountr++)
    {
        remStrSpace(str);//remove all spaces in stirng   
        if ((strLen(str) == 0)) //if string length is 0 it is error
        {                                                                     
            ER = INVALID_EXPRESSION;    //if string length is 0 it is error
            break; //break current loop
        }
        /* in case string contains +) or -) or *) any operator before ')'*/
        if ((strIsContainCh(str, ')') == 1) && (isOperator(str[charSearch(str, ')') - 1])))
        {
            ER = INVALID_OPER; //it is operator error
            break;
        }
        /* in case string index 0 has & or > or < or any kind of operator*/
        if (strIsContainCh(class1, str[0]) ||   //is the first char in string is * or / or %
            strIsContainCh(class3, str[0]) ||   //is the first char in string os > or < 
            strIsContainCh(class4, str[0]) ||    //is the first char in string is & or | 
            strIsContainCh(class5, str[0])     //is the first char in string is & or | 

            )
        {
            ER = INVALID_EXPRESSION; //braces error
            break;
        }

        if (strIsContain(str, "()"))   //if string contains empty ()
        {
            ER = INVALID_BRACES; //braces error
            break;
        }
        /* in valid chars in string expression*/
        if (strIsContainCh(str, '#') ||
            strIsContainCh(str, '@') ||
            strIsContainCh(str, '_') ||
            strIsContainCh(str, '?') ||
            strIsContainCh(str, '\'') ||
            strIsContainCh(str, '\"') ||
            strIsContainCh(str, '\\') ||
            strIsContainCh(str, ':') ||
            strIsContainCh(str, '$') ||
            strIsContainCh(str, ';') ||
            strIsContainCh(str, '[') ||
            strIsContainCh(str, ']')
            )
        {
            ER = INVALID_CHAR;   //return invalid char error
            break;
        }
        /* in case string has  >&*  or <> or >>> or any invalid operators */
        while (str[count] != '\0')
        {
            if (((strIsContainCh(class0, str[count])) && (strIsContainCh(class1, str[count + 1]))) ||  // +*,!*, +/,...
                ((strIsContainCh(class0, str[count])) && (strIsContainCh(class3, str[count + 1]))) ||  // !>, +<,... 
                ((strIsContainCh(class0, str[count])) && (strIsContainCh(class4, str[count + 1]))) ||  // !&, -|,...
                ((strIsContainCh(class0, str[count])) && (strIsContainCh(class5, str[count + 1]))) ||  // += or -= but != is valid
                ((strIsContainCh(class5, str[count])) && (strIsContainCh(class0, str[count + 1]))) ||   // =!, =+, =-,...


                ((strIsContainCh(class1, str[count])) && (strIsContainCh(class1, str[count + 1]))) ||  // //, %%,..
                ((strIsContainCh(class1, str[count])) && (strIsContainCh(class3, str[count + 1]))) ||  // *>, /<,..
                ((strIsContainCh(class3, str[count])) && (strIsContainCh(class1, str[count + 1]))) ||  // >*, </,..
                ((strIsContainCh(class1, str[count])) && (strIsContainCh(class4, str[count + 1]))) ||  // *&, %|,..
                ((strIsContainCh(class4, str[count])) && (strIsContainCh(class1, str[count + 1]))) ||  //  &*, *&,..

                ((strIsContainCh(class3, str[count])) && (strIsContainCh(class3, str[count + 1]))) ||  //  ><,<>,..
                ((strIsContainCh(class4, str[count])) && (strIsContainCh(class4, str[count + 1]))) ||  //  |&,&^,..



                ((strIsContainCh(class4, str[count])) && (strIsContainCh(class5, str[count + 1]))) ||  //  &=,|=,..
                ((strIsContainCh(class5, str[count])) && (strIsContainCh(class4, str[count + 1]))) ||   //=& ,=|,..
                ((strIsContainCh(class4, str[count])) && (strIsContainCh(class3, str[count + 1]))) ||     //&> or |<
                ((strIsContainCh(class3, str[count])) && (strIsContainCh(class4, str[count + 1]))) ||     //<& or >|


                ((strIsContainCh(class5, str[count])) && (strIsContainCh(class3, str[count + 1]))) ||     //=>,=<

                				
                ((strIsContainCh(class0, str[count])) && (isValidOper(str + count + 1) == 0)) ||   //in case there is no any digit or ans string after operator
				((strIsContainCh(class1, str[count])) && (isValidOper(str + count + 1) == 0)) ||   //in case there is no any digit or ans string after operator
				((strIsContainCh(class3, str[count])) && (isValidOper(str + count + 1) == 0)) ||   //in case there is no any digit or ans string after operator
				((strIsContainCh(class4, str[count])) && (isValidOper(str + count + 1) == 0)) ||   //in case there is no any digit or ans string after operator
				
				(str[count] == '.' && isOperator(str[count + 1])) ||   //in case of .> or .+,...
                
				(strIsContainCh(class5, str[count])==1)   //only '=' exist 
                )
            {
                if ((str[count] == '*') && (str[count + 1] == '*') &&  //** is valid 
                    ((isDigitChar(str[count + 2])) || (strIsContainCh(class0, str[count + 2]))))count++;
                else if ((str[count] == '>') && (str[count + 1] == '>') &&    //>> is valid
                    ((isDigitChar(str[count + 2])) || (strIsContainCh(class0, str[count + 2]))))count++;
                else if ((str[count] == '<') && (str[count + 1] == '<') &&     //<< is valid
                    ((isDigitChar(str[count + 2])) || (strIsContainCh(class0, str[count + 2]))))count++;
                else if ((str[count] == '!') && (str[count + 1] == '=') &&      //!= is valid
                    ((isDigitChar(str[count + 2])) || (strIsContainCh(class0, str[count + 2]))))count++;
                else if ((str[count] == '=') && (str[count + 1] == '=') &&       // == is valid
                    ((isDigitChar(str[count + 2])) || (strIsContainCh(class0, str[count + 2]))))count++;
                else if ((str[count] == '&') && (str[count + 1] == '&') &&       // && is valid
                    ((isDigitChar(str[count + 2])) || (strIsContainCh(class0, str[count + 2]))))count++;
                else if ((str[count] == '|') && (str[count + 1] == '|') &&       // || is valid
                    ((isDigitChar(str[count + 2])) || (strIsContainCh(class0, str[count + 2]))))count++;
                else {
                    ER = INVALID_EXPRESSION; //invalid operator
                    break;
                }
            }
            else if ((str[count] == '>') && (str[count + 1] == '=') &&      //>= is valid
                ((isDigitChar(str[count + 2])) || (strIsContainCh(class0, str[count + 2]))))count++;
            else if ((str[count] == '<') && (str[count + 1] == '=') &&      //<= is valid
                ((isDigitChar(str[count + 2])) || (strIsContainCh(class0, str[count + 2]))))count++;
            else if (isChar(str[count]))
            {
                if ((str[count] == 'a') && (str[count + 1] == 'n') &&      //ans is valid
                    (str[count + 2] == 's'))count += 2;
                else if ((str[count] == 'A') && (str[count + 1] == 'N') &&      //ANS is valid
                    (str[count + 2] == 'S'))count += 2;

                else if ((str[count] == 'h') && (str[count + 1] == 'e') &&      //hex is valid
                    (str[count + 2] == 'x'))count += 2;
                else if ((str[count] == 'H') && (str[count + 1] == 'E') &&      //HEX is valid
                    (str[count + 2] == 'X'))count += 2;

                else if ((str[count] == 'b') && (str[count + 1] == 'i') &&      //bin is valid
                    (str[count + 2] == 'n'))count += 2;
                else if ((str[count] == 'B') && (str[count + 1] == 'I') &&      //BIN is valid
                    (str[count + 2] == 'N'))count += 2;
				
				else if ((str[count] == 'c') && (str[count + 1] == 'l') &&      //clear is valid
                    (str[count + 2] == 'e')&&(str[count+3]=='a')&&(str[count+4]=='r'))count += 4;
				else if ((str[count] == 'C') && (str[count + 1] == 'L') &&      //clear is valid
                    (str[count + 2] == 'E')&&(str[count+3]=='A')&&(str[count+4]=='R'))count += 4;
                else
                {
                    ER = INVALID_EXPRESSION; //invalid expression
                    break;      //break current loop
                }
            }


            count++; //incrment counter to go to next char 
        }




    }
    return ER;     //return the type of error

}
/*clear the previous result*/
void clearHandle(int8_t* str,int8_t* prev)
{
    if (strIsContain(str, "clear") == 1)  /* clear the previous result*/
    {
        if (strLen(str) == 5)    //if string length is 5
        {
            delStr(str, "clear"); //delete "clear" string
			*prev=0;//reset prev flag   		
            clr=1; //clear = 1 means that the previous hab been cleared			

        }
        else    //string is greater than 5
        {
            ER = INVALID_EXPRESSION;//the input expression is not valid 
        }
    }
}
double calculator(int8_t* str)
{
    int8_t opers[SIZE];//is used to store operators after extracting them from str
    static double nums[SIZE];//is used to store numbers after extracting them from str
	static uint8_t prev = 0;//flag to indicate, that you can work in the previous result 
    double result; //is used to return the result to user
    strRules(str); // check string expression rules 
    typeConverstionandle(str, nums, prev); // do type conversion in case the user want the result as hex or binary 
    handleAns(str, nums, prev); //in case the user wants to worl with the result of the previous operation
    strOptimize(str);// do string optimization in case the expression is +++n or  ++-- 
    handleParenthesis(str); // remove parenthesis after evaluation , it has the highest priotiy 
	clearHandle(str,&prev);//clear the previous result
    if ((ER == NO_ERROR)&&(clr==0)) // in case there is no error comes from string expression or from evaluation of string expression 
    {
        extractOpers(str, opers); //extract operators from string 
        extractnums(str, nums, opers);// extract numbers form string
        result = strCalc(nums, opers); //do calculation between operators and numbers numbers
        prev = 1; //rise flag to be seen by handleAns function and typeConverstionandle function  
    }
    else
    {
        //it means it is no valid result
    }
    return result;
}
