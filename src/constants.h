// Audio samples must be at 44100 Hz
#define SAMPLING_FREQUENCY 44100
// Audio sample max value is 255 - we store each audio value as char
#define SAMPLE_MAX_VALUE 255
// Buffer size for PWM is 32000 bytes (audio samples longer than 32000 bytes will be truncated)
#define BUFFER_SIZE 32000
#define NRF_CLOCK_FREQUENCY 16000000