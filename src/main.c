#include <audio.h>
#include <clap.h>
#include <snare.h>

#include "app_timer.h"
#include "nrf_delay.h"
#include "nrfx_saadc.h"
#include "microbit_v2.h"

// EDGE_P0 => Row 1
// EDGE_P1 => Col 1
// EDGE_P2 => Col 2

int main(void)
{
  printf("starting our application\n");
  audio_init();
  nrf_gpio_cfg_output(EDGE_P0);
  nrf_gpio_pin_set(EDGE_P0);
  nrf_gpio_cfg_input(EDGE_P1, NRF_GPIO_PIN_PULLDOWN);
  nrf_gpio_cfg_input(EDGE_P2, NRF_GPIO_PIN_PULLDOWN);
  while (true)
  {
    if (nrf_gpio_pin_read(EDGE_P1))
    {
      printf("press button 1 - play clap\n");
      play_audio_sample(clap, clap_size);
      nrf_delay_ms(1000);
    }

    if (nrf_gpio_pin_read(EDGE_P2))
    {
      printf("press button 2 - play snare\n");
      play_audio_sample(snare, snare_size);
      nrf_delay_ms(1000);
    }
    nrf_delay_ms(50);
  }
}
