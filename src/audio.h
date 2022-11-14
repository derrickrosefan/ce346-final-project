#pragma once
#include <stdio.h>
#include <stdint.h>
#include <constants.h>
#include <nrf.h>
#include <nrf_delay.h>
#include <nrfx_pwm.h>
#include <microbit_v2.h>

void audio_init(void);
void play_audio_sample(const unsigned char *audio_sample, uint16_t audio_sample_size);