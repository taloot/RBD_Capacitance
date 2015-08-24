// Arduino Capacitance Library - A real-time library for determining relative capacitance
// Copyright 2015 Alex Taujenis
// MIT License

#ifndef CAPACITANCE_H
#define CAPACITANCE_H

#include <Arduino.h>

class Capacitance {
  public:
    Capacitance(int send_pin, int receive_pin); // constructor
    void setSampleSize(int size); // how many readings to take per sample
    void start();                 // begin a sample and take many readings: alias of _startSampling()
    void update();                // keep this class updating in real-time
    bool isFinished();            // if all readings have been taken for this sample: alias of _doneSampling()
    unsigned long getValue();     // the sum of readings divided by the sample size: alias of _getAverage()
  private:
    int _send_pin;
    int _receive_pin;
    int _sample_size  = 100;       // how many readings should be taken for one sample
    int _sample_count = 0;         // how many readings have been taken for the current sample
    bool _sampling    = false;     // true if in the middle of a sample
    bool _waiting     = false;     // true if in the middle of a reading
    bool _reading     = false;     // true if finished with one reading
    unsigned long _sample_sum = 0; // temp value that holds the sum of all readings for this sample
    unsigned long _start;          // the time in microseconds that a reading was started
    unsigned long _total_value;    // the time in microseconds how long a reading took
    unsigned long _total_average;  // the average time in microseconds for the last sample_size number of readings
    unsigned long _getValue();     // returns the value of the single reading when done
    unsigned long _getAverage();   // returns the sum of readings divided by the sample size
    void _startSampling();         // begin a sample and take many readings
    bool _doneSampling();          // returns true if all readings have been taken for this sample
    void _startReading();          // kick off the process to take a single reading
    bool _doneReading();           // returns true if finished taking a single reading
    void _takeReading();           // perform the actual reading (pin charge and discharge)
    void _sample();                // perform many readings
};

#endif