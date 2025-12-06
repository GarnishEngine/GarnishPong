#include <garnish_app.hpp>

#include <shared.hpp>
#include <Utility/camera.hpp>

#include <geometry.hpp>

int main() {
    std::string engineAssetPath = "../3rdParty/GarnishEngine/";
    garnish::App::CreateInfo createInfo{ };
    createInfo.assetPath = engineAssetPath;
    garnish::App app{ createInfo };

    uint32_t meshHandle = app.get_render_device()->setup_mesh(createUnitCubeGeometry());

    // TODO need to sort out these paths
    uint32_t texHandle = app.get_render_device()->load_texture(engineAssetPath + "../../assets/white-square.png");

    auto vikingRoom = app.get_controller().create_entity_with_components(
        garnish::Renderable{.meshHandle = meshHandle, .texHandle = texHandle}
    );

    app.get_controller().create_entity_with_components(garnish::Camera());

    app.run();
}