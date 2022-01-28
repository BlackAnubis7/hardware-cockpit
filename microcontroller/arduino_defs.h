#include "LedControl.h"

// High pin state
#define _HIGH HIGH

// Low pin state
#define _LOW LOW

// Initialise output pin with number __pin__
#define _OUT_INIT(__pin__) {pinMode(__pin__, OUTPUT);}

// Set __pin__ state to __state__ (should be _HIGH or _LOW)
#define _OUT_SET(__pin__, __state__) {digitalWrite(__pin__, __state__);}

// Set state of __pin__ under condition - _HIGH if __cond__ is true, _LOW if false
#define _OUT_IF(__pin__, __cond__) {_OUT_SET(__pin__, (__cond__ ? _HIGH : _LOW));}

// Set state of __pin__ to _HIGH
#define _OUT_HIGH(__pin__) {_OUT_SET(__pin__, _HIGH);}

// Set state of __pin__ to _LOW
#define _OUT_LOW(__pin__) {_OUT_SET(__pin__, _LOW);}


// Get number of allocated displays
#define _MAX_SIZE(__ptr__) {__ptr__->size;}

// Initialise __size__ MAX7219 chips, and puts into pointer __ptr__ to _MAX_TYPE variable
#define _MAX_INIT(__ptr__, __din__, __clk__, __load__, __size__) { \
    __ptr__->lc = LedControl(__din__, __clk__, __load__, __size__); \
    __ptr__->size = __size__;}

// Clear one MAX's display
#define _MAX_CLEAR(__ptr__, __index__) {__ptr__->lc.clearDisplay(__index__);}

// Shutdown one MAX's display
#define _MAX_SHUTDOWN(__ptr__, __index__) {__ptr__->lc.shutdown(__index__, 1);}

// Wake up one MAX's display
#define _MAX_WAKE(__ptr__, __index__) {__ptr__->lc.clearDisplay(__index__, 0);}

// Set one MAX's display intensity __intens__ (from 0 to 15)
#define _MAX_INTENSITY(__ptr__, __index__, __intens__) \
    {__ptr__->lc.setIntensity(__index__, __intens__);}

// Set display's character
#define _MAX_CHAR(__ptr__, __index__, __digno__, __char__, __dot__) \
    {__ptr__->lc.setChar(__index__, __digno__, __char__, __dot__);}


// Initialise __size__ DM13A chips into __ptr__ (pointer to _DM13_TYPE variable)
#define _DM13_INIT(__ptr__, __dai__, __dck__, __lat__, __en__, __size__) { \
    __ptr__->dai = __dai__; \
    __ptr__->dck = __dck__; \
    __ptr__->lat = __lat__; \
    __ptr__->en = __en__; \
    __ptr__->size = __size__;}

// Get DM13A chain size
#define _DM13_SIZE(__ptr__) {__ptr__->size;}

// Flush bits into DM13A chain
#define _DM13_FLUSH(__ptr__, __dai__, __dck__, __lat__, __en__) { \
    _OUT_IF(__ptr__->dai, __dat__); \
    _OUT_IF(__ptr__->dck, __dck__); \
    _OUT_IF(__ptr__->lat, __lat__); \
    _OUT_IF(__ptr__->en, __en__);}


// DM13A controller type
typedef struct {int dai, int dck, int lat, int en, int size} _DM13_TYPE;

// MAX7219 controller type
typedef struct {LedControl lc, int size} _MAX_TYPE;