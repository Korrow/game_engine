#ifndef SYSTEMS_PLAYER_HPP
#define SYSTEMS_PLAYER_HPP
#include <entityx/entityx.h>
#include <string>
#include <assert.h>
#include <iostream>

namespace core{
    class Application;
}

struct SDL_KeyboardEvent;

namespace systems{

class PlayerControlSystem : public entityx::System<PlayerControlSystem>, public entityx::Receiver<PlayerControlSystem>{
public:
    PlayerControlSystem(){}

    void configure(entityx::EventManager &event_manager);

    void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;
    void receive(const SDL_KeyboardEvent &event);
private:
    float input_x, input_y;
};

}

#endif /* SYSTEMS_PLAYER_HPP */