#include <recorder.h>

/*
void record_pattern(button stop_button)
{
    while (!is_button_pressed(stop_button)) {
        node_t *sound = (node_t *)malloc(sizeof(node_t));
        if (is_button_pressed(MPC_BUTTON_1)) {
            sound->audio_sample = hi_hat;
            sound->audio_sample_size = hi_hat_size;
        }
        
        sound->timer_value = stopwatch.get_stopwatch_time();
        list_insert_sorted(sound);
    }
}
*/

void play_pattern()
{
    if (list_get_first() && list_get_first()->timer_value < get_stopwatch_time())
    {
        node_t *sound = list_remove_first();
        play_audio_sample(sound->audio_sample, sound->audio_sample_size);
        free(sound);
    };
}

