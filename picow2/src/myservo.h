//myservo.h
#ifndef MYSERVO_H
#define MYSERVO_H

#include <stdlib.h>
#include "hardware/pwm.h"

#define SERVO_PIN 19
#define PWM_FREQ 50
#define MIN_PULSE_WIDTH_US 1000
#define MAX_PULSE_WIDTH_US 2100
#define PULSE_RANGE_US (MAX_PULSE_WIDTH_US - MIN_PULSE_WIDTH_US)

float pulse_width_us;
uint32_t duty_cycle_servo;
uint channel_servo;
uint slice_num_servo;

void servo_center(){
pulse_width_us = MIN_PULSE_WIDTH_US + (PULSE_RANGE_US/2.0f);
duty_cycle_servo = (uint32_t)(pulse_width_us * 10000 / (1000000.0f/PWM_FREQ));
pwm_set_chan_level(slice_num_servo, channel_servo, duty_cycle_servo);
}


void init_servo(){
gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM);
slice_num_servo = pwm_gpio_to_slice_num(SERVO_PIN);
channel_servo = pwm_gpio_to_channel(SERVO_PIN);

float clock_div = 125000000.0f / (PWM_FREQ * 10000); // Example clock divider
pwm_set_clkdiv(slice_num_servo, clock_div);
pwm_set_wrap(slice_num_servo, 10000); // Example wrap value
pwm_set_enabled(slice_num_servo, true);
servo_center();
}

void servo_left(){
pulse_width_us = MIN_PULSE_WIDTH_US;
duty_cycle_servo = (uint32_t)(pulse_width_us * 10000 / (1000000.0f/PWM_FREQ));
pwm_set_chan_level(slice_num_servo, channel_servo, duty_cycle_servo);
}

void servo_right(){
pulse_width_us = MAX_PULSE_WIDTH_US;
duty_cycle_servo = (uint32_t)(pulse_width_us * 10000 / (1000000.0f/PWM_FREQ));
pwm_set_chan_level(slice_num_servo, channel_servo, duty_cycle_servo);
}

#endif
