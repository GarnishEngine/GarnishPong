#include <garnish_app.hpp>

#include <shared.hpp>
#include <Utility/camera.hpp>

int main() {
    std::string assetPath = "../3rdParty/GarnishEngine/";
    garnish::App::CreateInfo createInfo{ };
    createInfo.assetPath = assetPath;
    garnish::App app{ createInfo };

    // TODO asset path should be automatically added here (maybe)
    uint32_t meshHandle = app.get_render_device()->setup_mesh(assetPath + "Models/viking_room.obj");

    uint32_t texHandle = app.get_render_device()->load_texture(assetPath + "Textures/viking_room.png");

    auto vikingRoom = app.get_controller().create_entity_with_components(
        garnish::Renderable{.meshHandle = meshHandle, .texHandle = texHandle}
    );

    app.get_controller().create_entity_with_components(garnish::Camera());

    app.run();
}