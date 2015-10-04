#include "core/world.hpp"
#include "components/basic.hpp"
#include "components/render.hpp"
#include "components/player.hpp"
#include "systems/events.hpp"
#include "systems/player.hpp"
#include "systems/rendering.hpp"
#include "sdlwrap/surface.hpp"
#include <assert.h>
#include "core/logging.hpp"

namespace core{
World::World(Application *papplication):papplication(papplication){
    LOG(INFO) << "Constructing world";
    systems.add<systems::PositionPrinter>();
    systems.add<systems::RenderSystem>();
    systems.add<systems::EventSystem>();
    systems.add<systems::PlayerControlSystem>();
    systems.configure();
    auto prender = systems.system<systems::RenderSystem>();
}

//TODO : Consider adding another layer of abstraction between "systems" and logic?
// The goal would be to be less tied to entityx
void World::init(){

    LOG(INFO) << "Initializing world";
    LOG(INFO) << "Initializing systems";
    auto prender = systems.system<systems::RenderSystem>();
    assert (prender != nullptr);
    prender->init();
    auto pevent = systems.system<systems::EventSystem>();
    assert (pevent != nullptr);
    pevent->init(papplication);
    LOG(INFO) << "Initialized systems";

    LOG(INFO) << "Initializing entity ";
    auto ptex = prender->load_texture("resources/testimage.png");
    entityx::Entity entity = entities.create();
    entity.assign<components::Spacial>(100.0, 100.0, 200.0, 200.0, 0.0, 80, 0.0);
    entity.assign<components::RenderTexture>(ptex);
    entity.assign<components::Player>();
    LOG(INFO) << "Initialized entity ";
    LOG(INFO) << "Initialized world";
}

void World::update(entityx::TimeDelta dt) {
    // Events should be handled first (I think?)
    systems.update<systems::EventSystem>(dt);
    systems.update<systems::PlayerControlSystem>(dt);
    systems.update<systems::PositionPrinter>(dt);
}
void World::render(entityx::TimeDelta dt) {
    systems.update<systems::RenderSystem>(dt);

}
}
