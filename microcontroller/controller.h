#include <stdint.h>
#include "empty_defs.h"

typedef uint16_t b16_t;

typedef struct dm13a {
    _pin_t dai;  // DataIn pin
    _pin_t dck;  // DataClock pin
    _pin_t lat;  // Latch pin
    int size;  // Number of DM13A chips in chain
    b16_t* buffer;  // array of length equal to size (MSB of buffer[0] will end up on first LED of first DM13A)
} dm13a;

/**
    Update all bits of particular DM13A
    @param chain pointer to DM13A struct
    @param index chip's index in the chain
    @param newval 16 bits of data of macrodefined type b16_t
*/
void dm13a_setbits(dm13a* chain, int index, b16_t newval) {
    if(index < chain->size) {  // only if index is valid
        chain->buffer[index] = newval;
    }
}

/**
    Update one chain's bit
    @param chain pointer to DM13A struct
    @param diode_ind diode index in chain (counting from first LED of first chip)
    @param newbit new LED state to be assigned (off if 0, on otherwise)
*/
void dm13a_setbit(dm13a* chain, int diode_ind, int newbit) {
    if(diode_ind < 16 * chain->size) {  // only if index is valid
        if(newbit) newbit = 1;  // in case of nonbinary values, we trust C boolean syntax
        else newbit = 0;
        int chip = diode_ind / 16;
        int rev_ind = 15 - (diode_ind % 16);
        if((chain->buffer[chip] >> rev_ind) % 2 != newbit) {  // bit has to be changed
            chain->buffer[chip] ^= (1 << rev_ind);
        }
    }
}

void dm13a_flush(dm13a* chain);

void dm13a_init(dm13a* crt, _pin_t dai, _pin_t dck, _pin_t lat, int size, b16_t* buffer);
