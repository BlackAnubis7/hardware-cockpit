// TEST FILE

#include "controller.h"

dm13a ch;
dm13a ch2;
_b16_t data[2];
_b16_t data2[1];

void setup() {
    dm13a_init(&ch, 44, 46, 42, NULL, 1, data);
    dm13a_init(&ch2, 44, 46, 30, NULL, 1, data2);
    delay(1000);
}

void loop() {
    dm13a_setbits(&ch, 0, (_b16_t)0b0000000000101000);
    dm13a_flush(&ch);
    dm13a_setbits(&ch2, 0, (_b16_t)0b0000000000011100);
    dm13a_flush(&ch2);
    delay(1000);

    dm13a_setbits(&ch, 0, (_b16_t)0b0000000000110000);
    dm13a_flush(&ch);
    dm13a_setbits(&ch2, 0, (_b16_t)0b0000000000000000);
    dm13a_flush(&ch2);
    delay(1000);

}
