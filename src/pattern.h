#pragma once

#include <stdlib.h>
#include "timer_linked_list.h"
#include "audio.h"
#include "stopwatch.h"

void add_to_pattern(const unsigned char *audio_sample, uint16_t audio_sample_size);
void play_pattern();
bool is_pattern_empty();
void swap_pattern();
void clear_pattern();
