#include "arduino_defs.h"
#include "misc_defs.h"

#define MAX7219_NO_SHUTDOWN 0x0C01
#define MAX7219_DISPLAY_TEST 0x0F01
#define MAX7219_NO_DISPLAY_TEST 0x0F00
#define MAX7219_DECODE_MODE_PREFIX 0x0900
#define MAX7219_INTENSITY_PREFIX 0x0A00
#define MAX7219_SCAN_LIMIT_PREFIX 0x0B00

typedef struct max7219 {
    _pin_t din;  // DataIn pin
    _pin_t clk;  // Clock pin
    _pin_t load;  // Load pin
    short size;  // Number of MAX7219 chips in chain
    _b8_t* chars;  // array of length at least 8*size (represents displayed digits/characters)
    // chars[0] is D0 of the 1st chip; chars[1] is D1 of the 1st cip; chars[8] is D0 of the 2nd chip etc.
    _b16_t* buffer;  // array of length equal to size (MSB of buffer[0] will enter the MAX7219 chain last)
} max7219;

/*
    Update all bits of particular MAX7219
    @param chain pointer to MAX7219 struct
    @param index chip's index in the chain (index=0 is the chip directly connected to the microcontroller)
    @param newval 16 bits of data of macrodefined type _b16_t
*/
void max7219_setbits(max7219* chain, int index, _b16_t newval) {
    if(index < chain->size) {
        chain->buffer[index] = newval;
    }
}

/*
    Flush buffer into MAX7219 chain
    @param chain pointer to MAX7219 struct
*/
void max7219_flush(max7219* chain) {
    _OUT_LOW(chain->clk);
    _OUT_LOW(chain->load);
    for(int c = chain->size-1; c>=0; c--) {
        for(int i=32; i>=0; i--) {  // 32 will create the last clock edge
            if(i%2 == 0) {
                _OUT_HIGH(chain->clk);
            } else {
                _OUT_IF(chain->din, (chain->buffer[c] >> i/2) % 2 == 1);
                _OUT_LOW(chain->clk);
            }
        }
    }
    _OUT_LOW(chain->din);
    _OUT_LOW(chain->clk);
    _OUT_HIGH(chain->load);
    _SLEEP_MICROS(1);  // just in case - documentation states it should be at least 50ns (this is 20x more)
    _OUT_HIGH(chain->clk);
}

/*
    Send same set of bits to every chip in the chain
    @param chain pointer to MAX7219 struct
    @param val set of 16 bits to be sent
*/
void max7219_send_to_all_chips(max7219* chain, _b16_t val) {
    for(int c = chain->size-1; c>=0; c--) {
        max7219_setbits(chain, c, val);
    }
    max7219_flush(chain);
}

/*
    Set all digits of the chain to blank
    @param chain pointer to MAX7219 struct
*/
void max7219_clear(max7219* chain) {
    for(_b16_t sig=0x0100; sig<=0x0800; sig+=0x0100) {
        max7219_send_to_all_chips(chain, sig);
    }
}

/*
    Prepare the display - turn it on and perform basic configuration
    @param chain pointer to MAX7219 struct
    @param intensity expected brightness [0, 15] - 0 is very dim, but still visible
*/
void max7219_prepare(max7219* chain, uint8_t intensity) {
    max7219_send_to_all_chips(chain, MAX7219_NO_SHUTDOWN);
    max7219_clear(chain);
    max7219_send_to_all_chips(chain, MAX7219_NO_DISPLAY_TEST);
    max7219_send_to_all_chips(chain, MAX7219_DECODE_MODE_PREFIX);  // no decode for any digits
    max7219_send_to_all_chips(chain, MAX7219_SCAN_LIMIT_PREFIX | 0b111);  // display all digits
    if(intensity > 0b1111) max7219_send_to_all_chips(chain, MAX7219_INTENSITY_PREFIX | 0b1111);
    else max7219_send_to_all_chips(chain, MAX7219_INTENSITY_PREFIX | intensity);
    for(int i=0; i<chain->size; i++) chain->buffer[i] = 0;
}


void max7219_init(max7219* crt, _pin_t din, _pin_t clk, _pin_t load, short size, _b8_t* chars, _b16_t* buffer) {
    crt->din = din;
    _OUT_INIT(din);
    _OUT_LOW(din);
    crt->clk = clk;
    _OUT_INIT(clk);
    _OUT_LOW(clk);
    crt->load = load;
    _OUT_INIT(load);
    _OUT_HIGH(load);
    crt->size = size;
    crt->chars = chars;
    for(int i=0; i<8*size; i++) chars[i] = 0;
    crt->buffer = buffer;
    for(int i=0; i<size; i++) buffer[i] = 0;
    max7219_flush(crt);
}

/*
    Update one digit per chip
    @param chain pointer to MAX7219 struct
    @param index index of the digit to update (index=4 will update digit on chip's D4 output).
    If index outside of [0, 7] range, nothing will happen.
*/
void max7219_update_digit(max7219* chain, int index) {
    if(0<=index && index<=7) {
        _b16_t prefix = (index+1) << 8;
        _b8_t postfix;
        for(int i=0; i<chain->size; i++) {
            postfix = chain->chars[i*8 + index];
            chain->buffer[i] = prefix | postfix;
        }
        max7219_flush(chain);
    }
}
