#include "arduino_defs.h"
#include "misc_defs.h"

/*
    Type: AABBCCD0
    - AA = step (0 if 4/cycle, 1 if 2/cycle, 2 if 1/cycle)
    - BB = phase (one of states on which a detent is placed)
    - CC = sequence (0=0123, 1=0132, 2=0312)
    - D = reverse (1 if sequence is reversed)
    - 01100110 = 2 detents per cycle (on 2 and 1); counter increased on 2>3>1>0

    Prevstate: AAAAAABB
    - AAAAAA = physical detent delta (0x20 means none, 0x1E two detents down, 0x23 two detents up etc.)
    - BB = previous pins' state (0b10 means pin1 was up and pin2 was down)
*/
typedef struct encoder {
    _pin_t pin1;
    _pin_t pin2;
    _b8_t type;
    _s8_t prevstate;
    short delta;
} encoder;

/*
    Turn two digital inputs to one number from range [0, 3].
    Both pins need to be initialised as inputs already.
*/
_b8_t _merge_two_inputs(_pin_t pin1, _pin_t pin2) {
    int in1 = _IN_GETBIN(pin1);
    int in2 = _IN_GETBIN(pin2);
    return in1 << 1 | in2;
}

short _get_encoder_state_index(short sequence, _b8_t state) {
    if(state == 0) return 0;
    else if(state == 1) return (sequence == 2) ? 2 : 1;
    else if(state == 2) return (sequence == 0) ? 2 : 3;
    else return 3 - sequence;
}

/*
    @param enc
    @param pin1
    @param pin2
    @param step {0, 1, 2}
    @param reverse true or false
    @param phase {0, 1, 2, 3}
    @param sequence {0, 1, 2}
*/
void encoder_init(encoder* enc, _pin_t pin1, _pin_t pin2, short step, bool reverse=false, short sequence=1, short phase=0) {
    _IN_INIT(pin1);
    _IN_INIT(pin2);
    enc->pin1 = pin1;
    enc->pin2 = pin2;
    _b8_t step_ = (step & 0b11) << 6;
    _b8_t phase_ = (phase & 0b11) << 4;
    _b8_t seq_ = (sequence & 0b11) << 2;
    _b8_t rev_ = (reverse & 0b1) << 1;
    enc->type = step_ | phase_ | seq_ | rev_;
    enc->prevstate = 0x80 | _merge_two_inputs(pin1, pin2);
    enc->delta = 0;
}

int encoder_update_state(encoder* enc) {
    int returnCode = 0;
    short step = enc->type >> 6 & 0b11;
    short phase = enc->type >> 4 & 0b11;
    short seq = enc->type >> 2 & 0b11;
    bool reverse = enc->type >> 1 & 0b1;
    _b8_t currState = _merge_two_inputs(enc->pin1, enc->pin2);
    _b8_t prevState = enc->prevstate & 0b11;
    if(currState != prevState) {
        _b8_t detentDelta = enc->prevstate & 0b11111100;  // not shifted - 0x80 means no change (instead of 0x20)

        short shift = _get_encoder_state_index(seq, phase);
        short curr = _get_encoder_state_index(seq, currState);
        short prev = _get_encoder_state_index(seq, prevState);
        
        curr = (curr - shift + 4) % 4;
        prev = (prev - shift + 4) % 4;

        if(curr == (prev+1)%4) detentDelta += (reverse ? -0b100 : 0b100);
        else if(curr == (prev-1)%4) detentDelta += (reverse ? 0b100 : -0b100);
        else returnCode = 0x100 | currState << 4 | prevState;  // wrong state change detected (misconfiguration, or rotation was too fast)
            

        if(detentDelta != 0x80) {
            bool isDetent = step == 0 || curr == 0 || step == 1 && curr == 2;
            if(isDetent) {
                enc->delta += (detentDelta > 0x80 ? 1 : -1);
                detentDelta = 0x80;
            }
        }

        enc->prevstate = detentDelta & 0b11111100 | currState & 0b11;
    }
    return returnCode;  // even if an error occurred, the output might still be correct
}

short encoder_get_delta_and_reset(encoder* enc) {
    short ret = enc->delta;
    enc->delta = 0;
    return ret;
}
