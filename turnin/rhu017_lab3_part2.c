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
// volatile unsigned char TimerFlag = 0;
enum States {start, inactive, wait_inc, wait_dec, wait_reset} state;
	unsigned char count;


// void TimerSR() {TimerFlag = 1;}

void tick(){
      switch(state){
            case start:
                  state = inactive;
                  break;
            case inactive:
				  if(~PINA & 0x01){
					  if(~PINA & 0x02)
						state = wait_reset;
					  else{
						if(++count > 9)
						  count = 9;
						state = wait_inc;
					  }
				  }
				  else if(~PINA & 0x02){
					  if(~PINA & 0x01)
						  state = wait_reset;
					  else{
						  if(count-- <= 0)
							count = 0;
						  state = wait_dec;
					  }
				  }
				  else
					  state = inactive;

                  break;
            case wait_inc:
                  state = (~PINA & 0x01)? wait_inc : inactive;
                  break;
            case wait_dec:
                  state = (~PINA & 0x02)? wait_dec : inactive;
                  break;
            case wait_reset:
                  state = ((~PINA & 0x01) || (~PINA & 0x02))? wait_reset : inactive;
                  break;
            default: state = start;
                  break;
      }
}


int main(void) {
      /* Insert DDR and PORT initializations */
      DDRA = 0x00; PORTA = 0xFF;
      // DDRB = 0xFF; PORTB = 0x00;
      DDRC = 0xFF; PORTC = 7;
      /* Insert your solution below */
      state = start;
	  count = 0;
      while (1) {
          tick();
		  PORTC = count;
      }
      return 1;
}
