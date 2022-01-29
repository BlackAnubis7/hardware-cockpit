#include "arduino_defs.h"

typedef struct dm13a {
    _pin_t dai;  // DataIn pin
    _pin_t dck;  // DataClock pin
    _pin_t lat;  // Load pin
    _pin_t en;  // Enable pin
    int size;  // Number of DM13A chips in chain
    _b16_t* buffer;  // array of length equal to size (MSB of buffer[0] will end up on first LED of first DM13A)
} dm13a;

// Initialise new dm13a struct
dm13a* dm13a_init(_pin_t dai, _pin_t dck, _pin_t lat, _pin_t en, int size, _b16_t* buffer) {
    dm13a crt;
    crt.dai = dai;
    _OUT_INIT(dai);
    _OUT_LOW(dai);
    crt.dck = dck;
    _OUT_INIT(dck);
    _OUT_LOW(dck);
    crt.lat = lat;
    _OUT_INIT(lat);
    _OUT_LOW(lat);
    crt.en = en;
    _OUT_INIT(en);
    _OUT_LOW(en);
    crt.size = size;
    crt.buffer = buffer;
    for(int i=0; i<size; i++) buffer[i] = 0;
    return &dm13a;
}

// Update all bits of particular DM13A
void dm13a_setbits(dm13a* chain, int index, _b16_t newval) {
    if(index < chain->size) {  // only if index is valid
        chain->buffer[index] = newval;
    }
}

// Update one chain's bit
void dm13a_setbit(dm13a* chain, int index, int bit) {
    if(index < 16 * chain->size) {  // only if index is valid
        if(bit) bit = 1;  // in case of nonbinary values, we trust C boolean syntax
        int chip = index / 16;
        int rev_ind = 15 - (index % 16);
        if((chain->buffer[index] >> rev_ind) % 2 != bit) {  // bit has to be changed
            chain->buffer[index] ^= (1 << rev_ind);
        }
    }
}

// Flush buffer into DM13A chain
void dm13a_flush(dm13a* chain) {
    for(int c = chain->size-1; c>=0; c--) {
        for(int i=0; i<32; i++) {
            if(i%2 == 0) {
                _OUT_HIGH(chain->dck);
            } else {
                _OUT_LOW(chain->dck);
                _OUT_IF(chain->dai, (chain->buffer[c] >> i/2) % 2 == 1);
            }
        }
        _OUT_HIGH(chain->lat);
        _SLEEP_MS(1);  // without that delay, correct work is not guaranteed
        _OUT_LOW(chain->lat);
    }
}
