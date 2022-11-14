#include <audio.h>
#include <clap.h>

int main(void)
{
  audio_init();
  while (true)
  {
    play_audio_sample(clap, clap_size);
  }
}
