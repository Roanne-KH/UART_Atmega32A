#include<xc.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define F_CPU 8000000UL

char _newline[]="\t\r";// variable to dispaly values iN UART LINE BY LINE
// Enavling the transmission to UART 
void UART_init(int BaudRate) {
  // TX::
    UCSRB |= (1 << TXEN);          // Enable Transmitter
   // UCSRC|=(1<<USBS);           if IT IS WRITTEN THIS WAT THEN THE BIT NUMBER USB EILL BE SET IN UBRRH NOT UCSRC, URSEL=0.
    UCSRC|=(1<<URSEL)|(1<<USBS);  // IF THE URSEL=1 THEN WE CAN WRITE ON UCSRC , TO CHANGE THE NUM OF STOP BITS TO 2BITS
 //RX::
    UCSRB |= (1 << RXEN);       //Enable Receiver
     //UCSRB |= (1 <<UDRIE);      //EnableUDRinterrupt to indicate if  (UDR) is ready to receive new data
    UCSRB |= (1 << RXCIE);     // Enablr RX_INTERRUPT enable when RXC flag =1 , INTERRUPT will be triggered --->means unread data still in UDR.
 // BaudRate::
    int val;
    val=(F_CPU/16.0/BaudRate)-1;
    UBRRL = (char)val;             //1st least  8 bits.CAST
    UBRRH = (char)val>>8;           // extention bits for higher baud rate values.
}

int isPressed(int pinNum) {
    if (PINC & (1 << pinNum)) {
        return 1;
    } else
        return 0;
}
int isSet(int pinNum) {
    if (PINC & (1 << pinNum)) {
        return 1;
    } else
        return 0;
}

//this function is to transmit a single character. 
void transmitChar(char data) {
    while (!(UCSRA & (1 << UDRE)));// POOLING WAY : WAIT FOR FLAG TO BE SETTED , we didnot use  ISR OF UDRE Flag.
    UDR = data;
}
//this function is to transmit strings 
void transmitString(char *data) {
    for (int i = 0; data[i] != '\0'; i++) {
        transmitChar(data[i]);
    }
}

//this function is convert integer to string to be be displayed in uart terminal
void transmitValue(int val) {

    char buffer[20];
    itoa(val,buffer,10);
    transmitString(buffer);
}
// this function is be able to show each value line by line.
void newline(){
    transmitString(_newline);
}