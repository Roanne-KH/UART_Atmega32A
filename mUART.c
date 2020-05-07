#include<xc.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define F_CPU 8000000UL
// Enavling the transmission to UART 
void UART_init(int BaudRate) {
    UCSRB |= (1 << TXEN);          // Enable Transmitter
   // UCSRC|=(1<<USBS);           if IT IS WRITTEN THIS WAT THEN THE BIT NUMBER USB EILL BE SET IN UBRRH NOT UCSRC, URSEL=0.
    UCSRC|=(1<<URSEL)|(1<<USBS);  // IF THE URSEL=1 THEN WE CAN WRITE ON UCSRC TO CHANGE THE NUM OF STOP BITS TO 2BITS
 
    UCSRB |= (1 << RXEN);       //Enable Receiver
     //UCSRB |= (1 <<UDRIE);      //EnableUDRinterrupt to indicate if  (UDR) is ready to receive new data
     UCSRB |= (1 << RXCIE);     // Enablr RX_INTERRUPT enable when RXC flag =1 , INTERRUPT will be triggered --->means unread data still in UDR.
    // BaudRate
    int val;
    val=(F_CPU/16.0/BaudRate)-1;
    UBRRL = (char)val;             //1st least  8 bits.CAST
    UBRRH = (char)val>>8;
}

int isPressed(int pinNum) {
    if (PINC & (1 << pinNum)) {
        return 1;
    } else
        return 0;
}


void transmitChar(char data) {
    while (!(UCSRA & (1 << UDRE)));// POOLING WAY : WAIT FOR FLAG
    UDR = data;
}

void transmitString(char *data) {
    for (int i = 0; data[i] != '\0'; i++) {
        transmitChar(data[i]);
    }
}


void transmitValue(int val) {

    char buffer[20];
    itoa(val,buffer,10);
    transmitString(buffer);
}
