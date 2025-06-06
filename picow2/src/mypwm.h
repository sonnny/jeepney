//mypwm.h
//https://github.com/sirfonzie/INF2004_LAB4/blob/main/l298n.c

#ifndef MYPWM_H
#define MYPWM_H

#include <stdio.h>
#include "hardware/pwm.h"

#define MOTOR_IN1 16
#define MOTOR_IN2 17
#define PWM_FREQ_MOTOR 1000

uint slice_num;

void stop_motor(){
pwm_set_chan_level(slice_num,PWM_CHAN_A,0);
pwm_set_chan_level(slice_num,PWM_CHAN_B,0);}

void init_pwm(){
gpio_set_function(MOTOR_IN1,GPIO_FUNC_PWM);
gpio_set_function(MOTOR_IN2,GPIO_FUNC_PWM);
slice_num = pwm_gpio_to_slice_num(MOTOR_IN1);//same slice for in1 and in2 
float clock_freq = 125000000.0f; //default pico frequency
uint32_t divider = clock_freq / (PWM_FREQ_MOTOR * 200);//200 is full resolution
pwm_set_clkdiv(slice_num,divider);
pwm_set_wrap(slice_num,199);//resolution 0 - 199
stop_motor();
pwm_set_enabled(slice_num,true);}

void forward_motor(uint duty){//duty range 0-199
pwm_set_chan_level(slice_num,PWM_CHAN_A,duty);
pwm_set_chan_level(slice_num,PWM_CHAN_B,0);}

void reverse_motor(uint duty){//duty range 0-199
pwm_set_chan_level(slice_num,PWM_CHAN_A,0);
pwm_set_chan_level(slice_num,PWM_CHAN_B,duty);}

#endif
