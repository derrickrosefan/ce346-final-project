#include <input.h>

void input_init()
{
    nrf_gpio_cfg_output(ROW_1);
    nrf_gpio_cfg_output(ROW_2);
    nrf_gpio_cfg_input(COL_1, NRF_GPIO_PIN_PULLDOWN);
    nrf_gpio_cfg_input(COL_2, NRF_GPIO_PIN_PULLDOWN);
    nrf_gpio_cfg_input(COL_3, NRF_GPIO_PIN_PULLDOWN);
}

bool is_button_pressed(Button button)
{
    nrf_gpio_pin_clear(ROW_1);
    nrf_gpio_pin_clear(ROW_2);
    nrf_gpio_pin_set(button.row);
    return nrf_gpio_pin_read(button.col);
};