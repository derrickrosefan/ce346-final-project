#include <audio.h>
#include <input.h>
#include <bass.h>
#include <kick.h>
#include <snare.h>
#include <clap.h>
#include <led.h>
#include <hi_hat.h>
#include <timer_linked_list.h>
#include <pattern.h>

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

int main(void)
{
  printf("starting our application\n");
  audio_init();
  input_init();
  stopwatch_init();
  led_matrix_init();

  while (true) // Polling
  {
    // draw_char('c');
    if (is_button_pressed(MPC_BUTTON_1)) // if button1 is pressed
    {
      if (IS_RECORDING) // if we are on RECORDING mode
      {
        add_to_pattern(clap, clap_size); // add button1 sound (clap) to recording
      }
      play_audio_sample(clap, clap_size); // play clap sound
      // draw_char('c');
      nrf_delay_ms(100);
    }

    if (is_button_pressed(MPC_BUTTON_2)) // if button 2 is pressed
    {
      if (IS_RECORDING) // if we are on RECORDING mode
      {
        add_to_pattern(hi_hat, hi_hat_size);
      }
      play_audio_sample(hi_hat, hi_hat_size);
      nrf_delay_ms(100);
    }

    if (is_button_pressed(MPC_BUTTON_3))
    {
      if (IS_RECORDING)
      {
        add_to_pattern(snare, snare_size);
      }
      play_audio_sample(snare, snare_size);
      nrf_delay_ms(100);
    }

    if (is_button_pressed(MPC_BUTTON_4))
    {
      if (IS_RECORDING)
      {
        add_to_pattern(kick, kick_size);
      }
      play_audio_sample(kick, kick_size);
      nrf_delay_ms(100);
    }

    if (is_button_pressed(PLAY_BUTTON) && !is_button_pressed(RECORD_BUTTON)) // if PLAY button is pressed (and not recording), set PLAYING boolean to true
    {
      if (is_pattern_empty())
      {
        swap_pattern();
      }
      if (!is_pattern_empty())
      {
        printf("playing pattern!\n");
        IS_PLAYING_PATTERN = true;
        reset_stopwatch();
      }
      nrf_delay_ms(100);
    }

    if (IS_PLAYING_PATTERN) //
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
        clear_pattern();
      }
      else
      {
        printf("stopping record!\n");
        // list_print(&pattern_linked_list_primary);
      }
      IS_RECORDING = !IS_RECORDING;
      nrf_delay_ms(100);
    }

    nrf_delay_ms(25);
  }
}