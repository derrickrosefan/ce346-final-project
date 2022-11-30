#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <microbit_v2.h>

typedef struct Button Button;

struct Button
{
    uint16_t row;
    uint16_t col;
};

#define ROW_1 EDGE_P0
#define ROW_2 EDGE_P1
#define COL_1 EDGE_P2
#define COL_2 EDGE_P3
#define COL_3 EDGE_P4

void input_init(void);
bool is_button_pressed(Button);