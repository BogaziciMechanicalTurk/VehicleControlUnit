/*
 * Reads Hall Effect sensors on BLDC
 * Attaches an interrupt to each Hall Effect state change
 * States change exactly once in every 1/6th of rotator turn
 * 1 wheel turn is 24 times motor rotator turn
 * 1 Rotator turn is 6 times a signal change
 */

// Interrupt pins on an Arduino Mega are; 
// 2, 3, 18, 19, 20, 21
#include "RunningMedian.h"


const byte hall_a_m1 = 2; 
const byte hall_b_m1 = 3; 
const byte hall_c_m1 = 18;

const byte hall_a_m2 = 19;
const byte hall_b_m2 = 20;
const byte hall_c_m2 = 21;

const byte ledPin = 13;


float time_before_m1=0;
float time_now_m1=0;
float elapsed_time_m1=0;

float time_before_m2=0;
float time_now_m2=0;
float elapsed_time_m2=0;

// counter for odometry
unsigned long odometry_counter_m1 = 0;
unsigned long odometry_counter_m2 = 0;

//5 time measures are read and the median value is taken for noise correction
RunningMedian time_measures_m1 = RunningMedian(5);
RunningMedian time_measures_m2 = RunningMedian(5);

int counter_m1=0,counter_m2=0;
//rev per milisecond to kilometer per hour
int rpms_to_kmh = 4860;
//rev per microsecond to kilometer per hour
int rpmicros_to_kmh = 4860000;
//one rotation of the wheel is 24 rotation of the rotator of BLDC
int rotator_to_wheel=24;

void setup() {
  pinMode(hall_a_m1, INPUT_PULLUP);
  pinMode(hall_b_m1, INPUT_PULLUP);
  pinMode(hall_c_m1, INPUT_PULLUP);

  pinMode(hall_a_m2, INPUT_PULLUP);
  pinMode(hall_b_m2, INPUT_PULLUP);
  pinMode(hall_c_m2, INPUT_PULLUP);


  attachInterrupt(hall_a_m1, measure_m1_time, CHANGE);
  attachInterrupt(hall_b_m1, measure_m1_time, CHANGE);
  attachInterrupt(hall_c_m1, measure_m1_time, CHANGE);

  attachInterrupt(hall_a_m2, measure_m2_time, CHANGE);
  attachInterrupt(hall_b_m2, measure_m2_time, CHANGE);
  attachInterrupt(hall_c_m2, measure_m2_time, CHANGE);
}

void loop() {



}

void measure_m1_time() {
  odometry_counter_m1++;
  elapsed_time_m1 = time_before_m1 - micros();
  time_before_m1=micros();
  time_measures_m1.add(elapsed_time_m1);
  counter_m1++;
  if(counter_m1%6=0){ 
    calc_m1_speed();
  }
}


int calc_m1_speed(){
  time_now_m1 = time_measures_m1.getMedian();
  speed_kmh = rpmicros_to_kmh/time_now_m1;

}

void measure_m2_time() {
  odometry_counter_m2++;
  elapsed_time_m2 = time_before_m2 - micros();
  time_before_m2=micros();
  time_measures_m2.add(elapsed_time_m2);
  counter_m2++;
  if(counter_m1%6=0){ 
    calc_m2_speed();
  }
}

int calc_m2_speed(){
  time_now_m2 = time_measures_m2.getMedian();
  speed_kmh = rpmicros_to_kmh/time_now_m2;
  
}


