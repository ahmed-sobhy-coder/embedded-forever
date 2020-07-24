#ifndef __bit_H__
#define __bit_H__
//****************************************************************
// BS manipulation
//****************************************************************

#define B(I)                    (0x01U<<I) //shift to index
#define STV(R,V)                 (R=V)
#define ST1B(R,I)                (R|=B(I))
#define ST2B(R,I1,I2)            (R|=B(I1)|B(I2))
#define ST3B(R,I1,I2,I3)         (R|=B(I1)|B(I2)|B(I3))
#define ST4B(R,I1,I2,I3,I4)         (R|=B(I1)|B(I2)|B(I3)|B(I4))
#define SETALL(R)    (R=0xFFU)

#define CLR1B(R,I)               (R&=(~B(I)))
#define CLR2B(R,I1,I2)           (R&=~(B(I1)|B(I2)))
#define CLR3B(R,I1,I2,I3)        (R &=~(B(I1)|B(I2)|B(I3)))
#define CLR4B(R,I1,I2,I3,I4)     (R &=~(B(I1)|B(I2)|B(I3)|B(I4)))
#define TOG1B(R,I)               ((R)^=B(I))
#define TOG2B(R,I1,I2)           (R^=B(I1)^B(I2))
#define TOG3B(R,I1,I2,I3)        (R^=B(I1)^B(I2)^B(I3))

#define RD1B(R,I)   ((R>>I)&(0X01U))                            
#define RD2B(R,I)   ((R>>I)&(0x03U))
#define RD3B(R,I)   ((R>>I)&(0x07U))
#define RD4B(R,I)   ((R>>I)&(0x0FU))
#define RD5B(R,I)   ((R>>I)&(0x1FU))
#define RD6B(R,I)   ((R>>I)&(0x3FU))
#define RD7B(R,I)   ((R>>I)&(0x7FU))
#define RD8B(R,I)   ((R>>I)&(0xFFU))

















































































#define CLR4B4MI(R,I)  (R&(~(0x0F<<I*4))) //clear 4 bits 4 multiple of index
#define SHV4MI(V,I)	   (V<<(I*4))//shift value 4 multiple of index
#define CLR2B2MI(R,I)  (R&(~(0x03<<I*2)))//clear 2 bits 2 multiple of index
#define SHV2MI(V,I)	   (V<<(I*2)) //shift value 2 multiple of index

#define ST2B2MI(R,I,V)   (R|= SHV2MI(V,I)|CLR2B2MI(R,I))
#define ST4B4MI(R,I,V)   (R|= SHV4MI(V,I)|CLR4B4MI(R,I))

#define STV1BI(R,I,V)   (R=(V<<(I))|(R&(~(0x01<<I))))
#define STV2BI(R,I,V)   (R=(V<<(I))|(R&(~(0x03<<I))))
#define STV3BI(R,I,V) (R=(V<<(I))|(R&(~(0x07<<I))))
#define STV4BI(R,I,V)  (R=(V<<(I))|(R&(~(0x0F<<I))))
#define STV5BI(R,I,V)  (R=(V<<(I))|(R&(~(0x1F<<I))))

#define STV6BI(R,I,V)   (R=(V<<(I))|(R&(~(0x3F<<I))))
#define STV7BI(R,I,V) (R=(V<<(I))|(R&(~(0x7F<<I))))
#define STV8BI(R,I,V) (R=(V<<(I))|(R&(~(0xFF<<I))))


/*===========================NIBBLES=====================================*/
#define STLN(R)   (R|= 0x0F) //set lower nibble                 
#define STHN(R)   (R|= 0xF0) //set higher nibble
#define CLRLN(R)  (R & =  (~ (0x0F)))//clear lower nibble                
#define CLRHN(R)  (R & =  (~ (0xF0))) //clear higher nibble
#define RDLN(R)   (R & 0x0F)//read lower nibble
#define RDHN(R)   ((R&0xF0)>>4)//read higher nibble

#define STVHN(R,V)  (R=(R&0x0F)|(V>>4)) //PUT value in the higher nibble
#define STVLN(R,V)  (R=(R&0xF0)|(V&0x0F))

#define STHNVIHNR(R,V)      (R=(R&0x0F)|(V&0XF0)) //copy the higher nipple of the value to the higher nipple of register 
#define STLNVIHNR(R,V)      (R=(R&0x0F)|(V<<4))//copy the lower nipple of the value to the higher nipple of register 

#endif
