#include <stdint.h>
#include "arduino_defs.h"

typedef uint16_t _b16_t;

typedef struct dm13a {
    _pin_t dai;  // DataIn pin
    _pin_t dck;  // DataClock pin
    _pin_t lat;  // Latch pin
    int size;  // Number of DM13A chips in chain
    _b16_t* buffer;  // array of length equal to size (MSB of buffer[0] will end up on first LED of first DM13A)
} dm13a;

/*
    Update all bits of particular DM13A
    @param chain pointer to DM13A struct
    @param index chip's index in the chain
    @param newval 16 bits of data of macrodefined type _b16_t
*/
void dm13a_setbits(dm13a* chain, int index, _b16_t newval) {
    if(index < chain->size) {  // only if index is valid
        chain->buffer[index] = newval;
    }
}

/*
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

/*
    Flush buffer into DM13A chain
    @param chain pointer to DM13A struct
*/
void dm13a_flush(dm13a* chain) {
    _OUT_LOW(chain->lat);
    for(int c = chain->size-1; c>=0; c--) {
        for(int i=0; i<=32; i++) {  // 32 will create the last clock edge
            if(i%2 == 0) {
                _OUT_HIGH(chain->dck);
            } else {
                _OUT_LOW(chain->dck);
                _OUT_IF(chain->dai, (chain->buffer[c] >> i/2) % 2 == 1);
            }
        }
    }
    _OUT_LOW(chain->dck);
    _OUT_HIGH(chain->lat);
    _SLEEP_MS(1);  // without that delay, correct work is not guaranteed
}

/*
    Initialise new dm13a struct
    @param crt pointer to DM13A struct
    @param dai DataIn identifier of macrodefined type _pin_t
    @param dck DataClock identifier of macrodefined type _pin_t
    @param lat Latch identifier of macrodefined type _pin_t
    @param size number of DM13A chips in the chain
    @param buffer array of _b16_t elements; array's length has to be at least "size" (elements with indices equal or greater than "size" will remain unused)
*/
void dm13a_init(dm13a* crt, _pin_t dai, _pin_t dck, _pin_t lat, int size, _b16_t* buffer) {
    crt->dai = dai;
    _OUT_INIT(dai);
    _OUT_LOW(dai);
    crt->dck = dck;
    _OUT_INIT(dck);
    _OUT_LOW(dck);
    crt->lat = lat;
    _OUT_INIT(lat);
    _OUT_LOW(lat);
    crt->size = size;
    crt->buffer = buffer;
    for(int i=0; i<size; i++) buffer[i] = 0;
    dm13a_flush(crt);
}
