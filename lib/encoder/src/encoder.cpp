#include "encoder.h"
#include <string.h>
#include <stdio.h>

const int Encoder::ENCODER_STOP = 0;
const int Encoder::ENCODER_RUN = 1;

Encoder::Encoder(unsigned long(*millisFunction)(), unsigned long reset_time, unsigned long restart_time) {
    func_millis = millisFunction;
    resetTime = reset_time;
    restartTime = restart_time;
    isCountDown = false;
    reset();
}

void Encoder::countDown(long counterInit, void(*stopFunction)()) {
    func_stop = stopFunction;
    downCounter = counterInit;
    isCountDown = true;
}

void Encoder::count() {
    unsigned long m = func_millis();
    sumtime += m - time;
    counter++;
    if (isCountDown) {
        downCounter--;
        if (downCounter <= 0) {
            isCountDown = false;
            func_stop();
        }
    }
    time = m;
}

void Encoder::reset() {
    counter = 0;
    sumtime = 0;
    time = func_millis();
    lastRestartTime = time;
}

void Encoder::restart() {
    sumtime = sumtime / 3;
    counter = counter / 3;
    time = func_millis();
    lastRestartTime = time;
}

void Encoder::checkReset() {
    if ((resetTime <= 0) || isCountDown) {
        return;
    }

    unsigned long m = func_millis();
    if ((m - time) > resetTime) {
        reset();
    }
}

void Encoder::checkRestart() {
    if ((restartTime <= 0) || isCountDown) {
        return;
    }
    unsigned long m = func_millis();
    if ((m - lastRestartTime) > restartTime) {
        restart();
    }
}

char * Encoder::log(char * msg) const {
    char buf[100];
    /** The right way of converting unsigned long to char*:
    const int n = snprintf(NULL, 0, "%lu", ulong_value);
    assert(n > 0);
    char buf[n+1];
    int c = snprintf(buf, n+1, "%lu", ulong_value);
    assert(buf[n] == '\0');
    assert(c == n);
    */
    strcpy(msg, "counter:");
    sprintf(buf, "%lu", counter);
    strcat(msg, buf);
    strcat(msg, "dcounter:");
    sprintf(buf, "%lu", downCounter);
    strcat(msg, buf);
    strcat(msg, ", sumtime:");
    sprintf(buf, "%lu", sumtime);
    strcat(msg, buf);
    strcat(msg, ", time:");
    sprintf(buf, "%lu", time);
    strcat(msg, buf);

    return msg;
}

float Encoder::getTicksPerTime(float defaultValue) {
    checkReset();
    checkRestart();

    if (counter != 0) {
        return (float)sumtime / (float)counter;
    }
    else {
        return defaultValue;
    }
}
