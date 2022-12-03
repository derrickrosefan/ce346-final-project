#include "pattern.h"

node_t *pattern_linked_list_primary = NULL;
node_t *pattern_linked_list_secondary = NULL;

void add_to_pattern(const unsigned char *audio_sample, uint16_t audio_sample_size)
{
    printf("adding to pattern!\n");
    node_t *sound = (node_t *)malloc(sizeof(node_t));
    sound->audio_sample = audio_sample;
    sound->audio_sample_size = audio_sample_size;
    sound->timer_value = get_stopwatch_time();
    list_insert_sorted(sound, &pattern_linked_list_primary);
}

void play_pattern()
{
    if (list_get_first(&pattern_linked_list_primary) && list_get_first(&pattern_linked_list_primary)->timer_value < get_stopwatch_time())
    {
        node_t *sound = list_remove_first(&pattern_linked_list_primary);
        list_insert_sorted(sound, &pattern_linked_list_secondary);
        play_audio_sample(sound->audio_sample, sound->audio_sample_size);
    }
}

bool is_pattern_empty()
{
    return list_get_first(&pattern_linked_list_primary) == NULL;
}

void swap_pattern()
{
    pattern_linked_list_primary = pattern_linked_list_secondary;
    pattern_linked_list_secondary = NULL;
}

void clear_pattern()
{
    clear_list(&pattern_linked_list_primary);
    clear_list(&pattern_linked_list_secondary);
}