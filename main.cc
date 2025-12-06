#include <garnish_app.hpp>

#include <shared.hpp>
#include <Utility/camera.hpp>

#include <geometry.hpp>

int main() {
    std::string engineAssetPath = "../3rdParty/GarnishEngine/";
    garnish::App::CreateInfo createInfo{ };
    createInfo.assetPath = engineAssetPath;
    garnish::App app{ createInfo };

    uint32_t unitCube = app.get_render_device()->setup_mesh(createUnitCubeGeometry());

    // TODO need to sort out these paths
    uint32_t whiteTexture = app.get_render_device()->load_texture(engineAssetPath + "../../assets/white-square.png");

    auto ball = app.get_controller().create_entity_with_components(
        garnish::Renderable{.meshHandle = unitCube, .texHandle = whiteTexture}
    );

    auto leftPaddle = app.get_controller().create_entity_with_components(
        garnish::Renderable{.meshHandle = unitCube, .texHandle = whiteTexture},
        garnish::Transform{ .position = glm::vec3{ -2.0f, 0.0f, 0.0f } }
    );

    auto rightPaddle = app.get_controller().create_entity_with_components(
        garnish::Renderable{.meshHandle = unitCube, .texHandle = whiteTexture},
        garnish::Transform{ .position = glm::vec3{ 2.0f, 0.0f, 0.0f } }
    );

    app.get_controller().create_entity_with_components(garnish::Camera());

    app.run();
}