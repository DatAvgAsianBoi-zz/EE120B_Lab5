/*	Author: huryan18
 *  Partner(s) Name:
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

unsigned char GetBit(unsigned char x, unsigned char k) {
      return ((x & (0x01 << k)) != 0);
}

int main(void) {
      /* Insert DDR and PORT initializations */
      DDRA = 0x00; PORTA = 0xFF;
      //DDRB = 0x00; PORTB = 0xFF;
      DDRC = 0xFF; PORTC = 0x00;
      /* Insert your solution below */
      unsigned char fuel_lvl = PINA & (0x0F);
      unsigned char output = 0x00;
      while (1) {
            fuel_lvl = PINA & (0x0F);
            output = 0x00;

            if(fuel_lvl > 12) //Level 13 - 15
                  output = output | 0x01;
            if(fuel_lvl > 9) //Level 10 - 12
                  output = output | 0x02;
            if(fuel_lvl > 6) //Level 7 - 9
                  output = output | 0x04;
            if(fuel_lvl > 4) //Level 5 - 6
                  output = output | 0x08;
            if(fuel_lvl > 2) //Level 3 - 4
                  output = output | 0x10;
            if(fuel_lvl > 0) //Level 1 - 2
                  output = output | 0x20;
            if(fuel_lvl < 5)
                  output = output | 0x40;

            if((PINA & 0x10) && (PINA & 0x20) && !(PINA & 0x40))
                  output = output | 0x80;

            PORTC = output;

    }
    return 1;
}
