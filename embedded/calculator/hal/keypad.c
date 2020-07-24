#include "keypad.h"
const int8_t keypad[4][4]={
	{1,2,3,'A'},
	{4,5,6,'B'},
	{7,8,9,'C'},
	{'*',0,'#','D'}
};
#define KEYPAD_COLS_WITH_INEERNAL_PULLDOWN
#ifdef KEYPAD_COLS_WITH_INEERNAL_PULLDOWN

void KEYPAD_init(void){
	GPIO_PinInit(KEYPAD_COL_PORT,COL0,INPULDN);
	GPIO_PinInit(KEYPAD_COL_PORT,COL1,INPULDN);
	GPIO_PinInit(KEYPAD_COL_PORT,COL2,INPULDN);
	GPIO_PinInit(KEYPAD_COL_PORT,COL3,INPULDN);
	
	GPIO_PinInit(KEYPAD_ROW_PORT,ROW0,OUTPUT);
	GPIO_PinInit(KEYPAD_ROW_PORT,ROW1,OUTPUT);
	GPIO_PinInit(KEYPAD_ROW_PORT,ROW2,OUTPUT);
	GPIO_PinInit(KEYPAD_ROW_PORT,ROW3,OUTPUT);
}
int8_t KEYPAD_Get_Key(void){
	int8_t col,row,key;
	while(1){
		for(row=0;row<NROW;row++){
			//GPIOE->DATA = (1<<(row+ROW0)); or
			//SET_VALUE_IN_FOUR_BITS(GPIOE->DATA,ROW0,(1<<row)); or
			GPIO_NibblePinsOut(KEYPAD_ROW_PORT,ROW0,(1<<row));
			for(col=0;col<NCOL;col++){
			//if(READBIT(GPIOC->DATA,(COL0+col))==1){
				if(GPIO_PinRead(KEYPAD_COL_PORT,COL0+col)==1){
					key= keypad[row][col];
					//_delay_ms_(500); or
					while(GPIO_PinRead(KEYPAD_COL_PORT,COL0+col)==1);
					return key;
				}
			}
		}
	}
}
#endif
#ifdef KEYPAD_ROWS_WITH_INEERNAL_PULLDOWN
void KEYPAD_init(void){
	GPIO_PinInit(KEYPAD_ROW_PORT,ROW0,INPULDN);
	GPIO_PinInit(KEYPAD_ROW_PORT,ROW1,INPULDN);
	GPIO_PinInit(KEYPAD_ROW_PORT,ROW2,INPULDN);
	GPIO_PinInit(KEYPAD_ROW_PORT,ROW3,INPULDN);
	GPIO_PinInit(KEYPAD_COL_PORT,COL0,OUTPUT);
	GPIO_PinInit(KEYPAD_COL_PORT,COL1,OUTPUT);
	GPIO_PinInit(KEYPAD_COL_PORT,COL2,OUTPUT);
	GPIO_PinInit(KEYPAD_COL_PORT,COL3,OUTPUT);
}
int8_t KEYPAD_Get_Key(void){
	int8_t col,row,key,value;
	while(1){
		for(col=0;col<NCOL;col++){
			//GPIOC->DATA = (1<<(col+COL0)); or
			//SET_VALUE_IN_FOUR_BITS(GPIOC->DATA,COL0,(1<<col)); or
			GPIO_Four_Pins_Digital_Output(KEYPAD_COL_PORT,COL0,(1<<col));
			for(row=0;row<NCOL;row++){
			//	if(READBIT(GPIOE->DATA,(row+ROW0))==1){
				if(GPIO_Pin_Read_Input(KEYPAD_ROW_PORT,row+ROW0)==1){
					key=(row*NCOL)+col+1; 
					value= KEYPAD_Map_Key_To_Value(key);
					//_delay_ms_(500); or
					while(GPIO_Pin_Read_Input(KEYPAD_ROW_PORT,row+ROW0)==1);
					return value;
				}
			}
		}
	}
}
#endif
#ifdef KEYPAD_ROWS_WITH_INEERNAL_PULLUPP
void KEYPAD_init(void){
	GPIO_PinInit(KEYPAD_ROW_PORT,ROW0,INPULUP );
	GPIO_PinInit(KEYPAD_ROW_PORT,ROW1,INPULUP );
	GPIO_PinInit(KEYPAD_ROW_PORT,ROW2,INPULUP );
	GPIO_PinInit(KEYPAD_ROW_PORT,ROW3,INPULUP );
	GPIO_PinInit(KEYPAD_COL_PORT,COL0,OUTPUT);
	GPIO_PinInit(KEYPAD_COL_PORT,COL1,OUTPUT);
	GPIO_PinInit(KEYPAD_COL_PORT,COL2,OUTPUT);
	GPIO_PinInit(KEYPAD_COL_PORT,COL3,OUTPUT);
}
int8_t KEYPAD_Get_Key(void){
	int8_t col,row,key,value;
	while(1){
		for(col=0;col<NCOL;col++){
			//			GPIOC->DATA = ~(1<<(col+COL0)); or
			//SET_VALUE_IN_FOUR_BITS(GPIOC->DATA,COL0,~(1<<col)); or
			GPIO_Four_Pins_Digital_Output(KEYPAD_COL_PORT,COL0,~(1<<col));
			for(row=0;row<NCOL;row++){
			//	if(READBIT(GPIOE->DATA,(row+ROW0))==0){
				if(GPIO_Pin_Read_Input(KEYPAD_ROW_PORT,row+ROW0)==0){
					key=(row*NCOL)+col+1;
					value= KEYPAD_Map_Key_To_Value(key);
					//_delay_ms_(500); or
					while(GPIO_Pin_Read_Input(KEYPAD_ROW_PORT,row+ROW0)==0);
					return value;
				}
			}
		}
	}
}
#endif
int8_t KEYPAD_Map_Key_To_Value(int8_t key){
	switch(key){
		case 1: 
			key= 1;
		break;
		case 2: 
			key= 2;
		break;
		case 3: 
			key= 3;
		break;
		case 4: 
			key='A';
		break;
		case 5: 
			key= 4;
		break;
		case 6: 
			key= 5;
		break;
		case 7: 
			key= 6;
		break;
		case 8: 
			key='B';
		break;
		case 9: 
			key= 7;
		break;
		case 10: 
			key= 8;
		break;
		case 11: 
			key= 9;
		break;
		case 12: 
			key= 'C';
		break;
		case 13: 
			key= '*';
		break;
		case 14: 
			key= 0;
		break;
		case 15: 
			key='#';
		break;
		case 16: 
			key='D';
		break;
		default :
			break;
	} 
	return key;
}
