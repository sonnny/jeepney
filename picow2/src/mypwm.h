//mypwm.h

#ifndef MYPWM_H
#define MYPWM_H

#include <stdio.h>
#include "hardware/pwm.h"
#include "hardware/clocks.h"

#define MOTOR_IN1 16
#define MOTOR_IN2 17
#define PWM_FREQ_MOTOR 1000

uint slice_num;

void init_pwm(){
gpio_init(MOTOR_IN1);
gpio_set_dir(MOTOR_IN1,GPIO_OUT);
gpio_init(MOTOR_IN2);
gpio_set_dir(MOTOR_IN2,GPIO_OUT);
gpio_put(MOTOR_IN1,0);
gpio_put(MOTOR_IN2,0);
gpio_set_function(MOTOR_IN1,GPIO_FUNC_PWM);
gpio_set_function(MOTOR_IN2,GPIO_FUNC_PWM);
slice_num = pwm_gpio_to_slice_num(MOTOR_IN1);
pwm_config config = pwm_get_default_config();
float clock_div = (float)clock_get_hz(clk_sys) / (PWM_FREQ_MOTOR * 200);
pwm_config_set_clkdiv(&config,clock_div);
pwm_config_set_wrap(&config,200);
pwm_init(slice_num,&config,true);}

void stop_motor(){
pwm_set_chan_level(slice_num,PWM_CHAN_A,0);
pwm_set_chan_level(slice_num,PWM_CHAN_B,0);}

void forward_motor(uint duty){
printf("forward\n");
pwm_set_chan_level(slice_num,PWM_CHAN_A,duty);
pwm_set_chan_level(slice_num,PWM_CHAN_B,0);}

void reverse_motor(uint duty){
pwm_set_chan_level(slice_num,PWM_CHAN_A,0);
pwm_set_chan_level(slice_num,PWM_CHAN_B,duty);}

#endif
