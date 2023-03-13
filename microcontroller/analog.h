#include "arduino_defs.h"
#include "misc_defs.h"

/*
    Read analog input from pin, and return the value normalised to range [0, 255]
*/
_b8_t analog_read_as_byte(_pin_t pin) {
    int aread = (int) (256.0 * (_ANALOG_GET(pin) / (_ANALOG_MAX + 1.0)));
    if(aread < 0) return 0;
    else if(aread > 0xFF) return 0xFF;
    else return (_b8_t)aread;
}
