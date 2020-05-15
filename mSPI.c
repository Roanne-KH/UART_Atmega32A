#include <xc.h>
#include"mSPI.h"
void SPI_init(int SPI_Mode, char Prescaler)

{
    DDRB |=(1<<MOSI)|(1<<SCK)|(1<SS); // Declaring those pins as inputs.
    SPCR|=(1<<SPIE)|(1<<SPE)|( SPI_Mode<<MSTR)|(Prescaler <<0);
    
}

void SPI_write(char data )
{   SPDR=0;
    SPDR = data;// Send data , flag =1 when serial transmisssion is complete
    while (!(SPSR & (1<<SPIF)));// It waits until SPIE flag IS SET  
    
}
