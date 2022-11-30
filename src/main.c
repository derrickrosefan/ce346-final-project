#include <audio.h>
#include <input.h>
#include <clap.h>
#include <hi_hat.h>

#include <app_timer.h>
#include <nrf_delay.h>
#include <microbit_v2.h>

Button MPC_BUTTON_1 = {ROW_1, COL_1};
Button MPC_BUTTON_2 = {ROW_1, COL_2};
Button MPC_BUTTON_3 = {ROW_1, COL_3};
Button MPC_BUTTON_4 = {ROW_2, COL_1};

int main(void)
{
  printf("starting our application\n");
  audio_init();
  input_init();
  while (true)
  {
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
      play_audio_sample(hi_hat, hi_hat_size);
      nrf_delay_ms(100);
    }
    nrf_delay_ms(50);
  }
}
