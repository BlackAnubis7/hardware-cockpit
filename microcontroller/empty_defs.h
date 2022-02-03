// Type of labels that define GPIO pins (usually numbers)
#define _pin_t int

// High pin state
#define _OUT_HIGH NULL

// Low pin state
#define _OUT_LOW NULL

// Initialise output pin with number __pin__
#define _OUT_INIT(__pin__) {}

// Set __pin__ state to __state__ (should be _OUT_HIGH or _OUT_LOW)
#define _OUT_SET(__pin__, __state__) {}

// Set state of __pin__ under condition - _OUT_HIGH if __cond__ is true, _OUT_LOW if false
#define _OUT_IF(__pin__, __cond__) {_OUT_SET(__pin__, (__cond__ ? _OUT_HIGH : _OUT_LOW));}

// Set state of __pin__ to _OUT_HIGH
#define _OUT_SET_HIGH(__pin__) {_OUT_SET(__pin__, _OUT_HIGH);}

// Set state of __pin__ to _OUT_LOW
#define _OUT_SET_LOW(__pin__) {_OUT_SET(__pin__, _OUT_LOW);}

// Sleep __millis__ milliseconds
#define _SLEEP_MS(__millis__) {}

