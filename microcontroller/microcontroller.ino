// TEST FILE

#include "controller.h"

dm13a ch;
_b16_t data[2];

void setup() {
    dm13a_init(&ch, 44, 46, 42, 40, 2, data);
    delay(1000);
}

void loop() {
    dm13a_setbits(&ch, 1, (_b16_t)0b0000000000010100);
    dm13a_flush(&ch);
    delay(1000);

    dm13a_setbit(&ch, 27, 0);
    dm13a_setbit(&ch, 13, 1);
    dm13a_flush(&ch);
    delay(1000);

    dm13a_setbits(&ch, 1, (_b16_t)0b0000000000011000);
    dm13a_setbit(&ch, 13, 0);
    dm13a_flush(&ch);
    delay(2000);

}
