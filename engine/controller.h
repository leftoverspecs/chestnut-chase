#pragma once

#include "keyboard.h"

#include <SDL_events.h>
#include <SDL_gamecontroller.h>

#include <array>
#include <optional>

namespace engine {

class Controller {
public:
    explicit Controller(int id);
    ~Controller();

    Controller(const Controller &) = delete;
    Controller(Controller &&) = delete;
    Controller &operator = (const Controller &) = delete;
    Controller &operator = (Controller &&) = delete;

    int is_button_a_pressed() const;
    int is_button_left_pressed() const;
    int is_button_right_pressed() const;

    int get_right_trigger() const;

    void rumble(Uint16 low_freq, Uint16 high_freq, Uint32 duration) const;

    static int get_num_controllers();
private:
    SDL_GameController *controller;
    std::optional<Keyboard> keyboard;
    std::array<int, 8> axis;
    std::array<int, 32> buttons;

    int filter_events(SDL_Event *event);

    static int event_filter(void *userdata, SDL_Event *event);
};

}
