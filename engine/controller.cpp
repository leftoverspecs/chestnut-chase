#include "controller.h"

#include <stdexcept>

namespace engine {

Controller::Controller(int id)
  : controller(SDL_GameControllerOpen(id)),
    axis{0},
    buttons{0}
{
    if (controller == nullptr) {
        throw std::runtime_error(SDL_GetError());
    }
    SDL_AddEventWatch(Controller::event_filter, this);
}

Controller::~Controller() {
    SDL_DelEventWatch(Controller::event_filter, this);
    SDL_GameControllerClose(controller);
}

int Controller::is_button_a_pressed() const {
    return buttons[SDL_CONTROLLER_BUTTON_A];
}

int Controller::get_right_trigger() const {
    return axis[SDL_CONTROLLER_AXIS_TRIGGERRIGHT];
}

void Controller::rumble(Uint16 low_freq, Uint16 high_freq, Uint32 duration) const {
    SDL_GameControllerRumble(controller, low_freq, high_freq, duration);
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
