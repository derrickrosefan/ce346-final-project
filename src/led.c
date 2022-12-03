#include "led.h"

APP_TIMER_DEF(led_timer);
static uint32_t current_row = 0;
uint32_t row_leds[] = {LED_ROW1, LED_ROW2, LED_ROW3, LED_ROW4, LED_ROW5};
uint32_t col_leds[] = {LED_COL1, LED_COL2, LED_COL3, LED_COL4, LED_COL5};
bool led_states[5][5] = {false};

uint32_t row_curr = 0;
uint32_t offset = 0;

bool IS_PLAY_LED_ON = false;
bool IS_RECORD_LED_ON = false;

void toggle_led_pattern()
{
  nrf_gpio_pin_clear(row_leds[current_row]);
  current_row = (current_row + 1) % 5;
  for (uint32_t j = 0; j < 5; j++)
  {
    nrf_gpio_pin_write(col_leds[j], !led_states[current_row][j]);
  }
  nrf_gpio_pin_set(row_leds[current_row]);
}

void record_play_led_init()
{
  nrf_gpio_pin_dir_set(PLAY_LED, NRF_GPIO_PIN_DIR_OUTPUT);
  nrf_gpio_pin_dir_set(RECORD_LED, NRF_GPIO_PIN_DIR_OUTPUT);
}

void led_matrix_init()
{
  app_timer_init();
  app_timer_create(&led_timer, APP_TIMER_MODE_REPEATED, toggle_led_pattern);
  app_timer_start(led_timer, 30, NULL);
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

void draw_char(u_char in)
{
  // printf("Drawing Char\n");
  for (int row = 0; row < 5; row++)
  {
    for (int col = 0; col < 5; col++)
    {
      led_states[row][col] = (font[in][row] >> col) & 1;
    }
  }
}

void toggle_record_led()
{
  if (IS_RECORD_LED_ON)
  {
    nrf_gpio_pin_clear(RECORD_LED);
  }
  else
  {
    nrf_gpio_pin_set(RECORD_LED);
  }
  IS_RECORD_LED_ON = !IS_RECORD_LED_ON;
}

void toggle_play_led()
{
  if (IS_PLAY_LED_ON)
  {
    nrf_gpio_pin_clear(PLAY_LED);
  }
  else
  {
    nrf_gpio_pin_set(PLAY_LED);
  }
  IS_PLAY_LED_ON = !IS_PLAY_LED_ON;
}
