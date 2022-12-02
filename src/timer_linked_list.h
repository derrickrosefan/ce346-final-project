#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "nrf.h"

// -- List types

// a node within a linked list
typedef struct node_t
{
    const unsigned char *audio_sample;
    uint16_t audio_sample_size;

    // *** Do not edit below this line ***
    float timer_value;

    // pointer to next node in list. Do not change this field for a node or you
    //  will break the list
    struct node_t *next;
} node_t;

// -- List functions

// clears list
void clear_list(void);

// Insert node at the correct place in the linked list based on increasing
//  node->timer_value. The node_t must be malloc'd before being added.
void list_insert_sorted(node_t *node);

// Return the first node in the linked list without removing it. This value may
//  be NULL if the list is empty.
node_t *list_get_first();

// Remove the first node from the linked list and return it. This value may be
//  NULL if the list is empty.
node_t *list_remove_first();

// Remove the specified node from the linked list. Note that the memory for the
//  node is NOT automatically freed.
void list_remove(node_t *node);

// Print the linked list for debugging.
void list_print();
