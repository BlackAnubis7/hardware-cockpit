#import "controller.h"

/**
    Initialise new dm13a struct
    @param crt pointer to DM13A struct where it will be initialised
    @param dai DataIn identifier of macrodefined type _pin_t
    @param dck DataClock identifier of macrodefined type _pin_t
    @param lat Latch identifier of macrodefined type _pin_t
    @param size number of DM13A chips in the chain
    @param buffer array of b16_t elements; array's length has to be at least "size" (elements with indices equal or greater than "size" will remain unused)
*/
void dm13a_init(dm13a* crt, _pin_t dai, _pin_t dck, _pin_t lat, int size, b16_t* buffer) {
    crt->dai = dai;
    _OUT_INIT(dai);
    _OUT_SET_LOW(dai);
    crt->dck = dck;
    _OUT_INIT(dck);
    _OUT_SET_LOW(dck);
    crt->lat = lat;
    _OUT_INIT(lat);
    _OUT_SET_LOW(lat);
    crt->size = size;
    crt->buffer = buffer;
    for(int i=0; i<size; i++) buffer[i] = 0;
    dm13a_flush(crt);
}

/**
    Flush buffer into DM13A chain
    @param chain pointer to DM13A struct
*/
void dm13a_flush(dm13a* chain) {
    _OUT_SET_LOW(chain->lat);
    for(int c = chain->size-1; c>=0; c--) {
        for(int i=0; i<=32; i++) {  // 32 will create the last clock edge
            if(i%2 == 0) {
                _OUT_SET_HIGH(chain->dck);
            } else {
                _OUT_SET_LOW(chain->dck);
                _OUT_IF(chain->dai, (chain->buffer[c] >> i/2) % 2 == 1);
            }
        }
    }
    _OUT_SET_LOW(chain->dck);
    _OUT_SET_HIGH(chain->lat);
    _SLEEP_MS(1);  // without that delay, correct work is not guaranteed
}
