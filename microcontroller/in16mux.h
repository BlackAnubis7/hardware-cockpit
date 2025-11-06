#include "arduino_defs.h"
#include "misc_defs.h"

typedef struct in16mux {
    _pin_t addr0;  // address' LSB
    _pin_t addr1;
    _pin_t addr2;
    _pin_t addr3;  // address' MSB
    short size;  // number of multiplexers with common address pins
    _pin_t* din;  // DataIn pins (array of length equal or larger to size)
    _b16_t* state;  // LSB is input at IN0, MSB is IN15; state[n] stores input from din[n] (array of length equal or larger to size)
} in16mux;

void in16mux_init(in16mux* mux, _pin_t addr0, _pin_t addr1, _pin_t addr2, _pin_t addr3, short size, _pin_t* din, _b16_t* state) {
    _OUT_INIT(addr0);
    mux->addr0 = addr0;
    _OUT_INIT(addr1);
    mux->addr1 = addr1;
    _OUT_INIT(addr2);
    mux->addr2 = addr2;
    _OUT_INIT(addr3);
    mux->addr3 = addr3;
    mux->size = size;
    mux->din = din;
    mux->state = state;
    for(int i=0; i<size; i++) {
        _IN_INIT(din[i]);
    }
}

/*
    FOR INTERNAL USE
    Read current inputs from all multiplexers and add it to given addresses in "mux.state" using bitwise OR.
    "addr" parameter does not affect from which input data will be read, it only affects where it is going to be saved.
    Due to bitwise OR usage, if "mux.state" has "1" on given position, it will remain "1" even if read data is "0".
    addr=0 refers to LSB and addr=15 to MSB - it should equal to current set address.
    If addr > 15, this function will not do anything (should never be used that way).
*/
void in16mux_read_current(in16mux* mux, unsigned short addr) {
    for(int i=0; i<mux->size; i++) {
        mux->state[i] |= _IN_GETBIN(mux->din[i]) << addr;
    }
}

/*
    Update mux.state based on all inputs in multiplexers. WARNING: disconnected inputs may have unpredictably 0 or 1
*/
void in16mux_update_state(in16mux* mux) {
    for(int i=0; i<mux->size; i++) mux->state[i] = 0;
    // using Gray code to optimize
    _OUT_SET(mux->addr0, _LOW);
    _OUT_SET(mux->addr1, _LOW);
    _OUT_SET(mux->addr2, _LOW);
    _OUT_SET(mux->addr3, _LOW);   // 0000
    in16mux_read_current(mux, 0);
    _OUT_SET(mux->addr0, _HIGH);  // 0001
    in16mux_read_current(mux, 1);
    _OUT_SET(mux->addr1, _HIGH);  // 0011
    in16mux_read_current(mux, 3);
    _OUT_SET(mux->addr0, _LOW);   // 0010
    in16mux_read_current(mux, 2);
    _OUT_SET(mux->addr2, _HIGH);  // 0110
    in16mux_read_current(mux, 6);
    _OUT_SET(mux->addr0, _HIGH);  // 0111
    in16mux_read_current(mux, 7);
    _OUT_SET(mux->addr1, _LOW);   // 0101
    in16mux_read_current(mux, 5);
    _OUT_SET(mux->addr0, _LOW);   // 0100
    in16mux_read_current(mux, 4);
    _OUT_SET(mux->addr3, _HIGH);  // 1100
    in16mux_read_current(mux, 12);
    _OUT_SET(mux->addr0, _HIGH);  // 1101
    in16mux_read_current(mux, 13);
    _OUT_SET(mux->addr1, _HIGH);  // 1111
    in16mux_read_current(mux, 15);
    _OUT_SET(mux->addr0, _LOW);   // 1110
    in16mux_read_current(mux, 14);
    _OUT_SET(mux->addr2, _LOW);   // 1010
    in16mux_read_current(mux, 10);
    _OUT_SET(mux->addr0, _HIGH);  // 1011
    in16mux_read_current(mux, 11);
    _OUT_SET(mux->addr1, _LOW);   // 1001
    in16mux_read_current(mux, 9);
    _OUT_SET(mux->addr0, _LOW);   // 1000
    in16mux_read_current(mux, 8);
}
