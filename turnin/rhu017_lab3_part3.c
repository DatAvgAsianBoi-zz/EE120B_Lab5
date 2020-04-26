/*	Author: huryan18
 *  Partner(s) Name:
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *    Video Link : https://youtu.be/qTORDjZMppg

 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
// volatile unsigned char TimerFlag = 0;
enum States {start, inactive, wait} state;
unsigned char output;
unsigned char count;

// void TimerSR() {TimerFlag = 1;}

void tick(){
      switch(state){
            case start:
                  state = inactive;
                  break;
            case inactive:
			if(~PINA & 0x01){
				if(output == 0)
					output = 0x01;
				else{
					if(count == 0){
						output *= 2;
						if(output > 0x40)
							count = 1;
					}
					else{
						output >> 1;
						if(output == 0x00)
							count = 0;
					}
				}
				state = wait;
			}
			else
				state = inactive;
                  break;
            case wait:
                  state = (~PINA & 0x01)? wait : inactive;
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
	output = 0x00;
	count = 0;
      while (1) {
          	tick();
  		PORTC = output;
      }
      return 1;
}
