#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <app_timer.h>
#include <nrf_gpio.h>
#include <microbit_v2.h>
#include "led.h"
#include "font.h"

#define RECORD_LED EDGE_P16
#define PLAY_LED EDGE_P15

// Initialize the LED matrix display
void led_matrix_init(void);
void record_play_led_init(void);
void toggle_record_led(void);
void toggle_play_led(void);
void draw_char(u_char in);
