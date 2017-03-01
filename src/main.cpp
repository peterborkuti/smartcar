// #ifndef UNIT_TEST // disable program main loop while unit testing in progress

#include <Arduino.h>
#include <PID_v1.h>
#include "encoder.h"
#include "hyundairemote.h"

HyundaiRemote remote(5);

double Setpoint1 = 45, Input1, Output1, Default1;
double Setpoint2 = 45, Input2, Output2, Default2;
//Specify the links and initial tuning parameters
double Kp=10.0, Ki=5.0, Kd=0.0;
PID pid1(&Input1, &Output1, &Setpoint1, Kp, Ki, Kd, REVERSE);
PID pid2(&Input2, &Output2, &Setpoint2, Kp, Ki, Kd, REVERSE);

Encoder e1(millis, 1000, 1000);
Encoder e2(millis, 1000, 1000);

bool motorIsStopped = false;

void e1Count() {
    e1.count();
}

void e2Count() {
    e2.count();
}

void motorStop() {
    Default1 = 100;
    Default2 = 100;
    Setpoint1 = 100;
    Setpoint2 = 100;
    analogWrite(6, 0);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    analogWrite(9, 0);
    pid1.SetControllerDirection(REVERSE);
    pid2.SetControllerDirection(REVERSE);
    delay(100);
    e1.reset();
    e2.reset();
}

void motorForward() {
    Default1 = 100;
    Default2 = 100;
    Setpoint1 = 20;
    Setpoint2 = 20;
    analogWrite(6, 255);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    analogWrite(9, 255);
    pid1.SetControllerDirection(REVERSE);
    pid2.SetControllerDirection(REVERSE);
    e1.reset();
    e2.reset();
    delay(100);
}

void motorStop1(){
    Default1 = 100;
    Setpoint1 = 100;
    analogWrite(6, 0);
    digitalWrite(7, LOW);
    pid1.SetControllerDirection(REVERSE);
    delay(100);
    e1.reset();
    motorIsStopped = true;
}

void motorStop2(){
    Default2 = 100;
    Setpoint2 = 100;
    digitalWrite(8, LOW);
    analogWrite(9, 0);
    pid2.SetControllerDirection(REVERSE);
    delay(100);
    e2.reset();
    motorIsStopped = true;
}

void motorBackward() {
    Default1 = 100;
    Default2 = 100;
    Setpoint1 = 20;
    Setpoint2 = 20;
    analogWrite(6, 0);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    analogWrite(9, 0);
    pid1.SetControllerDirection(DIRECT);
    pid2.SetControllerDirection(DIRECT);
    e1.reset();
    e2.reset();
    delay(100);
}

void motorLeft() {
    Default1 = 100;
    Default2 = 100;
    Setpoint1 = 20;
    Setpoint2 = 20;
    analogWrite(6, 255);
    digitalWrite(7, LOW);
    digitalWrite(8, HIGH);
    analogWrite(9, 0);
    pid1.SetControllerDirection(DIRECT);
    pid2.SetControllerDirection(REVERSE);
    e1.reset();
    e2.reset();

}

void motorRight() {
    Default1 = 100;
    Default2 = 100;
    Setpoint1 = 20;
    Setpoint2 = 20;
    analogWrite(6, 0);
    digitalWrite(7, HIGH);
    digitalWrite(8, LOW);
    analogWrite(9, 255);
    pid1.SetControllerDirection(REVERSE);
    pid2.SetControllerDirection(DIRECT);
    e1.reset();
    e2.reset();

}

void carForward(long distance) {
    Default1 = 100;
    Default2 = 100;
    Setpoint1 = 10;
    Setpoint2 = 10;
    analogWrite(6, 255);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    analogWrite(9, 255);
    pid1.SetControllerDirection(REVERSE);
    pid2.SetControllerDirection(REVERSE);
    e1.reset();
    e2.reset();
    e1.countDown(distance, motorStop1);
    e2.countDown(distance, motorStop2);
    delay(100);
}

void carBackward(long distance) {
    Default1 = 100;
    Default2 = 100;
    Setpoint1 = 10;
    Setpoint2 = 10;
    analogWrite(6, 0);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    analogWrite(9, 0);
    pid1.SetControllerDirection(DIRECT);
    pid2.SetControllerDirection(DIRECT);
    e1.reset();
    e2.reset();
    e1.countDown(distance, motorStop1);
    e2.countDown(distance, motorStop2);
    delay(100);
}

void carRight(long distance) {
    Default1 = 100;
    Default2 = 100;
    Setpoint1 = 20;
    Setpoint2 = 20;
    analogWrite(6, 0);
    digitalWrite(7, HIGH);
    digitalWrite(8, LOW);
    analogWrite(9, 255);
    pid1.SetControllerDirection(REVERSE);
    pid2.SetControllerDirection(DIRECT);
    e1.reset();
    e2.reset();
    e1.countDown(distance, motorStop1);
    e2.countDown(distance, motorStop2);
    delay(100);
}

void carLeft(long distance) {
    Default1 = 100;
    Default2 = 100;
    Setpoint1 = 20;
    Setpoint2 = 20;
    analogWrite(6, 255);
    digitalWrite(7, LOW);
    digitalWrite(8, HIGH);
    analogWrite(9, 0);
    pid1.SetControllerDirection(DIRECT);
    pid2.SetControllerDirection(REVERSE);
    e1.reset();
    e2.reset();
    e1.countDown(distance, motorStop1);
    e2.countDown(distance, motorStop2);
    delay(100);
}



void setup() {
    Serial.begin(115200);

    remote.enable();

    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);

    pinMode(2, INPUT_PULLUP);
    pinMode(3, INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(2), e1Count, RISING);
    attachInterrupt(digitalPinToInterrupt(3), e2Count, RISING);

    pid1.SetOutputLimits(0, 255.0);
    pid1.SetSampleTime(10);
    pid1.SetMode(AUTOMATIC);
    pid2.SetOutputLimits(0, 255.0);
    pid2.SetSampleTime(10);
    pid2.SetMode(AUTOMATIC);

    motorStop();

    delay(1000);

    //carRight(20);
}

void log() {
    Serial.print("(I1,O1,S1,D1):");
    Serial.print(Input1);
    Serial.print(",");
    Serial.print(Output1);
    Serial.print(",");
    Serial.print(Setpoint1);
    Serial.print(",");
    Serial.print(Default1);

    Serial.print("(I2,O2,S2,D2):");
    Serial.print(Input2);
    Serial.print(",");
    Serial.print(Output2);
    Serial.print(",");
    Serial.print(Setpoint2);
    Serial.print(",");
    Serial.println(Default2);
}

char msg[200];
uint32_t m = millis();
uint32_t pm = micros();

void act(int action) {
    if (action == remote.RECEIVED_NOTHING) return;

    Serial.println(action);

    if (action == remote.STOP) {
        motorStop();
        return;
    }

    if (action == remote.LEFT) {
        motorLeft();
        return;
    }

    if (action == remote.RIGHT) {
        motorRight();
        return;
    }

    if (action == remote.BACKWARD) {
        motorBackward();
        return;
    }
    if (action == remote.FORWARD) {
        motorForward();
        return;
    }
}

void act2(int action) {
    if (action == remote.RECEIVED_NOTHING) return;

    Serial.println(action);

    if (action == remote.STOP) {
        motorStop();
        return;
    }

    if (action == remote.LEFT) {
        carLeft(20);
        return;
    }

    if (action == remote.RIGHT) {
        carRight(20);
        return;
    }

    if (action == remote.BACKWARD) {
        carBackward(100);
        return;
    }
    if (action == remote.FORWARD) {
        carForward(100);
        return;
    }
}

void loop() {

    act2(remote.getValue());

    Input1 = e1.getTicksPerTime(Default1);
    Input2 = e2.getTicksPerTime(Default2);

    pid1.Compute();
    pid2.Compute();

    if ((millis() - m) > 100) {
        Serial.println(e1.log(msg));
        Serial.println(e2.log(msg));
        log();

        m = millis();
    }

    analogWrite(9, Output1);
    analogWrite(6, Output2);


    //Serial.println(micros() - pm);
    //pm = micros();
}
