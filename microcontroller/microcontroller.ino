// TEST FILE

#include "dm13a.h"

dm13a ch;
dm13a ch2;
_b16_t data[2];
_b16_t data2[1];

void setup() {
    dm13a_init(&ch, 46, 48, 52, 1, data);
//    dm13a_init(&ch2, 44, 46, 30, 1, data2);
    dm13a_setbits(&ch, 0, (_b16_t)0b1000000000110000);
    dm13a_flush(&ch);
    delay(1000);
}

void loop() {
    dm13a_setbits(&ch, 0, (_b16_t)0b1101110101000000);
    dm13a_flush(&ch);
//    dm13a_setbits(&ch2, 0, (_b16_t)0b0000000000011100);
//    dm13a_flush(&ch2);
    delay(1000);

//    dm13a_setbits(&ch, 0, (_b16_t)0b1000000000110000);
//    dm13a_flush(&ch);
//    dm13a_setbits(&ch, 0, (_b16_t)0b1101110101000000);
//    dm13a_flush(&ch);
//    dm13a_setbits(&ch2, 0, (_b16_t)0b0000000000011100);
//    dm13a_flush(&ch2);
    delay(1000);

}
