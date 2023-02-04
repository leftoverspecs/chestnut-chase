#include "controller.h"

#include <stdexcept>

namespace engine {

Controller::Controller(int id)
  : controller(SDL_GameControllerOpen(id)),
    axis{0},
    buttons{0}
{
    if (controller == nullptr) {
        keyboard.emplace();
    } else {
        SDL_AddEventWatch(Controller::event_filter, this);
    }
}

Controller::~Controller() {
    if (!keyboard) {
        SDL_DelEventWatch(Controller::event_filter, this);
        SDL_GameControllerClose(controller);
    }
}

int Controller::is_button_a_pressed() const {
    if (!keyboard) {
        return buttons[SDL_CONTROLLER_BUTTON_A];
    } else {
        return keyboard->is_space_pressed();
    }
}

int Controller::is_button_left_pressed() const {
    if (!keyboard) {
        return buttons[SDL_CONTROLLER_BUTTON_DPAD_LEFT];
    } else {
        return keyboard->is_left_pressed();
    }
}

int Controller::is_button_right_pressed() const {
    if (!keyboard) {
        return buttons[SDL_CONTROLLER_BUTTON_DPAD_RIGHT];
    } else {
        return keyboard->is_right_pressed();
    }
}

int Controller::get_right_trigger() const {
    if (!keyboard) {
        return axis[SDL_CONTROLLER_AXIS_TRIGGERRIGHT];
    } else {
        return keyboard->is_lshift_pressed();
    }
}

void Controller::rumble(Uint16 low_freq, Uint16 high_freq, Uint32 duration) const {
    if (!keyboard) {
        SDL_GameControllerRumble(controller, low_freq, high_freq, duration);
    }
}

int Controller::get_num_controllers() {
    return SDL_NumJoysticks();
}

int Controller::filter_events(SDL_Event *event) {
    switch (event->type) {
        case SDL_CONTROLLERAXISMOTION: {
            const SDL_ControllerAxisEvent a = event->caxis;
            if (SDL_GameControllerFromInstanceID(a.which) == controller) {
                axis[a.axis] = a.value;
            }
            break;
        }
        case SDL_CONTROLLERBUTTONDOWN:
        case SDL_CONTROLLERBUTTONUP: {
            const SDL_ControllerButtonEvent b = event->cbutton;
            if (SDL_GameControllerFromInstanceID(b.which) == controller) {
                if (b.state == SDL_PRESSED) {
                    ++buttons[b.button];
                } else if (b.state == SDL_RELEASED) {
                    buttons[b.button] = 0;
                }
            }
            break;
        }
    }
    return 0;
}

int Controller::event_filter(void *userdata, SDL_Event *event) {
    Controller *const self = static_cast<Controller *>(userdata);
    return self->filter_events(event);
}

}
