#include <audio.h>
#include <clap.h>

int main(void)
{
  audio_init();
  while (true)
  {
    play_audio_sample(clap, clap_size);
    nrf_delay_us(1000000);
  }
}
