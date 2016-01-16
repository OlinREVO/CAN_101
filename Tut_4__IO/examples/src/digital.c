// Digital input to digital output
// Try modifying this to toggle the digital output every time
// you click the button

#define F_CPU (1000000L)
#include <avr/io.h>

int main (void) {
    // Set PE1 to output (pin 10)
    DDRE |= _BV(PE1);

    // Set PE2 to input (pin 11)
    DDRE &= ~(_BV(PE2)); 

    while(1) {
        if(PINE & _BV(PE2)){
            // Turn on
            PORTE |= _BV(PE1);
        }else{
            // Turn off
            PORTE &= ~(_BV(PE1));
        }
    }
}
