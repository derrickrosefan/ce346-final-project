#include <audio.h>
#include <input.h>
#include <bass.h>
#include <kick.h>
#include <snare.h>
#include <clap.h>
#include <hi_hat.h>
#include <timer_linked_list.h>
#include <stdlib.h>

#include <nrf_delay.h>
#include <microbit_v2.h>
#include <stopwatch.h>

Button MPC_BUTTON_1 = {ROW_1, COL_1};
Button MPC_BUTTON_2 = {ROW_1, COL_2};
Button MPC_BUTTON_3 = {ROW_1, COL_3};
Button MPC_BUTTON_4 = {ROW_2, COL_1};
Button RECORD_BUTTON = {ROW_2, COL_2}; // 5
Button PLAY_BUTTON = {ROW_2, COL_3};   // 6

bool IS_RECORDING = false;
bool IS_PLAYING_PATTERN = false;

void add_to_pattern(const unsigned char *audio_sample, uint16_t audio_sample_size)
{
  printf("adding to patttern right now!\n");
  node_t *sound = (node_t *)malloc(sizeof(node_t));
  sound->audio_sample = audio_sample;
  sound->audio_sample_size = audio_sample_size;
  sound->timer_value = get_stopwatch_time();
  list_insert_sorted(sound);
}

void play_pattern()
{
  if (list_get_first() && list_get_first()->timer_value < get_stopwatch_time())
  {
    node_t *sound = list_remove_first();
    play_audio_sample(sound->audio_sample, sound->audio_sample_size);
    // no need to free, just restart timer when get to end of linked list.
    free(sound);
  }
}

int main(void)
{
  printf("starting our application\n");
  audio_init();
  input_init();
  stopwatch_init();

  while (true)
  {
    if (is_button_pressed(MPC_BUTTON_1))
    {
      if (IS_RECORDING)
      {
        add_to_pattern(clap, clap_size);
      }
      play_audio_sample(clap, clap_size);
    }

    if (is_button_pressed(MPC_BUTTON_2))
    {
      if (IS_RECORDING)
      {
        add_to_pattern(hi_hat, hi_hat_size);
      }
      play_audio_sample(hi_hat, hi_hat_size);
    }

    if (is_button_pressed(MPC_BUTTON_3))
    {
      if (IS_RECORDING)
      {
        add_to_pattern(snare, snare_size);
      }
      play_audio_sample(snare, snare_size);
    }

    if (is_button_pressed(MPC_BUTTON_4))
    {
      if (IS_RECORDING)
      {
        add_to_pattern(kick, kick_size);
      }
      play_audio_sample(kick, kick_size);
    }

    if (is_button_pressed(PLAY_BUTTON) && !is_button_pressed(RECORD_BUTTON) && list_get_first())
    {
      printf("playing pattern!\n");
      IS_PLAYING_PATTERN = true;
      reset_stopwatch();
    }

    if (IS_PLAYING_PATTERN)
    {
      play_pattern();
    }

    if (is_button_pressed(RECORD_BUTTON))
    {
      if (!IS_RECORDING)
      {
        printf("starting record!\n");
        nrf_delay_ms(200);
        IS_PLAYING_PATTERN = false;
        reset_stopwatch();
        clear_list();
      }
      else
      {
        printf("stopping record!\n");
      }
      IS_RECORDING = !IS_RECORDING;
    }

    nrf_delay_ms(150);
  }
}