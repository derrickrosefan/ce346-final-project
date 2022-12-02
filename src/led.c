#include "nrf_gpio.h"
#include "microbit_v2.h"
#include "led.h"
#include "font.h"

uint32_t row_leds[] = {LED_ROW1, LED_ROW2, LED_ROW3, LED_ROW4, LED_ROW5};
uint32_t col_leds[] = {LED_COL1, LED_COL2, LED_COL3, LED_COL4, LED_COL5};
bool led_states[5][5] = {false};

uint32_t row_curr = 0;
uint32_t offset = 0;

void led_matrix_init()
{
  row_curr = 0;
  offset = 0;
  for (int i = 0; i < 5; i++)
  {
    for (int j = 0; j < 5; j++)
    {
      led_states[i][j] = false;
    }
  }

  // initialize row pins
  for (int i = 0; i < 5; i++)
  {
    nrf_gpio_pin_dir_set(row_leds[i], NRF_GPIO_PIN_DIR_OUTPUT);
    nrf_gpio_pin_clear(row_leds[i]);
  }

  // initialize col pins
  for (int i = 0; i < 5; i++)
  {
    nrf_gpio_pin_dir_set(col_leds[i], NRF_GPIO_PIN_DIR_OUTPUT);
    nrf_gpio_pin_set(col_leds[i]);
  }
}

void draw_char(char in)
{
  printf("Drawing Char\n");
  for (int row = 0; row < 5; row++)
  {
    for (int col = 0; col < 5; col++)
    {
      led_states[row][col] = (font[in][row] >> col) & 1;
    }
  }
}
