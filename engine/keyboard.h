#pragma once

#include <SDL2/SDL_events.h>

#include <array>

namespace engine {

class Keyboard {
public:
    Keyboard();
    ~Keyboard();

    Keyboard(const Keyboard &) = delete;
    Keyboard(Keyboard &&) = delete;
    Keyboard &operator = (const Keyboard &) = delete;
    Keyboard &operator = (Keyboard &&) = delete;

    int is_left_pressed() const { return left; }
    int is_right_pressed() const { return right; }
    int is_space_pressed() const { return space; }
    int is_a_pressed() const { return a; }
    int is_d_pressed() const { return d; }
    int is_lshift_pressed() const { return lshift; }
private:
    int space;
    int left;
    int right;
    int a;
    int d;
    int lshift;

    int filter_events(SDL_Event *event);
    static int event_filter(void *userdata, SDL_Event *event);
};

}
