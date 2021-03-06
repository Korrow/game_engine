#include "core/world.hpp"
#include "core/config.hpp"
#include "components/basic.hpp"
#include "components/render.hpp"
#include "components/pathfinding.hpp"
#include "components/player.hpp"
#include "systems/events.hpp"
#include "systems/pathfinding.hpp"
#include "systems/player.hpp"
#include "systems/rendering.hpp"
#include "sdlwrap/surface.hpp"
#include <assert.h>
#include "core/logging.hpp"

namespace core{
World::World(Application *papplication, Config *pconfig):papplication(papplication), pconfig(pconfig){
    LOG(INFO) << "Constructing world";
    systems.add<systems::PositionPrinter>();
    systems.add<systems::RenderSystem>(pconfig);
    systems.add<systems::EventSystem>(papplication);
    systems.add<systems::CameraSystem>();
    systems.add<systems::PlayerControlSystem>();
    systems.add<systems::PathfindingSystem>();
    systems.configure();

    LOG(INFO) << "Initializing world";
    LOG(INFO) << "Initializing systems";
    auto prender = systems.system<systems::RenderSystem>();
    assert (prender != nullptr);
    auto pevent = systems.system<systems::EventSystem>();
    pevent->load_config(pconfig);
    assert (pevent != nullptr);
    LOG(INFO) << "Initialized systems";

    LOG(INFO) << "Initializing entity ";
    auto ptex = prender->load_texture("resources/testimage.png");
    entityx::Entity entity = entities.create();
    entity.assign<components::Spacial>(100.0, 100.0, 200.0, 200.0, 0.0, 0.0, 0.0);
    entity.assign<components::RenderTexture>(ptex);
    entity.assign<components::RenderData>(1);
    entity.assign<components::Player>();
    entity.assign<components::RenderCameraTarget>();

    auto ptex2 = prender->load_texture("resources/testimage.png");
    entityx::Entity ai = entities.create();
    ai.assign<components::Spacial>(100.0, 100.0, 200.0, 200.0, 0.0, 0.0, 0.0);
    ai.assign<components::RenderTexture>(ptex2);
    ai.assign<components::RenderData>(1);
    ai.assign<components::Pathfinding>(true, 242.0, 400.0);

    auto camera = entities.create();
    camera.assign<components::Spacial>(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    camera.assign<components::RenderCamera>();
    LOG(INFO) << "Initialized Camera";

    auto pbackground = prender->load_texture("resources/testbackground.png");
    entityx::Entity background = entities.create();
    background.assign<components::Spacial>(0.0, 0.0, 5120.0, 5120.0, 0.0, 0.0, 0.0);
    background.assign<components::RenderTexture>(pbackground);
    background.assign<components::RenderData>(0);
    LOG(INFO) << "Initialized Background";
}

//TODO : Consider adding another layer of abstraction between "systems" and logic?
// The goal would be to be less tied to entityx

void World::update(entityx::TimeDelta dt) {
    // Events should be handled first (I think?)
    systems.update<systems::EventSystem>(dt);
    systems.update<systems::PlayerControlSystem>(dt);
    systems.update<systems::PositionPrinter>(dt);
    systems.update<systems::PathfindingSystem>(dt);
}
void World::render(entityx::TimeDelta dt) {
    systems.update<systems::CameraSystem>(dt);
    systems.update<systems::RenderSystem>(dt);

}
}
