#include <stopwatch.h>

static nrfx_timer_t PATTERN_PLAYBACK_STOPWATCH = NRFX_TIMER_INSTANCE(0);

void stopwatch_handler(nrf_timer_event_t event, void *context)
{
}

void stopwatch_init()
{
    nrfx_timer_config_t stopwatch_config = {
        .frequency = NRF_TIMER_FREQ_1MHz,
        .mode = NRF_TIMER_MODE_TIMER,
        .bit_width = NRF_TIMER_BIT_WIDTH_32,
        .interrupt_priority = 4,
        .p_context = NULL};
    nrfx_timer_init(&PATTERN_PLAYBACK_STOPWATCH, &stopwatch_config, stopwatch_handler);
    nrfx_timer_enable(&PATTERN_PLAYBACK_STOPWATCH);
}

float get_stopwatch_time(void)
{
    return (float)nrfx_timer_capture(&PATTERN_PLAYBACK_STOPWATCH, 2) / 1000000.0;
}