#include "uart.h"
extern uint32_t sysclock;

static UART_INIT_STATUS isBaudRateValid(uint32_t baudRate)
{
    uint8_t validCheck; //temporary variable
    /* check baud rate set by the user*/
    if ((baudRate == 4800) || (baudRate == 9600) || (baudRate == 14400)
            || (baudRate == 19200) || (baudRate == 28800)
            || (baudRate == 38400))
    {
        validCheck = BAUDRATE_VALID; //the baud rate is valid
    }
    else
    {
        validCheck = BAUDRATE_INVALID; //the baud rate is invalid
    }
    return validCheck; //return the result
}
static UART_INIT_STATUS isCharSizeVaild(uint8_t size)
{
    uint8_t valid_check;
    if (size >= 5 || size <= 8)
    {
        valid_check = CHARSIZE_VALID;
    }
    else
    {
        valid_check = CHARSIZE_INVALID;
    }
    return valid_check;
}

void Uart_Init(uint8_t utn, UART_INIT_TYPE* utConfig)
{
    switch (utn)
    {
    case UT0: //U0RX  PA0 , U0TX PA1
        if (RD1B(SYSCTL->RCGCGPIO, PORTA) == 0)
        { //check if the gpio module clock is enabled
            ST1B(SYSCTL->RCGCGPIO, PORTA); //enable gpio clock
            while (RD1B(SYSCTL->PRGPIO, PORTA) == 0)
            { //wait until the gpio module is ready
            };
        }
        if (RD1B(SYSCTL->RCGCUART, UT0) == 0)
        { //check if the uartn module clock is enabled
            ST1B(SYSCTL->RCGCUART, UT0); //enable uart clock
            while (RD1B(SYSCTL->PRUART, UT0) == 0)
            { //wait until the uartN module is ready
            };
        }
        switch (utConfig->TYPE)
        //TX or RX or BOTH
        {
        case TX:
            /* gpio pin configuration   */
            ST1B(GPIOA->AFSEL, PA1); //change pin function
            CLR1B(GPIOA->AMSEL, PA1); //disable analog functionality
            ST4B4MI(GPIOA->PCTL, PA1, 1); //change pin mode
            ST1B(GPIOA->DEN, PA1); //enable digital functionality
            /* UART pin configuration   */
            CLR1B(UART0->CTL, UARTEN); //disable uartn module
            if (isBaudRateValid(utConfig->BAUD_RATE) == BAUDRATE_VALID)
            { //is valid baud rate
                STV(UART0->IBRD, BAUDINT(sysclock,utConfig->BAUD_RATE)); //put the integer part of baud rate computation into int baud register
                STV6BI(UART0->FBRD, BIT0,
                       BAUDFLOAT(sysclock,utConfig->BAUD_RATE)); ////put the float part of baud rate computation into float baud register
            }
            else //by default it is 9600bps
            {
                STV(UART0->IBRD, BAUDINT(sysclock,9600)); //put the integer part of baud rate computation into int baud register
                STV6BI(UART0->FBRD, BIT0, BAUDFLOAT(sysclock,9600)); ////put the float part of baud rate computation into float baud register
            }
            if (isCharSizeVaild(utConfig->CHAR_LEN) == CHARSIZE_VALID)
            {
                STV2BI(UART0->LCRH, WLEN, (utConfig->CHAR_LEN) - 5); //set character size
            }
            else //default character size is 7
            {
                STV2BI(UART0->LCRH, WLEN, 7 - 5); //set character size
            }
            if (utConfig->NSTOP_BIT == 2) //two stop bits
            {
                ST1B(UART0->LCRH, STP2); //two stop bits
            }
            else
            {
                CLR1B(UART0->LCRH, STP2); //one stop bit
            }
            CLR1B(UART0->LCRH, FEN); //disable fifo queue functionality
            STV4BI(UART0->CC, CS, 0); //select system clock source
            CLR1B(UART0->CTL, HSE); //select 16BAUD,sampling period
            ST1B(UART0->CTL, TXE); //enable transmit functionality
            ST1B(UART0->CTL, UARTEN); //uart enable
            break;

        case RX:
            /* gpio pin configuration   */
            ST1B(GPIOA->AFSEL, PA0); //change pin function
            CLR1B(GPIOA->AMSEL, PA0); //disable analog functionality
            ST4B4MI(GPIOA->PCTL, PA0, 1); //change pin mode
            ST1B(GPIOA->DEN, PA0); //enable digital functionality
            /* UART pin configuration   */
            CLR1B(UART0->CTL, UARTEN); //disable uartn module
            if (isBaudRateValid(utConfig->BAUD_RATE) == BAUDRATE_VALID)
            { //is valid baud rate
                STV(UART0->IBRD, BAUDINT(sysclock,utConfig->BAUD_RATE)); //put the integer part of baud rate computation into int baud register
                STV6BI(UART0->FBRD, BIT0,
                       BAUDFLOAT(sysclock,utConfig->BAUD_RATE)); ////put the float part of baud rate computation into float baud register
            }
            else //by default it is 9600bps
            {
                STV(UART0->IBRD, BAUDINT(sysclock,9600)); //put the integer part of baud rate computation into int baud register
                STV6BI(UART0->FBRD, BIT0, BAUDFLOAT(sysclock,9600)); ////put the float part of baud rate computation into float baud register
            }
            if (isCharSizeVaild(utConfig->CHAR_LEN) == CHARSIZE_VALID)
            {
                STV2BI(UART0->LCRH, WLEN, (utConfig->CHAR_LEN) - 5); //set character size
            }
            else //default character size is 7
            {
                STV2BI(UART0->LCRH, WLEN, 7 - 5); //set character size
            }
            if (utConfig->NSTOP_BIT == 2) //two stop bits
            {
                ST1B(UART0->LCRH, STP2); //two stop bits
            }
            else
            {
                CLR1B(UART0->LCRH, STP2); //one stop bit
            }
            CLR1B(UART0->LCRH, FEN); //disable fifo queue functionality
            STV4BI(UART0->CC, CS, 0); //select system clock source
            CLR1B(UART0->CTL, HSE); //select 16BAUD,sampling period
            ST1B(UART0->CTL, RXE); //enable receive functionality
            ST1B(UART0->CTL, UARTEN); //uart enable
            break;
        case BOTH:
            /* gpio pin configuration   */
            ST2B(GPIOA->AFSEL, PA0, PA1); //change pin function
            CLR2B(GPIOA->AMSEL, PA0, PA1); //disable analog functionality
            ST4B4MI(GPIOA->PCTL, PA0, 1); //change pin mode
            ST4B4MI(GPIOA->PCTL, PA1, 1); //change pin mode
            ST2B(GPIOA->DEN, PA0, PA1); //enable digital functionality
            /* UART pin configuration   */
            CLR1B(UART0->CTL, UARTEN); //disable uartn module
            if (isBaudRateValid(utConfig->BAUD_RATE) == BAUDRATE_VALID)
            { //is valid baud rate
                STV(UART0->IBRD, BAUDINT(sysclock,utConfig->BAUD_RATE)); //put the integer part of baud rate computation into int baud register
                STV6BI(UART0->FBRD, BIT0,
                       BAUDFLOAT(sysclock,utConfig->BAUD_RATE)); ////put the float part of baud rate computation into float baud register
            }
            else //by default it is 9600bps
            {
                STV(UART0->IBRD, BAUDINT(sysclock,9600)); //put the integer part of baud rate computation into int baud register
                STV6BI(UART0->FBRD, BIT0, BAUDFLOAT(sysclock,9600)); ////put the float part of baud rate computation into float baud register
            }
            if (isCharSizeVaild(utConfig->CHAR_LEN) == CHARSIZE_VALID)
            {
                STV2BI(UART0->LCRH, WLEN, (utConfig->CHAR_LEN) - 5); //set character size
            }
            else //default character size is 7
            {
                STV2BI(UART0->LCRH, WLEN, 7 - 5); //set character size
            }
            if (utConfig->NSTOP_BIT == 2) //two stop bits
            {
                ST1B(UART0->LCRH, STP2); //two stop bits
            }
            else
            {
                CLR1B(UART0->LCRH, STP2); //one stop bit
            }
            CLR1B(UART0->LCRH, FEN); //disable fifo queue functionality
            STV4BI(UART0->CC, CS, 0); //select system clock source
            CLR1B(UART0->CTL, HSE); //select 16BAUD,sampling period
            ST2B(UART0->CTL, RXE, TXE); //enable transmit & receive functionality
            ST1B(UART0->CTL, UARTEN); //uart enable
            break;
        }
        break;
    case UT1:
        // U1RX  PB0 , U1TX  PB1
        if (RD1B(SYSCTL->RCGCGPIO, PORTB) == 0)
        { //check if the gpio module clock is enabled
            ST1B(SYSCTL->RCGCGPIO, PORTB); //enable gpio clock
            while (RD1B(SYSCTL->PRGPIO, PORTB) == 0)
            { //wait until the gpio module is ready
            };
        }
        if (RD1B(SYSCTL->RCGCUART, UT1) == 0)
        { //check if the uartn module clock is enabled
            ST1B(SYSCTL->RCGCUART, UT1); //enable uart clock
            while (RD1B(SYSCTL->PRUART, UT1) == 0)
            { //wait until the uartN module is ready
            };
        }
        switch (utConfig->TYPE)
        //TX or RX or BOTH
        {
        case TX:
            /* gpio pin configuration   */
            ST1B(GPIOB->AFSEL, PB1); //change pin function
            CLR1B(GPIOB->AMSEL, PB1); //disable analog functionality
            ST4B4MI(GPIOB->PCTL, PB1, 1); //change pin mode
            ST1B(GPIOB->DEN, PB1); //enable digital functionality
            /* UART pin configuration   */
            CLR1B(UART1->CTL, UARTEN); //disable uartn module
            if (isBaudRateValid(utConfig->BAUD_RATE) == BAUDRATE_VALID)
            { //is valid baud rate
                STV(UART1->IBRD, BAUDINT(sysclock,utConfig->BAUD_RATE)); //put the integer part of baud rate computation into int baud register
                STV6BI(UART1->FBRD, BIT0,
                       BAUDFLOAT(sysclock,utConfig->BAUD_RATE)); ////put the float part of baud rate computation into float baud register
            }
            else //by default it is 9600bps
            {
                STV(UART1->IBRD, BAUDINT(sysclock,9600)); //put the integer part of baud rate computation into int baud register
                STV6BI(UART1->FBRD, BIT0, BAUDFLOAT(sysclock,9600)); ////put the float part of baud rate computation into float baud register
            }
            if (isCharSizeVaild(utConfig->CHAR_LEN) == CHARSIZE_VALID)
            {
                STV2BI(UART1->LCRH, WLEN, (utConfig->CHAR_LEN) - 5); //set character size
            }
            else //default character size is 7
            {
                STV2BI(UART1->LCRH, WLEN, 7 - 5); //set character size
            }
            if (utConfig->NSTOP_BIT == 2) //two stop bits
            {
                ST1B(UART1->LCRH, STP2); //two stop bits
            }
            else
            {
                CLR1B(UART1->LCRH, STP2); //one stop bit
            }
            CLR1B(UART1->LCRH, FEN); //disable fifo queue functionality
            STV4BI(UART1->CC, CS, 0); //select system clock source
            CLR1B(UART1->CTL, HSE); //select 16BAUD,sampling period
            ST1B(UART1->CTL, TXE); //enable transmit functionality
            ST1B(UART1->CTL, UARTEN); //uart enable
            break;

        case RX:
            /* gpio pin configuration   */
            ST1B(GPIOB->AFSEL, PB0); //change pin function
            CLR1B(GPIOB->AMSEL, PB0); //disable analog functionality
            ST4B4MI(GPIOB->PCTL, PB0, 1); //change pin mode
            ST1B(GPIOB->DEN, PB0); //enable digital functionality
            /* UART pin configuration   */
            CLR1B(UART1->CTL, UARTEN); //disable uartn module
            if (isBaudRateValid(utConfig->BAUD_RATE) == BAUDRATE_VALID)
            { //is valid baud rate
                STV(UART1->IBRD, BAUDINT(sysclock,utConfig->BAUD_RATE)); //put the integer part of baud rate computation into int baud register
                STV6BI(UART1->FBRD, BIT0,
                       BAUDFLOAT(sysclock,utConfig->BAUD_RATE)); ////put the float part of baud rate computation into float baud register
            }
            else //by default it is 9600bps
            {
                STV(UART1->IBRD, BAUDINT(sysclock,9600)); //put the integer part of baud rate computation into int baud register
                STV6BI(UART1->FBRD, BIT0, BAUDFLOAT(sysclock,9600)); ////put the float part of baud rate computation into float baud register
            }
            if (isCharSizeVaild(utConfig->CHAR_LEN) == CHARSIZE_VALID)
            {
                STV2BI(UART1->LCRH, WLEN, (utConfig->CHAR_LEN) - 5); //set character size
            }
            else //default character size is 7
            {
                STV2BI(UART1->LCRH, WLEN, 7 - 5); //set character size
            }
            if (utConfig->NSTOP_BIT == 2) //two stop bits
            {
                ST1B(UART1->LCRH, STP2); //two stop bits
            }
            else
            {
                CLR1B(UART1->LCRH, STP2); //one stop bit
            }
            CLR1B(UART1->LCRH, FEN); //disable fifo queue functionality
            STV4BI(UART1->CC, CS, 0); //select system clock source
            CLR1B(UART1->CTL, HSE); //select 16BAUD,sampling period
            ST1B(UART1->CTL, RXE); //enable receive functionality
            ST1B(UART1->CTL, UARTEN); //uart enable
            break;
        case BOTH:
            /* gpio pin configuration   */
            ST2B(GPIOB->AFSEL, PB0, PB1); //change pin function
            CLR2B(GPIOB->AMSEL, PB0, PB1); //disable analog functionality
            ST4B4MI(GPIOB->PCTL, PB0, 1); //change pin mode
            ST4B4MI(GPIOB->PCTL, PB1, 1); //change pin mode
            ST2B(GPIOB->DEN, PB0, PB1); //enable digital functionality
            /* UART pin configuration   */
            CLR1B(UART1->CTL, UARTEN); //disable uartn module
            if (isBaudRateValid(utConfig->BAUD_RATE) == BAUDRATE_VALID)
            { //is valid baud rate
                STV(UART1->IBRD, BAUDINT(sysclock,utConfig->BAUD_RATE)); //put the integer part of baud rate computation into int baud register
                STV6BI(UART1->FBRD, BIT0,
                       BAUDFLOAT(sysclock,utConfig->BAUD_RATE)); ////put the float part of baud rate computation into float baud register
            }
            else //by default it is 9600bps
            {
                STV(UART1->IBRD, BAUDINT(sysclock,9600)); //put the integer part of baud rate computation into int baud register
                STV6BI(UART1->FBRD, BIT0, BAUDFLOAT(sysclock,9600)); ////put the float part of baud rate computation into float baud register
            }
            if (isCharSizeVaild(utConfig->CHAR_LEN) == CHARSIZE_VALID)
            {
                STV2BI(UART1->LCRH, WLEN, (utConfig->CHAR_LEN) - 5); //set character size
            }
            else //default character size is 7
            {
                STV2BI(UART1->LCRH, WLEN, 7 - 5); //set character size
            }
            if (utConfig->NSTOP_BIT == 2) //two stop bits
            {
                ST1B(UART1->LCRH, STP2); //two stop bits
            }
            else
            {
                CLR1B(UART1->LCRH, STP2); //one stop bit
            }
            CLR1B(UART1->LCRH, FEN); //disable fifo queue functionality
            STV4BI(UART1->CC, CS, 0); //select system clock source
            CLR1B(UART1->CTL, HSE); //select 16BAUD,sampling period
            ST2B(UART1->CTL, RXE, TXE); //enable transmit & receive functionality
            ST1B(UART1->CTL, UARTEN); //uart enable

        }
        break;
    case UT2:
        //PORTD PD6:RX, PD7:TX
        if (RD1B(SYSCTL->RCGCGPIO, PORTD) == 0)
        { //check if the gpio module clock is enabled
            ST1B(SYSCTL->RCGCGPIO, PORTD); //enable gpio clock
            while (RD1B(SYSCTL->PRGPIO, PORTD) == 0)
            { //wait until the gpio module is ready
            };
        }
        if (RD1B(SYSCTL->RCGCUART, UT2) == 0)
        { //check if the uartn module clock is enabled
            ST1B(SYSCTL->RCGCUART, UT2); //enable uart clock
            while (RD1B(SYSCTL->PRUART, UT2) == 0)
            { //wait until the uartN module is ready
            };
        }
        switch (utConfig->TYPE)
        //TX or RX or BOTH
        {
        case TX:
            /* gpio pin configuration   */
            GPIOD->LOCK = UNLOCK; //unlock GPIOD to make a certain pin to work as gpio
            ST1B(GPIOD->CR, PD7); //comit the change
            ST1B(GPIOD->AFSEL, PD7); //change pin function
            CLR1B(GPIOD->AMSEL, PD7); //disable analog functionality
            ST4B4MI(GPIOD->PCTL, PD7, 1); //change pin mode
            ST1B(GPIOD->DEN, PD7); //enable digital functionality
            /* UART pin configuration   */
            CLR1B(UART2->CTL, UARTEN); //disable uartn module
            if (isBaudRateValid(utConfig->BAUD_RATE) == BAUDRATE_VALID)
            { //is valid baud rate
                STV(UART2->IBRD, BAUDINT(sysclock,utConfig->BAUD_RATE)); //put the integer part of baud rate computation into int baud register
                STV6BI(UART2->FBRD, BIT0,
                       BAUDFLOAT(sysclock,utConfig->BAUD_RATE)); ////put the float part of baud rate computation into float baud register
            }
            else //by default it is 9600bps
            {
                STV(UART2->IBRD, BAUDINT(sysclock,9600)); //put the integer part of baud rate computation into int baud register
                STV6BI(UART2->FBRD, BIT0, BAUDFLOAT(sysclock,9600)); ////put the float part of baud rate computation into float baud register
            }
            if (isCharSizeVaild(utConfig->CHAR_LEN) == CHARSIZE_VALID)
            {
                STV2BI(UART2->LCRH, WLEN, (utConfig->CHAR_LEN) - 5); //set character size
            }
            else //default character size is 7
            {
                STV2BI(UART2->LCRH, WLEN, 7 - 5); //set character size
            }
            if (utConfig->NSTOP_BIT == 2) //two stop bits
            {
                ST1B(UART2->LCRH, STP2); //two stop bits
            }
            else
            {
                CLR1B(UART2->LCRH, STP2); //one stop bit
            }
            CLR1B(UART2->LCRH, FEN); //disable fifo queue functionality
            STV4BI(UART2->CC, CS, 0); //select system clock source
            CLR1B(UART2->CTL, HSE); //select 16BAUD,sampling period
            ST1B(UART2->CTL, TXE); //enable transmit functionality
            ST1B(UART2->CTL, UARTEN); //uart enable
            break;

        case RX:
            /* gpio pin configuration   */
            ST1B(GPIOD->AFSEL, PD6); //change pin function
            CLR1B(GPIOD->AMSEL, PD6); //disable analog functionality
            ST4B4MI(GPIOD->PCTL, PD6, 1); //change pin mode
            ST1B(GPIOD->DEN, PD6); //enable digital functionality
            /* UART pin configuration   */
            CLR1B(UART2->CTL, UARTEN); //disable uartn module
            if (isBaudRateValid(utConfig->BAUD_RATE) == BAUDRATE_VALID)
            { //is valid baud rate
                STV(UART2->IBRD, BAUDINT(sysclock,utConfig->BAUD_RATE)); //put the integer part of baud rate computation into int baud register
                STV6BI(UART2->FBRD, BIT0,
                       BAUDFLOAT(sysclock,utConfig->BAUD_RATE)); ////put the float part of baud rate computation into float baud register
            }
            else //by default it is 9600bps
            {
                STV(UART2->IBRD, BAUDINT(sysclock,9600)); //put the integer part of baud rate computation into int baud register
                STV6BI(UART2->FBRD, BIT0, BAUDFLOAT(sysclock,9600)); ////put the float part of baud rate computation into float baud register
            }
            if (isCharSizeVaild(utConfig->CHAR_LEN) == CHARSIZE_VALID)
            {
                STV2BI(UART2->LCRH, WLEN, (utConfig->CHAR_LEN) - 5); //set character size
            }
            else //default character size is 7
            {
                STV2BI(UART2->LCRH, WLEN, 7 - 5); //set character size
            }
            if (utConfig->NSTOP_BIT == 2) //two stop bits
            {
                ST1B(UART2->LCRH, STP2); //two stop bits
            }
            else
            {
                CLR1B(UART2->LCRH, STP2); //one stop bit
            }
            CLR1B(UART2->LCRH, FEN); //disable fifo queue functionality
            STV4BI(UART2->CC, CS, 0); //select system clock source
            CLR1B(UART2->CTL, HSE); //select 16BAUD,sampling period
            ST1B(UART2->CTL, RXE); //enable receive functionality
            ST1B(UART2->CTL, UARTEN); //uart enable
            break;
        case BOTH:
            /* gpio pin configuration   */
            GPIOD->LOCK = UNLOCK; //unlock GPIOD to make a certain pin to work as gpio
            ST1B(GPIOD->CR, PD7); //comit the change
            ST2B(GPIOD->AFSEL, PD6, PD7); //change pin function
            CLR2B(GPIOD->AMSEL, PD6, PD7); //disable analog functionality
            ST4B4MI(GPIOD->PCTL, PD6, 1); //change pin mode
            ST4B4MI(GPIOD->PCTL, PD7, 1); //change pin mode
            ST2B(GPIOD->DEN, PD6, PD7); //enable digital functionality
            /* UART pin configuration   */
            CLR1B(UART2->CTL, UARTEN); //disable uartn module
            if (isBaudRateValid(utConfig->BAUD_RATE) == BAUDRATE_VALID)
            { //is valid baud rate
                STV(UART2->IBRD, BAUDINT(sysclock,utConfig->BAUD_RATE)); //put the integer part of baud rate computation into int baud register
                STV6BI(UART2->FBRD, BIT0,
                       BAUDFLOAT(sysclock,utConfig->BAUD_RATE)); ////put the float part of baud rate computation into float baud register
            }
            else //by default it is 9600bps
            {
                STV(UART2->IBRD, BAUDINT(sysclock,9600)); //put the integer part of baud rate computation into int baud register
                STV6BI(UART2->FBRD, BIT0, BAUDFLOAT(sysclock,9600)); ////put the float part of baud rate computation into float baud register
            }
            if (isCharSizeVaild(utConfig->CHAR_LEN) == CHARSIZE_VALID)
            {
                STV2BI(UART2->LCRH, WLEN, (utConfig->CHAR_LEN) - 5); //set character size
            }
            else //default character size is 7
            {
                STV2BI(UART2->LCRH, WLEN, 7 - 5); //set character size
            }
            if (utConfig->NSTOP_BIT == 2) //two stop bits
            {
                ST1B(UART2->LCRH, STP2); //two stop bits
            }
            else
            {
                CLR1B(UART2->LCRH, STP2); //one stop bit
            }
            CLR1B(UART2->LCRH, FEN); //disable fifo queue functionality
            STV4BI(UART2->CC, CS, 0); //select system clock source
            CLR1B(UART2->CTL, HSE); //select 16BAUD,sampling period
            ST2B(UART2->CTL, RXE, TXE); //enable transmit & receive functionality
            ST1B(UART2->CTL, UARTEN); //uart enable
        }
        break;
    case UT3: //PORTC, PC6:RX,PC7:TX
        if (RD1B(SYSCTL->RCGCGPIO, PORTC) == 0)
        { //check if the gpio module clock is enabled
            ST1B(SYSCTL->RCGCGPIO, PORTC); //enable gpio clock
            while (RD1B(SYSCTL->PRGPIO, PORTC) == 0)
            { //wait until the gpio module is ready
            };
        }
        if (RD1B(SYSCTL->RCGCUART, UT3) == 0)
        { //check if the uartn module clock is enabled
            ST1B(SYSCTL->RCGCUART, UT3); //enable uart clock
            while (RD1B(SYSCTL->PRUART, UT3) == 0)
            { //wait until the uartN module is ready
            };
        }
        switch (utConfig->TYPE)
        //TX or RX or BOTH
        {
        case TX:
            /* gpio pin configuration   */
            ST1B(GPIOC->AFSEL, PC7); //change pin function
            CLR1B(GPIOC->AMSEL, PC7); //disable analog functionality
            ST4B4MI(GPIOC->PCTL, PC7, 1); //change pin mode
            ST1B(GPIOC->DEN, PC7); //enable digital functionality
            /* UART pin configuration   */
            CLR1B(UART3->CTL, UARTEN); //disable uartn module
            if (isBaudRateValid(utConfig->BAUD_RATE) == BAUDRATE_VALID)
            { //is valid baud rate
                STV(UART3->IBRD, BAUDINT(sysclock,utConfig->BAUD_RATE)); //put the integer part of baud rate computation into int baud register
                STV6BI(UART3->FBRD, BIT0,
                       BAUDFLOAT(sysclock,utConfig->BAUD_RATE)); ////put the float part of baud rate computation into float baud register
            }
            else //by default it is 9600bps
            {
                STV(UART3->IBRD, BAUDINT(sysclock,9600)); //put the integer part of baud rate computation into int baud register
                STV6BI(UART3->FBRD, BIT0, BAUDFLOAT(sysclock,9600)); ////put the float part of baud rate computation into float baud register
            }
            if (isCharSizeVaild(utConfig->CHAR_LEN) == CHARSIZE_VALID)
            {
                STV2BI(UART3->LCRH, WLEN, (utConfig->CHAR_LEN) - 5); //set character size
            }
            else //default character size is 7
            {
                STV2BI(UART3->LCRH, WLEN, 7 - 5); //set character size
            }
            if (utConfig->NSTOP_BIT == 2) //two stop bits
            {
                ST1B(UART3->LCRH, STP2); //two stop bits
            }
            else
            {
                CLR1B(UART3->LCRH, STP2); //one stop bit
            }
            CLR1B(UART3->LCRH, FEN); //disable fifo queue functionality
            STV4BI(UART3->CC, CS, 0); //select system clock source
            CLR1B(UART3->CTL, HSE); //select 16BAUD,sampling period
            ST1B(UART3->CTL, TXE); //enable transmit functionality
            ST1B(UART3->CTL, UARTEN); //uart enable
            break;

        case RX:
            /* gpio pin configuration   */
            ST1B(GPIOC->AFSEL, PC6); //change pin function
            CLR1B(GPIOC->AMSEL, PC6); //disable analog functionality
            ST4B4MI(GPIOC->PCTL, PC6, 1); //change pin mode
            ST1B(GPIOC->DEN, PC6); //enable digital functionality
            /* UART pin configuration   */
            CLR1B(UART3->CTL, UARTEN); //disable uartn module
            if (isBaudRateValid(utConfig->BAUD_RATE) == BAUDRATE_VALID)
            { //is valid baud rate
                STV(UART3->IBRD, BAUDINT(sysclock,utConfig->BAUD_RATE)); //put the integer part of baud rate computation into int baud register
                STV6BI(UART3->FBRD, BIT0,
                       BAUDFLOAT(sysclock,utConfig->BAUD_RATE)); ////put the float part of baud rate computation into float baud register
            }
            else //by default it is 9600bps
            {
                STV(UART3->IBRD, BAUDINT(sysclock,9600)); //put the integer part of baud rate computation into int baud register
                STV6BI(UART3->FBRD, BIT0, BAUDFLOAT(sysclock,9600)); ////put the float part of baud rate computation into float baud register
            }
            if (isCharSizeVaild(utConfig->CHAR_LEN) == CHARSIZE_VALID)
            {
                STV2BI(UART3->LCRH, WLEN, (utConfig->CHAR_LEN) - 5); //set character size
            }
            else //default character size is 7
            {
                STV2BI(UART3->LCRH, WLEN, 7 - 5); //set character size
            }
            if (utConfig->NSTOP_BIT == 2) //two stop bits
            {
                ST1B(UART3->LCRH, STP2); //two stop bits
            }
            else
            {
                CLR1B(UART3->LCRH, STP2); //one stop bit
            }
            CLR1B(UART3->LCRH, FEN); //disable fifo queue functionality
            STV4BI(UART3->CC, CS, 0); //select system clock source
            CLR1B(UART3->CTL, HSE); //select 16BAUD,sampling period
            ST1B(UART3->CTL, RXE); //enable receive functionality
            ST1B(UART3->CTL, UARTEN); //uart enable
            break;
        case BOTH:
            /* gpio pin configuration   */
            ST2B(GPIOC->AFSEL, PC6, PC7); //change pin function
            CLR2B(GPIOC->AMSEL, PC6, PC7); //disable analog functionality
            ST4B4MI(GPIOC->PCTL, PC6, 1); //change pin mode
            ST4B4MI(GPIOC->PCTL, PC7, 1); //change pin mode
            ST2B(GPIOC->DEN, PC6, PC7); //enable digital functionality
            /* UART pin configuration   */
            CLR1B(UART3->CTL, UARTEN); //disable uartn module
            if (isBaudRateValid(utConfig->BAUD_RATE) == BAUDRATE_VALID)
            { //is valid baud rate
                STV(UART3->IBRD, BAUDINT(sysclock,utConfig->BAUD_RATE)); //put the integer part of baud rate computation into int baud register
                STV6BI(UART3->FBRD, BIT0,
                       BAUDFLOAT(sysclock,utConfig->BAUD_RATE)); ////put the float part of baud rate computation into float baud register
            }
            else //by default it is 9600bps
            {
                STV(UART3->IBRD, BAUDINT(sysclock,9600)); //put the integer part of baud rate computation into int baud register
                STV6BI(UART3->FBRD, BIT0, BAUDFLOAT(sysclock,9600)); ////put the float part of baud rate computation into float baud register
            }
            if (isCharSizeVaild(utConfig->CHAR_LEN) == CHARSIZE_VALID)
            {
                STV2BI(UART3->LCRH, WLEN, (utConfig->CHAR_LEN) - 5); //set character size
            }
            else //default character size is 7
            {
                STV2BI(UART3->LCRH, WLEN, 7 - 5); //set character size
            }
            if (utConfig->NSTOP_BIT == 2) //two stop bits
            {
                ST1B(UART3->LCRH, STP2); //two stop bits
            }
            else
            {
                CLR1B(UART3->LCRH, STP2); //one stop bit
            }
            CLR1B(UART3->LCRH, FEN); //disable fifo queue functionality
            STV4BI(UART3->CC, CS, 0); //select system clock source
            CLR1B(UART3->CTL, HSE); //select 16BAUD,sampling period
            ST2B(UART3->CTL, RXE, TXE); //enable transmit & receive functionality
            ST1B(UART3->CTL, UARTEN); //uart enable

        }
        break;
    case UT4: //PORTC,PC4:RX,PC5:TX
        if (RD1B(SYSCTL->RCGCGPIO, PORTC) == 0)
        { //check if the gpio module clock is enabled
            ST1B(SYSCTL->RCGCGPIO, PORTC); //enable gpio clock
            while (RD1B(SYSCTL->PRGPIO, PORTC) == 0)
            { //wait until the gpio module is ready
            };
        }
        if (RD1B(SYSCTL->RCGCUART, UT4) == 0)
        { //check if the uartn module clock is enabled
            ST1B(SYSCTL->RCGCUART, UT4); //enable uart clock
            while (RD1B(SYSCTL->PRUART, UT4) == 0)
            { //wait until the uartN module is ready
            };
        }
        switch (utConfig->TYPE)
        //TX or RX or BOTH
        {
        case TX:
            /* gpio pin configuration   */
            ST1B(GPIOC->AFSEL, PC5); //change pin function
            CLR1B(GPIOC->AMSEL, PC5); //disable analog functionality
            ST4B4MI(GPIOC->PCTL, PC5, 1); //change pin mode
            ST1B(GPIOC->DEN, PC5); //enable digital functionality
            /* UART pin configuration   */
            CLR1B(UART4->CTL, UARTEN); //disable uartn module
            if (isBaudRateValid(utConfig->BAUD_RATE) == BAUDRATE_VALID)
            { //is valid baud rate
                STV(UART4->IBRD, BAUDINT(sysclock,utConfig->BAUD_RATE)); //put the integer part of baud rate computation into int baud register
                STV6BI(UART4->FBRD, BIT0,
                       BAUDFLOAT(sysclock,utConfig->BAUD_RATE)); ////put the float part of baud rate computation into float baud register
            }
            else //by default it is 9600bps
            {
                STV(UART4->IBRD, BAUDINT(sysclock,9600)); //put the integer part of baud rate computation into int baud register
                STV6BI(UART4->FBRD, BIT0, BAUDFLOAT(sysclock,9600)); ////put the float part of baud rate computation into float baud register
            }
            if (isCharSizeVaild(utConfig->CHAR_LEN) == CHARSIZE_VALID)
            {
                STV2BI(UART4->LCRH, WLEN, (utConfig->CHAR_LEN) - 5); //set character size
            }
            else //default character size is 7
            {
                STV2BI(UART4->LCRH, WLEN, 7 - 5); //set character size
            }
            if (utConfig->NSTOP_BIT == 2) //two stop bits
            {
                ST1B(UART4->LCRH, STP2); //two stop bits
            }
            else
            {
                CLR1B(UART4->LCRH, STP2); //one stop bit
            }
            CLR1B(UART4->LCRH, FEN); //disable fifo queue functionality
            STV4BI(UART4->CC, CS, 0); //select system clock source
            CLR1B(UART4->CTL, HSE); //select 16BAUD,sampling period
            ST1B(UART4->CTL, TXE); //enable transmit functionality
            ST1B(UART4->CTL, UARTEN); //uart enable
            break;

        case RX:
            /* gpio pin configuration   */
            ST1B(GPIOC->AFSEL, PC4); //change pin function
            CLR1B(GPIOC->AMSEL, PC4); //disable analog functionality
            ST4B4MI(GPIOC->PCTL, PC4, 1); //change pin mode
            ST1B(GPIOC->DEN, PC4); //enable digital functionality
            /* UART pin configuration   */
            CLR1B(UART4->CTL, UARTEN); //disable uartn module
            if (isBaudRateValid(utConfig->BAUD_RATE) == BAUDRATE_VALID)
            { //is valid baud rate
                STV(UART4->IBRD, BAUDINT(sysclock,utConfig->BAUD_RATE)); //put the integer part of baud rate computation into int baud register
                STV6BI(UART4->FBRD, BIT0,
                       BAUDFLOAT(sysclock,utConfig->BAUD_RATE)); ////put the float part of baud rate computation into float baud register
            }
            else //by default it is 9600bps
            {
                STV(UART4->IBRD, BAUDINT(sysclock,9600)); //put the integer part of baud rate computation into int baud register
                STV6BI(UART4->FBRD, BIT0, BAUDFLOAT(sysclock,9600)); ////put the float part of baud rate computation into float baud register
            }
            if (isCharSizeVaild(utConfig->CHAR_LEN) == CHARSIZE_VALID)
            {
                STV2BI(UART4->LCRH, WLEN, (utConfig->CHAR_LEN) - 5); //set character size
            }
            else //default character size is 7
            {
                STV2BI(UART4->LCRH, WLEN, 7 - 5); //set character size
            }
            if (utConfig->NSTOP_BIT == 2) //two stop bits
            {
                ST1B(UART4->LCRH, STP2); //two stop bits
            }
            else
            {
                CLR1B(UART4->LCRH, STP2); //one stop bit
            }
            CLR1B(UART4->LCRH, FEN); //disable fifo queue functionality
            STV4BI(UART4->CC, CS, 0); //select system clock source
            CLR1B(UART4->CTL, HSE); //select 16BAUD,sampling period
            ST1B(UART4->CTL, RXE); //enable receive functionality
            ST1B(UART4->CTL, UARTEN); //uart enable
            break;
        case BOTH:
            /* gpio pin configuration   */
            ST2B(GPIOC->AFSEL, PC4, PC5); //change pin function
            CLR2B(GPIOC->AMSEL, PC4, PC5); //disable analog functionality
            ST4B4MI(GPIOC->PCTL, PC4, 1); //change pin mode
            ST4B4MI(GPIOC->PCTL, PC5, 1); //change pin mode
            ST2B(GPIOC->DEN, PC4, PC5); //enable digital functionality
            /* UART pin configuration   */
            CLR1B(UART4->CTL, UARTEN); //disable uartn module
            if (isBaudRateValid(utConfig->BAUD_RATE) == BAUDRATE_VALID)
            { //is valid baud rate
                STV(UART4->IBRD, BAUDINT(sysclock,utConfig->BAUD_RATE)); //put the integer part of baud rate computation into int baud register
                STV6BI(UART4->FBRD, BIT0,
                       BAUDFLOAT(sysclock,utConfig->BAUD_RATE)); ////put the float part of baud rate computation into float baud register
            }
            else //by default it is 9600bps
            {
                STV(UART4->IBRD, BAUDINT(sysclock,9600)); //put the integer part of baud rate computation into int baud register
                STV6BI(UART4->FBRD, BIT0, BAUDFLOAT(sysclock,9600)); ////put the float part of baud rate computation into float baud register
            }
            if (isCharSizeVaild(utConfig->CHAR_LEN) == CHARSIZE_VALID)
            {
                STV2BI(UART4->LCRH, WLEN, (utConfig->CHAR_LEN) - 5); //set character size
            }
            else //default character size is 7
            {
                STV2BI(UART4->LCRH, WLEN, 7 - 5); //set character size
            }
            if (utConfig->NSTOP_BIT == 2) //two stop bits
            {
                ST1B(UART4->LCRH, STP2); //two stop bits
            }
            else
            {
                CLR1B(UART4->LCRH, STP2); //one stop bit
            }
            CLR1B(UART4->LCRH, FEN); //disable fifo queue functionality
            STV4BI(UART4->CC, CS, 0); //select system clock source
            CLR1B(UART4->CTL, HSE); //select 16BAUD,sampling period
            ST2B(UART4->CTL, RXE, TXE); //enable transmit & receive functionality
            ST1B(UART4->CTL, UARTEN); //uart enable
        }
        break;
    case UT5: //PORTE,PE4:RX,PE5:TX
        if (RD1B(SYSCTL->RCGCGPIO, PORTE) == 0)
        { //check if the gpio module clock is enabled
            ST1B(SYSCTL->RCGCGPIO, PORTE); //enable gpio clock
            while (RD1B(SYSCTL->PRGPIO, PORTE) == 0)
            { //wait until the gpio module is ready
            };
        }
        if (RD1B(SYSCTL->RCGCUART, UT5) == 0)
        { //check if the uartn module clock is enabled
            ST1B(SYSCTL->RCGCUART, UT5); //enable uart clock
            while (RD1B(SYSCTL->PRUART, UT5) == 0)
            { //wait until the uartN module is ready
            };
        }
        switch (utConfig->TYPE)
        //TX or RX or BOTH
        {
        case TX:
            /* gpio pin configuration   */
            ST1B(GPIOE->AFSEL, PE5); //change pin function
            CLR1B(GPIOE->AMSEL, PE5); //disable analog functionality
            ST4B4MI(GPIOE->PCTL, PE5, 1); //change pin mode
            ST1B(GPIOE->DEN, PE5); //enable digital functionality
            /* UART pin configuration   */
            CLR1B(UART5->CTL, UARTEN); //disable uartn module
            if (isBaudRateValid(utConfig->BAUD_RATE) == BAUDRATE_VALID)
            { //is valid baud rate
                STV(UART5->IBRD, BAUDINT(sysclock,utConfig->BAUD_RATE)); //put the integer part of baud rate computation into int baud register
                STV6BI(UART5->FBRD, BIT0,
                       BAUDFLOAT(sysclock,utConfig->BAUD_RATE)); ////put the float part of baud rate computation into float baud register
            }
            else //by default it is 9600bps
            {
                STV(UART5->IBRD, BAUDINT(sysclock,9600)); //put the integer part of baud rate computation into int baud register
                STV6BI(UART5->FBRD, BIT0, BAUDFLOAT(sysclock,9600)); ////put the float part of baud rate computation into float baud register
            }
            if (isCharSizeVaild(utConfig->CHAR_LEN) == CHARSIZE_VALID)
            {
                STV2BI(UART5->LCRH, WLEN, (utConfig->CHAR_LEN) - 5); //set character size
            }
            else //default character size is 7
            {
                STV2BI(UART5->LCRH, WLEN, 7 - 5); //set character size
            }
            if (utConfig->NSTOP_BIT == 2) //two stop bits
            {
                ST1B(UART5->LCRH, STP2); //two stop bits
            }
            else
            {
                CLR1B(UART5->LCRH, STP2); //one stop bit
            }
            CLR1B(UART5->LCRH, FEN); //disable fifo queue functionality
            STV4BI(UART5->CC, CS, 0); //select system clock source
            CLR1B(UART5->CTL, HSE); //select 16BAUD,sampling period
            ST1B(UART5->CTL, TXE); //enable transmit functionality
            ST1B(UART5->CTL, UARTEN); //uart enable
            break;

        case RX:
            /* gpio pin configuration   */
            ST1B(GPIOE->AFSEL, PE4); //change pin function
            CLR1B(GPIOE->AMSEL, PE4); //disable analog functionality
            ST4B4MI(GPIOE->PCTL, PE4, 1); //change pin mode
            ST1B(GPIOE->DEN, PE4); //enable digital functionality
            /* UART pin configuration   */
            CLR1B(UART5->CTL, UARTEN); //disable uartn module
            if (isBaudRateValid(utConfig->BAUD_RATE) == BAUDRATE_VALID)
            { //is valid baud rate
                STV(UART5->IBRD, BAUDINT(sysclock,utConfig->BAUD_RATE)); //put the integer part of baud rate computation into int baud register
                STV6BI(UART5->FBRD, BIT0,
                       BAUDFLOAT(sysclock,utConfig->BAUD_RATE)); ////put the float part of baud rate computation into float baud register
            }
            else //by default it is 9600bps
            {
                STV(UART5->IBRD, BAUDINT(sysclock,9600)); //put the integer part of baud rate computation into int baud register
                STV6BI(UART5->FBRD, BIT0, BAUDFLOAT(sysclock,9600)); ////put the float part of baud rate computation into float baud register
            }
            if (isCharSizeVaild(utConfig->CHAR_LEN) == CHARSIZE_VALID)
            {
                STV2BI(UART5->LCRH, WLEN, (utConfig->CHAR_LEN) - 5); //set character size
            }
            else //default character size is 7
            {
                STV2BI(UART5->LCRH, WLEN, 7 - 5); //set character size
            }
            if (utConfig->NSTOP_BIT == 2) //two stop bits
            {
                ST1B(UART5->LCRH, STP2); //two stop bits
            }
            else
            {
                CLR1B(UART5->LCRH, STP2); //one stop bit
            }
            CLR1B(UART5->LCRH, FEN); //disable fifo queue functionality
            STV4BI(UART5->CC, CS, 0); //select system clock source
            CLR1B(UART5->CTL, HSE); //select 16BAUD,sampling period
            ST1B(UART5->CTL, RXE); //enable receive functionality
            ST1B(UART5->CTL, UARTEN); //uart enable
            break;
        case BOTH:
            /* gpio pin configuration   */
            ST2B(GPIOE->AFSEL, PE4, PE5); //change pin function
            CLR2B(GPIOE->AMSEL, PE4, PE5); //disable analog functionality
            ST4B4MI(GPIOE->PCTL, PE4, 1); //change pin mode
            ST4B4MI(GPIOE->PCTL, PE5, 1); //change pin mode
            ST2B(GPIOE->DEN, PE4, PE5); //enable digital functionality
            /* UART pin configuration   */
            CLR1B(UART5->CTL, UARTEN); //disable uartn module
            if (isBaudRateValid(utConfig->BAUD_RATE) == BAUDRATE_VALID)
            { //is valid baud rate
                STV(UART5->IBRD, BAUDINT(sysclock,utConfig->BAUD_RATE)); //put the integer part of baud rate computation into int baud register
                STV6BI(UART5->FBRD, BIT0,
                       BAUDFLOAT(sysclock,utConfig->BAUD_RATE)); ////put the float part of baud rate computation into float baud register
            }
            else //by default it is 9600bps
            {
                STV(UART5->IBRD, BAUDINT(sysclock,9600)); //put the integer part of baud rate computation into int baud register
                STV6BI(UART5->FBRD, BIT0, BAUDFLOAT(sysclock,9600)); ////put the float part of baud rate computation into float baud register
            }
            if (isCharSizeVaild(utConfig->CHAR_LEN) == CHARSIZE_VALID)
            {
                STV2BI(UART5->LCRH, WLEN, (utConfig->CHAR_LEN) - 5); //set character size
            }
            else //default character size is 7
            {
                STV2BI(UART5->LCRH, WLEN, 7 - 5); //set character size
            }
            if (utConfig->NSTOP_BIT == 2) //two stop bits
            {
                ST1B(UART5->LCRH, STP2); //two stop bits
            }
            else
            {
                CLR1B(UART5->LCRH, STP2); //one stop bit
            }
            CLR1B(UART5->LCRH, FEN); //disable fifo queue functionality
            STV4BI(UART5->CC, CS, 0); //select system clock source
            CLR1B(UART5->CTL, HSE); //select 16BAUD,sampling period
            ST2B(UART5->CTL, RXE, TXE); //enable transmit & receive functionality
            ST1B(UART5->CTL, UARTEN); //uart enable
        }
        break;
    case UT7: //PORTE,PE0:RX,PE1:TX
        if (RD1B(SYSCTL->RCGCGPIO, PORTE) == 0)
        { //check if the gpio module clock is enabled
            ST1B(SYSCTL->RCGCGPIO, PORTE); //enable gpio clock
            while (RD1B(SYSCTL->PRGPIO, PORTE) == 0)
            { //wait until the gpio module is ready
            };
        }
        if (RD1B(SYSCTL->RCGCUART, UT7) == 0)
        { //check if the uartn module clock is enabled
            ST1B(SYSCTL->RCGCUART, UT7); //enable uart clock
            while (RD1B(SYSCTL->PRUART, UT7) == 0)
            { //wait until the uartN module is ready
            };
        }
        switch (utConfig->TYPE)
        //TX or RX or BOTH
        {
        case TX:
            /* gpio pin configuration   */
            ST1B(GPIOE->AFSEL, PE1); //change pin function
            CLR1B(GPIOE->AMSEL, PE1); //disable analog functionality
            ST4B4MI(GPIOE->PCTL, PE1, 1); //change pin mode
            ST1B(GPIOE->DEN, PE1); //enable digital functionality
            /* UART pin configuration   */
            CLR1B(UART7->CTL, UARTEN); //disable uartn module
            if (isBaudRateValid(utConfig->BAUD_RATE) == BAUDRATE_VALID)
            { //is valid baud rate
                STV(UART7->IBRD, BAUDINT(sysclock,utConfig->BAUD_RATE)); //put the integer part of baud rate computation into int baud register
                STV6BI(UART7->FBRD, BIT0,
                       BAUDFLOAT(sysclock,utConfig->BAUD_RATE)); ////put the float part of baud rate computation into float baud register
            }
            else //by default it is 9600bps
            {
                STV(UART7->IBRD, BAUDINT(sysclock,9600)); //put the integer part of baud rate computation into int baud register
                STV6BI(UART7->FBRD, BIT0, BAUDFLOAT(sysclock,9600)); ////put the float part of baud rate computation into float baud register
            }
            if (isCharSizeVaild(utConfig->CHAR_LEN) == CHARSIZE_VALID)
            {
                STV2BI(UART7->LCRH, WLEN, (utConfig->CHAR_LEN) - 5); //set character size
            }
            else //default character size is 7
            {
                STV2BI(UART7->LCRH, WLEN, 7 - 5); //set character size
            }
            if (utConfig->NSTOP_BIT == 2) //two stop bits
            {
                ST1B(UART7->LCRH, STP2); //two stop bits
            }
            else
            {
                CLR1B(UART7->LCRH, STP2); //one stop bit
            }
            CLR1B(UART7->LCRH, FEN); //disable fifo queue functionality
            STV4BI(UART7->CC, CS, 0); //select system clock source
            CLR1B(UART7->CTL, HSE); //select 16BAUD,sampling period
            ST1B(UART7->CTL, TXE); //enable transmit functionality
            ST1B(UART7->CTL, UARTEN); //uart enable
            break;

        case RX:
            /* gpio pin configuration   */
            ST1B(GPIOE->AFSEL, PE0); //change pin function
            CLR1B(GPIOE->AMSEL, PE0); //disable analog functionality
            ST4B4MI(GPIOE->PCTL, PE0, 1); //change pin mode
            ST1B(GPIOE->DEN, PE0); //enable digital functionality
            /* UART pin configuration   */
            CLR1B(UART7->CTL, UARTEN); //disable uartn module
            if (isBaudRateValid(utConfig->BAUD_RATE) == BAUDRATE_VALID)
            { //is valid baud rate
                STV(UART7->IBRD, BAUDINT(sysclock,utConfig->BAUD_RATE)); //put the integer part of baud rate computation into int baud register
                STV6BI(UART7->FBRD, BIT0,
                       BAUDFLOAT(sysclock,utConfig->BAUD_RATE)); ////put the float part of baud rate computation into float baud register
            }
            else //by default it is 9600bps
            {
                STV(UART7->IBRD, BAUDINT(sysclock,9600)); //put the integer part of baud rate computation into int baud register
                STV6BI(UART7->FBRD, BIT0, BAUDFLOAT(sysclock,9600)); ////put the float part of baud rate computation into float baud register
            }
            if (isCharSizeVaild(utConfig->CHAR_LEN) == CHARSIZE_VALID)
            {
                STV2BI(UART7->LCRH, WLEN, (utConfig->CHAR_LEN) - 5); //set character size
            }
            else //default character size is 7
            {
                STV2BI(UART7->LCRH, WLEN, 7 - 5); //set character size
            }
            if (utConfig->NSTOP_BIT == 2) //two stop bits
            {
                ST1B(UART7->LCRH, STP2); //two stop bits
            }
            else
            {
                CLR1B(UART7->LCRH, STP2); //one stop bit
            }
            CLR1B(UART7->LCRH, FEN); //disable fifo queue functionality
            STV4BI(UART7->CC, CS, 0); //select system clock source
            CLR1B(UART7->CTL, HSE); //select 16BAUD,sampling period
            ST1B(UART7->CTL, RXE); //enable receive functionality
            ST1B(UART7->CTL, UARTEN); //uart enable
            break;
        case BOTH:
            /* gpio pin configuration   */
            ST2B(GPIOE->AFSEL, PE0, PE1); //change pin function
            CLR2B(GPIOE->AMSEL, PE0, PE1); //disable analog functionality
            ST4B4MI(GPIOE->PCTL, PE0, 1); //change pin mode
            ST4B4MI(GPIOE->PCTL, PE1, 1); //change pin mode
            ST2B(GPIOE->DEN, PE0, PE1); //enable digital functionality
            /* UART pin configuration   */
            CLR1B(UART7->CTL, UARTEN); //disable uartn module
            if (isBaudRateValid(utConfig->BAUD_RATE) == BAUDRATE_VALID)
            { //is valid baud rate
                STV(UART7->IBRD, BAUDINT(sysclock,utConfig->BAUD_RATE)); //put the integer part of baud rate computation into int baud register
                STV6BI(UART7->FBRD, BIT0,
                       BAUDFLOAT(sysclock,utConfig->BAUD_RATE)); ////put the float part of baud rate computation into float baud register
            }
            else //by default it is 9600bps
            {
                STV(UART7->IBRD, BAUDINT(sysclock,9600)); //put the integer part of baud rate computation into int baud register
                STV6BI(UART7->FBRD, BIT0, BAUDFLOAT(sysclock,9600)); ////put the float part of baud rate computation into float baud register
            }
            if (isCharSizeVaild(utConfig->CHAR_LEN) == CHARSIZE_VALID)
            {
                STV2BI(UART7->LCRH, WLEN, (utConfig->CHAR_LEN) - 5); //set character size
            }
            else //default character size is 7
            {
                STV2BI(UART7->LCRH, WLEN, 7 - 5); //set character size
            }
            if (utConfig->NSTOP_BIT == 2) //two stop bits
            {
                ST1B(UART7->LCRH, STP2); //two stop bits
            }
            else
            {
                CLR1B(UART7->LCRH, STP2); //one stop bit
            }
            CLR1B(UART7->LCRH, FEN); //disable fifo queue functionality
            STV4BI(UART7->CC, CS, 0); //select system clock source
            CLR1B(UART7->CTL, HSE); //select 16BAUD,sampling period
            ST2B(UART7->CTL, RXE, TXE); //enable transmit & receive functionality
            ST1B(UART7->CTL, UARTEN); //uart enable
        }
        break;
    }

}
//send one char
void Uart_SendChar(uint8_t uartn, int8_t character)
{
    switch (uartn)
    {
    case UT0:
        while (RD1B(UART0->FR, TXFF) == 1) //if the buffer is empty wait
        {
        }
        ;
        UART0->DR = character; //send one char
        break;
    case UT1:
        while (RD1B(UART1->FR, TXFF) == 1) //if the buffer is empty wait
        {
        }
        ;
        UART1->DR = character; //send one char
        break;
    case UT2:
        while (RD1B(UART2->FR, TXFF) == 1) //if the buffer is empty wait
        {
        }
        ;
        UART2->DR = character; //send one char
        break;
    case UT3:
        while (RD1B(UART3->FR, TXFF) == 1) //if the buffer is empty wait
        {
        }
        ;
        UART3->DR = character; //send one char
        break;
    case UT4:
        while (RD1B(UART4->FR, TXFF) == 1) //if the buffer is empty wait
        {
        }
        ;
        UART4->DR = character; //send one char
        break;
    case UT5:
        while (RD1B(UART5->FR, TXFF) == 1) //if the buffer is empty wait
        {
        }
        ;
        UART5->DR = character; //send one char
        break;
    case UT7:
        while (RD1B(UART7->FR, TXFF) == 1) //if the buffer is empty wait
        {
        }
        ;
        UART7->DR = character; //send one char
        break;
    }
}
/* uart send array of chars*/
void Uart_SendStr(uint8_t uartn, int8_t* str)
{
    uint8_t count = 0; //index to the next int8_tto be transmitted
    while (str[count] != '\0')  //send all chars except null
    {
        Uart_SendChar(uartn, str[count]); //send one int8_tevery time
        count++;  //increment the index
    }
}
/* uart send array of chars*/
void Uart_SendStrRcNl(uint8_t uartn, int8_t* str)
{
    uint8_t count = 0; //index to the next int8_tto be transmitted
    while (str[count] != '\0')  //send all chars except null
    {
        Uart_SendChar(uartn, str[count]); //send one int8_tevery time
        count++;  //increment the index
    }
    Uart_SendChar(uartn, '\r'); //send '\r'
    Uart_SendChar(uartn, '\n'); //send '\n'
}
int8_t UART_GetChar(uint8_t uartn)
{
    int8_t data = 0;  //variable to store char
    switch (uartn)
    {
    case UT0: //case uart 0
        while (RD1B(UART0->FR, RXFE) == 1) //if the buffer is empty wait until new character is received
        { // do nothing if the fifo is empty
        }
        ;
        data = UART0->DR;
        break; //hold the received int8_tin data variable
    case UT1:
        while (RD1B(UART1->FR, RXFE) == 1) //if the buffer is empty wait until new character is received
        { // do nothing if the fifo is empty
        }
        ;
        data = UART1->DR; //hold the received int8_tin data variable
        break;
    case UT2:
        while (RD1B(UART2->FR, RXFE) == 1) //if the buffer is empty wait until new character is received
        { // do nothing if the fifo is empty
        }
        ;
        data = UART2->DR; //hold the received int8_tin data variable
        break;
    case UT3:
        while (RD1B(UART3->FR, RXFE) == 1) //if the buffer is empty wait until new character is received
        { // do nothing if the fifo is empty
        }
        ;
        data = UART3->DR; //hold the received int8_tin data variable
        break;
    case UT4:
        while (RD1B(UART4->FR, RXFE) == 1) //if the buffer is empty wait until new character is received
        { // do nothing if the fifo is empty
        }
        ;
        data = UART4->DR; //hold the received int8_tin data variable
        break;
    case UT5:
        while (RD1B(UART5->FR, RXFE) == 1) //if the buffer is empty wait until new character is received
        { // do nothing if the fifo is empty
        }
        ;
        data = UART5->DR; //hold the received int8_tin data variable
        break;
    case UT6:
        while (RD1B(UART6->FR, RXFE) == 1) //if the buffer is empty wait until new character is received
        { // do nothing if the fifo is empty
        }
        ;
        data = UART6->DR; //hold the received int8_tin data variable
        break;
    case UT7:
        while (RD1B(UART7->FR, RXFE) == 1) //if the buffer is empty wait until new character is received
        { // do nothing if the fifo is empty
        }
        ;
        data = UART7->DR; //hold the received int8_tin data variable
        break;
    }
    return data; //return the received data
}
//------------UART_InString------------
// Accepts ASCII characters from the serial port
//    and adds them to a string until <enter> is typed
//    or until max length of the string is reached.
// It echoes each character as it is inputted.
// If a backspace is inputted, the string is modified
//    and the backspace is echoed
// terminates the string with a null character
// uses busy-waiting synchronization on RDRF
// Input: pointer to empty buffer, size of buffer
// Output: Null terminated string
// -- Modified by Agustinus Darmawan + Mingjie Qiu --
void UART_GetStrRcNl(uint8_t uartn, int8_t* str, uint32_t max)
{
    int8_t count = 0; //count number of received chars
    int8_t ch = 0; //variable to hold char
    switch (uartn)
    {
    case UT0:
        while (((ch = UART_GetChar(UT0)) != '\r') && count < max) //receive all chars except '\r',max chars can be received is determined be max
        {
            if (ch == '\0')
                continue; //if the transmitter does system reset or the wire is broken
                          //skip storing the NUll character
            str[count] = ch; //store the new char
            count++; //increment index to store the next char
        }
        break;
    case UT1:
        while (((ch = UART_GetChar(UT1)) != '\r') && (count < max)) //receive all chars except '\r',max chars can be received is determined be max
        {
            str[count] = ch; //store the new char
            count++; //increment index to store the next char
        }
        break;
    case UT2:
        while (((ch = UART_GetChar(UT2)) != '\r') && count < max) //receive all chars except '\r',max chars can be received is determined be max
        {

            if (ch == '\0')
                continue; //if the transmitter does system reset or the wire is broken
                          //skip storing the NUll character
            str[count] = ch; //store the new char
            count++; //increment index to store the next char
        }
        break;
    case UT3:
        while (((ch = UART_GetChar(UT3)) != '\r') && count < max) //receive all chars except '\r',max chars can be received is determined be max
        {
            if (ch == '\0')
                continue; //if the transmitter does system reset or the wire is broken
                          //skip storing the NUll character
            str[count] = ch; //store the new char
            count++; //increment index to store the next char
        }
        break;
    case UT4:
        while (((ch = UART_GetChar(UT4)) != '\r') && count < max) //receive all chars except '\r',max chars can be received is determined be max
        {
            if (ch == '\0')
                continue; //if the transmitter does system reset or the wire is broken
                          //skip storing the NUll character
            str[count] = ch; //store the new char
            count++; //increment index to store the next char
        }
        break;
    case UT5:
        while (((ch = UART_GetChar(UT5)) != '\r') && count < max) //receive all chars except '\r',max chars can be received is determined be max
        {
            if (ch == '\0')
                continue; //if the transmitter does system reset or the wire is broken
                          //skip storing the NUll character
            str[count] = ch; //store the new char
            count++; //increment index to store the next char
        }
        break;
    case UT6:
        while (((ch = UART_GetChar(UT6)) != '\r') && count < max) //receive all chars except '\r',max chars can be received is determined be max
        {
            if (ch == '\0')
                continue; //if the transmitter does system reset or the wire is broken
                          //skip storing the NUll character
            str[count] = ch; //store the new char
            count++; //increment index to store the next char
        }
        break;
    case UT7:
        while (((ch = UART_GetChar(UT7)) != '\r') && count < max) //receive all chars except '\r',max chars can be received is determined be max
        {
            if (ch == '\0')
                continue; //if the transmitter does system reset or the wire is broken
                          //skip storing the NUll character
            str[count] = ch; //store the new char
            count++; //increment index to store the next char
        }
        break;
    }
    ch = UART_GetChar(uartn); //remove \n
    str[count] = '\0';        //terminate with null
}
void UART_GetStr(uint8_t uartn, int8_t* str, uint32_t max)
{
    int8_t count = 0; //count number of received chars
    int8_t ch; //variable to hold char
    switch (uartn)
    {
    case UT0:
        while (((ch = UART_GetChar(UT0)) != '\0') && count < max) //receive all chars except '\r',max chars can be received is determined be max
        {
            str[count] = ch; //store the new char
            count++; //increment index to store the next char
        }
        break;
    case UT1:
        while (((ch = UART_GetChar(UT1)) != '\0') && count < max) //receive all chars except '\r',max chars can be received is determined be max
        {
            str[count] = ch; //store the new char
            count++; //increment index to store the next char
        }
        break;
    case UT2:
        while (((ch = UART_GetChar(UT2)) != '\0') && count < max) //receive all chars except '\r',max chars can be received is determined be max
        {
            str[count] = ch; //store the new char
            count++; //increment index to store the next char
        }
        break;
    case UT3:
        while (((ch = UART_GetChar(UT3)) != '\0') && count < max) //receive all chars except '\r',max chars can be received is determined be max
        {
            str[count] = ch; //store the new char
            count++; //increment index to store the next char
        }
        break;
    case UT4:
        while (((ch = UART_GetChar(UT4)) != '\0') && count < max) //receive all chars except '\r',max chars can be received is determined be max
        {
            str[count] = ch; //store the new char
            count++; //increment index to store the next char
        }
        break;
    case UT5:
        while (((ch = UART_GetChar(UT5)) != '\0') && count < max) //receive all chars except '\r',max chars can be received is determined be max
        {
            str[count] = ch; //store the new char
            count++; //increment index to store the next char
        }
        break;
    case UT6:
        while (((ch = UART_GetChar(UT6)) != '\0') && count < max) //receive all chars except '\r',max chars can be received is determined be max
        {
            str[count] = ch; //store the new char
            count++; //increment index to store the next char
        }
        break;
    case UT7:
        while (((ch = UART_GetChar(UT7)) != '\0') && count < max) //receive all chars except '\r',max chars can be received is determined be max
        {
            str[count] = ch; //store the new char
            count++; //increment index to store the next char
        }
        break;
    }
    str[count] = '\0'; //terminate with null
}
void UART_AT_Resp_Receive(uint8_t uartn, int8_t* string, uint32_t max)
{
    int8_t length = 0;
    int8_t character;
    switch (uartn)
    {
    case UT1:
        while (length < max)
        {
            character = UART_GetChar(UT1);
            *string++ = character;
            length++;
            if (character == 'O')
            {
                character = UART_GetChar(UT1);
                *string++ = character;
                length++;
                if (character == 'K')
                {
                    character = UART_GetChar(UT1);
                    *string++ = character; //store '\r'
                    length++;
                    if (character == '\r')
                    {
                        character = UART_GetChar(UT1);
                        *string++ = character;  // store '\n'
                        length++;
                        if (character == '\n')
                        {
                            *string = '\0';
                            length++;
                            break;
                        }
                    }
                }
            }
        }
        break;
    }
}
void Uart_SendInt(uint8_t uartn, int32_t num)
{
    Uart_SendStr(uartn, intToStr(num));

}
void Uart_SendFloat(uint32_t uartn, double float_num, uint8_t precision)
{
    Uart_SendStr(uartn, floatToStr(float_num, precision));
}
//print to terminal 
void printTerm(int8_t* str)
{
   Uart_SendStrRcNl(UT0,str);//print to terminal with RC NL
}
/*
void UART_Interrupt_Init(uint8_t uartn, uint32_t baudRate, uint8_t both){
	switch (uartn) {
	case UT0: //U0RX  PA0 , U0TX PA1
		ST1B(SYSCTL->RCGCGPIO, PORTA);
		ST1B(SYSCTL->RCGCUART, UT0);
		switch (both) {
		case TX:
			ST1B(GPIOA->AFSEL, PA1);
			CLR1B(GPIOA->AMSEL, PA1);
			ST4B4MI(GPIOA->PCTL, PA1, 1); //PA1 works as Tx
			ST1B(GPIOA->DEN, PA1);
			CLR1B(UART0->CTL, UARTEN);
			STV(UART0->IBRD, BAUDINT(baudRate));//BAUDINT(baudRate);
			STV6BI(UART0->FBRD, BIT0, BAUDFLOAT(sysclock,baudRate));
			STV2BI(UART0->LCRH, WLEN, charcter_bits(8));
			CLR1B(UART0->LCRH, STP2);
			ST1B(UART0->LCRH, FEN);
			STV4BI(UART0->CC, CS, 0);
			CLR1B(UART0->CTL, HSE);
		    ST1B(UART0->IM,TXIM);
		    NVIC_Enable_IRQ(UART0_VECTOR,0);
			ST1B(UART0->CTL, TXE);
			ST1B(UART0->CTL, UARTEN);
			break;
		case RX:
			ST1B(GPIOA->AFSEL, PA0);
			CLR1B(GPIOA->AMSEL, PA0);
			ST4B4MI(GPIOA->PCTL, PA0, 1); //PA1 works as Tx
			ST1B(GPIOA->DEN, PA0);
			CLR1B(UART0->CTL, UARTEN);
			STV(UART0->IBRD, BAUDINT(baudRate));//BAUDINT(baudRate);
			STV6BI(UART0->FBRD, BIT0, BAUDFLOAT(baudRate));
			STV2BI(UART0->LCRH, WLEN, charcter_bits(8));
			CLR1B(UART0->LCRH, STP2);
			ST1B(UART0->LCRH, FEN);
			STV4BI(UART0->CC, CS, 0);
			CLR1B(UART0->CTL, HSE);
			ST1B(UART0->IM,RXIM);
		    NVIC_Enable_IRQ(UART0_VECTOR,0);
			ST1B(UART0->CTL, RXE);
			ST1B(UART0->CTL, UARTEN);
			break;
		case BOTH:
			ST1B(GPIOA->AFSEL, PA1);
			ST1B(GPIOA->AFSEL, PA0);
			CLR1B(GPIOA->AMSEL, PA1);
			CLR1B(GPIOA->AMSEL, PA0);
			ST4B4MI(GPIOA->PCTL, PA1, 1); //PA1 works as Tx
			ST4B4MI(GPIOA->PCTL, PA0, 1); //PA1 works as Tx
			ST1B(GPIOA->DEN, PA1);
			ST1B(GPIOA->DEN, PA0);
			CLR1B(UART0->CTL, UARTEN);
			STV(UART0->IBRD, BAUDINT(sysclock,baudRate));//BAUDINT(baudRate);
			STV6BI(UART0->FBRD, BIT0, BAUDFLOAT(sysclock,baudRate));
			STV2BI(UART0->LCRH, WLEN, charcter_bits(8));
			CLR1B(UART0->LCRH, STP2);
			//	ST1B(UART0->LCRH,FEN);
			STV4BI(UART0->CC, CS, 0);
			CLR1B(UART0->CTL, HSE);
			ST1B(UART0->IM, RXIM);
			ST1B(UART0->CTL, TXE);
			ST1B(UART0->CTL, RXE);
			NVIC_Enable_IRQ(UART0_VECTOR, 1);
			ST1B(UART0->CTL, UARTEN);
		}
	}
}
*/


