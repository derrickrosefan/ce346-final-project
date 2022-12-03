#include <nrf_delay.h>
#include <microbit_v2.h>

#include "audio.h"
#include "input.h"
#include "bass.h"
#include "kick.h"
#include "snare.h"
#include "clap.h"
#include "hi_hat.h"
#include "timer_linked_list.h"
#include "pattern.h"
#include "led.h"
#include "stopwatch.h"

struct Button_to_Sample
{
  Button button;
  const unsigned char *audio_sample;
  uint16_t audio_size;
  char c;
};

const Button MPC_BUTTON_1 = {ROW_1, COL_1};
const Button MPC_BUTTON_2 = {ROW_1, COL_2};
const Button MPC_BUTTON_3 = {ROW_1, COL_3};
const Button MPC_BUTTON_4 = {ROW_2, COL_1};
const Button RECORD_BUTTON = {ROW_2, COL_2}; // 5
const Button PLAY_BUTTON = {ROW_2, COL_3};   // 6

const struct Button_to_Sample buttons[4] = {{MPC_BUTTON_1, clap, clap_size, 'c'},
                                            {MPC_BUTTON_2, hi_hat, hi_hat_size, 'h'},
                                            {MPC_BUTTON_3, snare, snare_size, 's'},
                                            {MPC_BUTTON_4, kick, kick_size, 'k'}};

bool IS_RECORDING = false;
bool IS_PLAYING_PATTERN = false;

int main(void)
{
  printf("starting application\n");
  audio_init();
  input_init();
  stopwatch_init();
  led_matrix_init();
  record_play_led_init();
  while (true) // Polling
  {
    for (int i = 0; i < 4; i++)
    {
      if (is_button_pressed(buttons[i].button))
      {
        if (IS_RECORDING) // if we are on RECORDING mode
        {
          add_to_pattern(buttons[i].audio_sample, buttons[i].audio_size); // add button sound to our recording
        }
        play_audio_sample(buttons[i].audio_sample, buttons[i].audio_size); // play sound
        draw_char(buttons[i].c);                                           // Draw character corresponding to sound on LED matrix
        nrf_delay_ms(100);
        draw_char(' '); // clear character from LED matrix
      }
    }

    if (is_button_pressed(PLAY_BUTTON) && !is_button_pressed(RECORD_BUTTON)) // if PLAY button is pressed (and not recording), set PLAYING boolean to true
    {
      if (!is_pattern_empty()) // If pattern linked list is empty
      {
        printf("playing pattern!\n");
        IS_PLAYING_PATTERN = true;
        toggle_play_led(); // turn on PLAY led
        reset_stopwatch();
      }
      nrf_delay_ms(100);
    }

    if (IS_PLAYING_PATTERN) // if playing pattern
    {
      play_pattern();
      if (is_pattern_empty()) // if pattern is empty, stop playing and turn LED off
      {
        printf("stop playing pattern!\n");
        swap_pattern();
        toggle_play_led();
        IS_PLAYING_PATTERN = false;
      }
    }

    if (is_button_pressed(RECORD_BUTTON)) // if record button is pressed
    {
      if (!IS_RECORDING) // if not recording, start recording (and turn on LED)
      {
        printf("starting record!\n");
        toggle_record_led();
        nrf_delay_ms(200);
        IS_PLAYING_PATTERN = false;
        reset_stopwatch();
        clear_pattern();
      }
      else
      {
        printf("stopping record!\n");
        toggle_record_led();
      }
      IS_RECORDING = !IS_RECORDING;
      nrf_delay_ms(100);
    }

    nrf_delay_ms(25);
  }
}