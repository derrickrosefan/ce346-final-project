#include <audio.h>

static uint16_t samples[BUFFER_SIZE] = {0};
static const float COUNTERTOP = (float)NRF_CLOCK_FREQUENCY / (float)SAMPLING_FREQUENCY;
static const nrfx_pwm_t PWM_INST = NRFX_PWM_INSTANCE(0);

void pwm_init(void)
{
    nrfx_pwm_config_t pwm_config = {
        .output_pins = {SPEAKER_OUT, NRFX_PWM_PIN_NOT_USED, NRFX_PWM_PIN_NOT_USED, NRFX_PWM_PIN_NOT_USED},
        .base_clock = NRF_PWM_CLK_16MHz,
        .count_mode = NRF_PWM_MODE_UP,
        .top_value = COUNTERTOP,
        .load_mode = NRF_PWM_LOAD_COMMON,
        .step_mode = NRF_PWM_STEP_AUTO};
    nrfx_pwm_init(&PWM_INST, &pwm_config, NULL);
}

void audio_init()
{
    pwm_init();
}

static uint16_t min(uint16_t num1, uint16_t num2)
{
    return num1 < num2 ? num1 : num2;
}

void play_audio_sample(const unsigned char *audio_sample, uint16_t audio_sample_size)
{

    for (uint16_t i = 0; i < min(BUFFER_SIZE, audio_sample_size); i++)
    {
        samples[i] = (uint16_t)((float)audio_sample[i] / (float)SAMPLE_MAX_VALUE) * COUNTERTOP;
    }
    nrf_pwm_sequence_t pwm_sequence = {
        .values.p_common = samples,
        .length = min(BUFFER_SIZE, audio_sample_size),
        .repeats = 0,
        .end_delay = 0,
    };
    nrfx_pwm_simple_playback(&PWM_INST, &pwm_sequence, 1, NRFX_PWM_FLAG_STOP);
}