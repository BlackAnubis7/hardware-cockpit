#include <stdint.h>

// Type of labels that define GPIO pins (usually numbers)
#define _pin_t uint8_t

// High pin state
#define _HIGH HIGH

// Low pin state
#define _LOW LOW

// Initialise output pin with number __pin__
#define _OUT_INIT(__pin__) pinMode(__pin__, OUTPUT)

// Set __pin__ state to __state__ (should be _HIGH or _LOW)
#define _OUT_SET(__pin__, __state__) digitalWrite(__pin__, __state__)

// Set state of __pin__ under condition - _HIGH if __cond__ is true, _LOW if false
#define _OUT_IF(__pin__, __cond__) _OUT_SET(__pin__, (__cond__ ? _HIGH : _LOW))

// Set state of __pin__ to _HIGH
#define _OUT_HIGH(__pin__) _OUT_SET(__pin__, _HIGH)

// Set state of __pin__ to _LOW
#define _OUT_LOW(__pin__) _OUT_SET(__pin__, _LOW)

// Sleep __millis__ milliseconds
#define _SLEEP_MS(__millis__) delay(__millis__)

// Sleep __micros__ microseconds
#define _SLEEP_MICROS(__micros__) delayMicroseconds(__micros__)


// Initialise input pin with number __pin__
#define _IN_INIT(__pin__) pinMode(__pin__, INPUT)

// Get __pin__ state (will be be _HIGH or _LOW)
#define _IN_GET(__pin__) digitalRead(__pin__)

// Get 0 or 1, depending on __pin__ state (0 if _LOW, 1 if _HOW)
#define _IN_GETBIN(__pin__) (_IN_GET(__pin__) == _HIGH ? 1 : 0)


// Type to carry analog read values
#define _analog_t uint16_t

// Default maximum value returned by analog read
#define _ANALOG_MAX 1023

// Read analog input (max value returned by this function is platform-dependent [1023 for Arduino])
#define _ANALOG_GET(__pin__) analogRead(__pin__)


// // Get number of allocated displays
// #define _MAX_SIZE(__ptr__) {__ptr__->size;}

// // Initialise __size__ MAX7219 chips, and puts into pointer __ptr__ to _MAX_TYPE variable
// #define _MAX_INIT(__ptr__, __din__, __clk__, __load__, __size__) { \
//     __ptr__->lc = LedControl(__din__, __clk__, __load__, __size__); \
//     __ptr__->size = __size__;}

// // Clear one MAX's display
// #define _MAX_CLEAR(__ptr__, __index__) {__ptr__->lc.clearDisplay(__index__);}

// // Shutdown one MAX's display
// #define _MAX_SHUTDOWN(__ptr__, __index__) {__ptr__->lc.shutdown(__index__, 1);}

// // Wake up one MAX's display
// #define _MAX_WAKE(__ptr__, __index__) {__ptr__->lc.clearDisplay(__index__, 0);}

// // Set one MAX's display intensity __intens__ (from 0 to 15)
// #define _MAX_INTENSITY(__ptr__, __index__, __intens__) \
//     {__ptr__->lc.setIntensity(__index__, __intens__);}

// // Set display's character
// #define _MAX_CHAR(__ptr__, __index__, __digno__, __char__, __dot__) \
//     {__ptr__->lc.setChar(__index__, __digno__, __char__, __dot__);}
