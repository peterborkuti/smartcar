#include <Arduino.h>
#include "hyundairemote.h"

const int HyundaiRemote::RECEIVED_NOTHING = 0;
const int HyundaiRemote::STOP = 1;
const int HyundaiRemote::LEFT = 2;
const int HyundaiRemote::RIGHT = 3;
const int HyundaiRemote::FORWARD = 4;
const int HyundaiRemote::BACKWARD = 5;

HyundaiRemote::HyundaiRemote(int pin):irrecv(pin) {
}

int HyundaiRemote::decodeValue(unsigned int button) {
    if ((button == 21) || (button == 22)) { // RIGHT,LEFT
      //I changed LEFT/RIGHT because originally it boosts the appropriate
      //motor, however, robot turns to the opposite direction
      return ((button == 21) ? LEFT : RIGHT);
    }
    if ((button == 18) || (button == 19)) { // FW, BW
      return((button == 18) ? FORWARD : BACKWARD);
    }
    if ((button == 37) || (button == 38)) { // tune-slower
      return((button == 37) ? LEFT : RIGHT);
    }
    if (button == 20 || button == 51) { //OK or exit
      return STOP;
    }

    return RECEIVED_NOTHING;
}

int HyundaiRemote::getValue() {
    int v = RECEIVED_NOTHING;

    if (irrecv.decode(&results)) {
        unsigned int button = (results.value) % 256;
        irrecv.resume(); // resume receiver

        v = decodeValue(button);
    }

    return v;
}

void HyundaiRemote::enable() {
    irrecv.enableIRIn();
}
