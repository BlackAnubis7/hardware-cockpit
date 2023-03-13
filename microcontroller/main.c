#include "misc_defs.h"
#include "dm13a.h"
#include "max7219.h"
#include "encoder.h"
#include "in16mux.h"
#include "analog.h"

_pin_t* simpleIns;
_pin_t* simpleOuts;
_pin_t* analogIns;
in16mux* in16muxs;
dm13a* dm13as;
encoder* encoders;
max7219* max7219s;

int simpleIns_n=0, simpleOuts_n=0, analogIns_n=0, in16muxs_n=0, dm13as_n=0, encoders_n=0, max7219s_n=0;

void allocate_top_level() {
    // numbers of particular components should already be initialised, otherwise these elements will not be detected
    simpleIns = (_pin_t*) calloc(simpleIns_n, sizeof(_pin_t));
    simpleOuts = (_pin_t*) calloc(simpleIns_n, sizeof(_pin_t));
    analogIns = (_pin_t*) calloc(simpleIns_n, sizeof(_pin_t));
    in16muxs = (in16mux*) calloc(simpleIns_n, sizeof(in16mux));
    dm13as = (dm13a*) calloc(simpleIns_n, sizeof(dm13a));
    encoders = (encoder*) calloc(simpleIns_n, sizeof(encoder));
    max7219s = (max7219*) calloc(simpleIns_n, sizeof(max7219));
}
