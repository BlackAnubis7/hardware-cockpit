// TEST FILE

#include "misc_defs.h"
#include "dm13a.h"
#include "max7219.h"
#include "encoder.h"
#include "in16mux.h"
#include "analog.h"

// _b8_t SEG7_NUMBER_LIST[] = {
//     SEG7_0,
//     SEG7_1,
//     SEG7_2,
//     SEG7_3,
//     SEG7_4,
//     SEG7_5,
//     SEG7_6,
//     SEG7_7,
//     SEG7_8,
//     SEG7_9
// };

// dm13a ch;
// dm13a ch2;
// max7219 max1;
// in16mux mux;
// _b16_t data[2];
// _b16_t data2[1];
// _b8_t max_chars[16];
// _b16_t max_data[2];
// _b16_t mux_data[2];
// _pin_t mux_pins[] = {50, 38};

// encoder enc1, enc2, enc5, enc10;
// long v1=0, v2=0, v5=0, v10=0, errors=0;
// short delta;

// unsigned long long iter = 0;

void setup() {
  // in16mux_init(&mux, 46, 44, 42, 40, 2, mux_pins, mux_data);
  
//     dm13a_init(&ch, 46, 48, 52, 1, data);
//    dm13a_init(&ch2, 44, 46, 30, 1, data2);
//     dm13a_setbits(&ch, 0, (_b16_t)0b1000000000110000);
//     dm13a_flush(&ch);
//     delay(1000);
//
//    max7219_init(&max1, 46, 48, 52, 1, max_chars, max_data);
//    max7219_prepare(&max1, 7);
//
//    max_chars[3] = 0xFE;
//    max7219_update_digit(&max1, 3);
    
//    encoder_init(&enc1, 30, 31, 1, true);
//    encoder_init(&enc2, 30, 31, 1, true);
//    encoder_init(&enc5, 30, 31, 1, true);
//    encoder_init(&enc10, 30, 31, 1, true);
    Serial.begin(115200);
//    max7219_send_to_all_chips(&max1, MAX7219_NO_DISPLAY_TEST);
}

void loop() {
  delay(1000);
  Serial.println(analog_read_as_byte(A3));
//  in16mux_update_state(&mux);
//  Serial.println(mux.state[1], BIN);
  
//    if(iter % 1 == 0) encoder_update_state(&enc1);
//    if(iter % 2 == 0) encoder_update_state(&enc2);
//    if(iter % 5 == 0) encoder_update_state(&enc5);
//    if(iter % 10 == 0) encoder_update_state(&enc10);
//    if(-1000 < v1 && v1 < 1000) {
//        v1 += encoder_get_delta_and_reset(&enc1);
//        v2 += encoder_get_delta_and_reset(&enc2);
//        v5 += encoder_get_delta_and_reset(&enc5);
//        v10 += encoder_get_delta_and_reset(&enc10);
//    }
//    if(iter % 1000 == 0) {
//       Serial.print(v1);
//       Serial.print(", ");
//       Serial.print(v2);
//       Serial.print(", ");
//       Serial.print(v5);
//       Serial.print(", ");
//       Serial.print(v10);
//       Serial.println("");
//    }
//    delay(1); iter++;
//    for(int i=0; i<6; i++) {
//        max7219_send_to_all_chips(&max1, 0x0200 | (0b10 << i));
//        max7219_setbits(&max1, 1, 0x0200 | (0b10 << i));
//        max7219_flush(&max1);
//        Serial.print(max1.buffer[0]);
//        Serial.print(" ");
//        Serial.println(max1.buffer[1]);
//         delay(100);
//         max_chars[0] = SEG7_NUMBER_LIST[(iter)%10];
//         max_chars[1] = SEG7_NUMBER_LIST[(iter)%10];
//         max_chars[2] = SEG7_NUMBER_LIST[(iter)%10];
//         max_chars[3] = SEG7_NUMBER_LIST[(iter)%10];
//         max7219_update_digit(&max1, 0);
//         max7219_update_digit(&max1, 1);
//         max7219_update_digit(&max1, 2);
//         max7219_update_digit(&max1, 3);
//         digitalWrite(48, HIGH);
//         digitalWrite(48, LOW);
//         digitalWrite(48, HIGH);
//         digitalWrite(48, LOW);
//         digitalWrite(48, HIGH);
//         digitalWrite(48, LOW);
//     }
//    max_chars[8+2] = SEG7_NUMBER_LIST[(iter++)%10];
//    max7219_update_digit(&max1, 2);
//    iter++;
//     dm13a_setbits(&ch, 0, (_b16_t)0b1101110101000000);
//     dm13a_flush(&ch);
//    dm13a_setbits(&ch2, 0, (_b16_t)0b0000000000011100);
//    dm13a_flush(&ch2);
//     delay(1000);

//    dm13a_setbits(&ch, 0, (_b16_t)0b1000000000110000);
//    dm13a_flush(&ch);
//    dm13a_setbits(&ch, 0, (_b16_t)0b1101110101000000);
//    dm13a_flush(&ch);
//    dm13a_setbits(&ch2, 0, (_b16_t)0b0000000000011100);
//    dm13a_flush(&ch2);
//     delay(1000);

}
