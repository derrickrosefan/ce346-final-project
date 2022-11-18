#include <audio.h>
#include <clap.h>

#include "app_timer.h"
#include "nrf_delay.h"
#include "nrfx_saadc.h"
#include "microbit_v2.h"

int main(void)
{
  printf("starting our application\n");
  audio_init();
  nrf_gpio_cfg_output(EDGE_P0);
  nrf_gpio_pin_set(EDGE_P0);
  nrf_gpio_cfg_input(EDGE_P1, NRF_GPIO_PIN_PULLDOWN);
  while (true)
  {
    if (nrf_gpio_pin_read(EDGE_P1))
    {
      printf("playing audio on button press\n");
      play_audio_sample(clap, clap_size);
    }
    nrf_delay_ms(200);
  }
}
