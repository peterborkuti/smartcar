/**
 * Decoding Hyundai Remote Controller's data for simple smart car
 * Peter Borkuti
 */


#ifndef HYUNDAIREMOTE_H
#define HYUNDAIREMOTE_H

#include <Arduino.h>
#include <IRremote.h>

class HyundaiRemote {
private:
    int RECV_PIN;

    IRrecv irrecv;

    decode_results results;

    int decodeValue(unsigned int);


public:
    HyundaiRemote(int);
    int getValue();

    /**
     * enableIRIn does not work when calling it from constructor
     */
    void enable();

    static const int RECEIVED_NOTHING;
    static const int FORWARD;
    static const int LEFT;
    static const int RIGHT;
    static const int BACKWARD;
    static const int STOP;

};

#endif
