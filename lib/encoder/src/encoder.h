/**
 * Simple Encoder class for dc motor's encoder
 *
 * Peter Borkuti
 */


#ifndef ENCODER_H
#define ENCODER_H

/**
 * DC Motor control class
 *
 */
class Encoder {
private:
    /**
     * millis() function
     * You can easily test the Encoder class without Arduino.h
     * with using a custom millis function
     */
    unsigned long (*func_millis)();

    void (*func_stop)();
    /**
     * number of counts of the encoder
     */
    volatile unsigned long counter;
    /**
     * Sum of time in millisecs between every encoder ticks
     */
    volatile unsigned long sumtime;
    /**
     * Last tick's time in millisecs
     */
    volatile unsigned long time;

    unsigned long resetTime;

    unsigned long restartTime;

    unsigned long lastRestartTime;

    volatile bool isCountDown;

    long downCounter;

public:

    Encoder(unsigned long(*millisFunction)(), unsigned long reset_time = 1000, unsigned long restart_time = 1000);

    /**
     * count method must be called whenever the encoder ticks
     * Use this function with interrupts, like this
     *  Encoder e1(millis);
     *
     *  void e1Count() {
     *     e1.count();
     *  }
     *
     */
    void count();

    void countDown(long counterInit, void (*stopFunction)());

    void checkReset();
    void checkRestart();

    void reset();
    void restart();

    char * log(char * msg) const;


    float getTicksPerTime(float defaultValue = 0);

    //int getState() const;
    static const int ENCODER_STOP;
    static const int ENCODER_RUN;
};

#endif
