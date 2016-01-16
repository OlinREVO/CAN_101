#define F_CPU (1000000L)
#include <avr/io.h>
#include <avr/interrupt.h> // Necessary for interrupts

ISR(INT1_vect) {
    //**********************************
    // Flip state of LED at pin 10 due to
    // interrupt on pin 16
    PORTE |= _BV(PE1);
}


int main( void ){
    //**********************************
    // Enable global interrupts
    sei();

    //**********************************
    // Set up pin 10 as output
    // Will be used to drive an LED
    // LED will have a state change on 
    //   interrupt of pin 16
    DDRE |= _BV(PE1); 

    //**********************************
    // Initialize pin 16 as interrupt pin
    // Will sense a button driving voltage of
    //  pin low (0V). The interrupt action will
    //  be to change LED state on pin 10
    EICRA = _BV(ISC00); // Interrupt on LOW
    EIMSK = _BV(INT1);  // Pin 16 interruptable

    //**********************************
    // Infinite for loop. Other things can be
    //  done here. Generally if an infinite
    //  for loop is to be used putting the ATmega
    //  to sleep is preferred -- but that is some
    //  fancy stuff
    for (;;) {
        // Loop 5evahhhhh
    }
}
