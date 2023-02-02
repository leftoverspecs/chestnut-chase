#pragma once

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_gamecontroller.h>

#include <array>

namespace engine {

class Controller {
public:
    explicit Controller(int id);
    ~Controller();

    int is_button_a_pressed() const;
    int get_right_trigger() const;
    void rumble(Uint16 low_freq, Uint16 high_freq, Uint32 duration) const;

    static int get_num_controllers();
private:
    SDL_GameController *controller;
    std::array<int, 8> axis;
    std::array<int, 32> buttons;

    int filter_events(SDL_Event *event);

    static int event_filter(void *userdata, SDL_Event *event);
};

}
