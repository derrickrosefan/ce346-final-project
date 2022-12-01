#include <audio.h>
#include <input.h>
#include <bass.h>
#include <kick.h>
#include <snare.h>
#include <clap.h>
#include <hi_hat.h>
#include <recorder.h>

#include <nrf_delay.h>
#include <microbit_v2.h>
#include <stopwatch.h>

Button MPC_BUTTON_1 = {ROW_1, COL_1};
Button MPC_BUTTON_2 = {ROW_1, COL_2};
Button MPC_BUTTON_3 = {ROW_1, COL_3};
Button MPC_BUTTON_4 = {ROW_2, COL_1};
Button RECORD_BUTTON = {ROW_2, COL_2}; // 5
Button PLAY_BUTTON = {ROW_2, COL_3};   // 6

// void create_pattern()
// {
//   for (uint16_t i = 0; i < 30; i++)
//   {
//     node_t *sound = (node_t *)malloc(sizeof(node_t));
//     sound->audio_sample = hi_hat;
//     sound->audio_sample_size = hi_hat_size;
//     sound->timer_value = 0.25 * (float)i;
//     list_insert_sorted(sound);
//   }
//   for (uint16_t i = 0; i < 5; i++)
//   {
//     node_t *sound = (node_t *)malloc(sizeof(node_t));
//     sound->audio_sample = clap;
//     sound->audio_sample_size = clap_size;
//     sound->timer_value = 1.0 * (float)i + 0.05;
//     list_insert_sorted(sound);
//   }
// }

int main(void)
{
  printf("starting our application\n");
  audio_init();
  input_init();
  stopwatch_init();
  create_pattern();

  while (true)
  {
    play_pattern();

    if (is_button_pressed(MPC_BUTTON_1))
    {
      play_audio_sample(clap, clap_size);
      nrf_delay_ms(100);
    }

    if (is_button_pressed(MPC_BUTTON_2))
    {
      play_audio_sample(hi_hat, hi_hat_size);
      nrf_delay_ms(100);
    }

    if (is_button_pressed(MPC_BUTTON_3))
    {
      play_audio_sample(snare, snare_size);
      nrf_delay_ms(100);
    }

    if (is_button_pressed(MPC_BUTTON_4))
    {
      play_audio_sample(kick, kick_size);
      nrf_delay_ms(100);
    }
    nrf_delay_ms(50);
  }
}
