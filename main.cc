#include <SDL3/SDL_keyboard.h>

#include <Physics/physics_system.hpp>
#include <Utility/camera.hpp>
#include <garnish_app.hpp>
#include <geometry.hpp>
#include <iostream>
#include <memory>
#include <shared.hpp>


struct LeftPaddle {};
struct RightPaddle {};

float movementAcceleration = 10.0f;

class LeftPaddleMovement {
    public:
    static void update(garnish::ECSController& world) {
        auto leftPaddles = world.get_entities<LeftPaddle, garnish::RigidBody>();

        if (leftPaddles.size() > 1)
            std::cout << "ERROR, more then one left paddle" << std::endl;

        auto leftPaddle = leftPaddles[0];

        int numkeys;
        const bool* keyboardState = SDL_GetKeyboardState(&numkeys);

        auto& rb = world.get_component<garnish::RigidBody>(leftPaddle);
        if (keyboardState[SDL_SCANCODE_W]) {
            rb.acceleration.y += movementAcceleration;
        } else if (keyboardState[SDL_SCANCODE_S]) {
            rb.acceleration.y -= movementAcceleration;
        }

        rb.acceleration.y += -(rb.acceleration.y / 2.0f);
    }
};

class RightPaddleMovement {
    public:
    static void update(garnish::ECSController& world) {
        auto rightPaddles =
            world.get_entities<RightPaddle, garnish::RigidBody>();

        if (rightPaddles.size() > 1)
            std::cout << "ERROR, more then one right paddle" << std::endl;

        auto rightPaddle = rightPaddles[0];

        int numkeys;
        const bool* keyboardState = SDL_GetKeyboardState(&numkeys);

        auto& rb = world.get_component<garnish::RigidBody>(rightPaddle);
        if (keyboardState[SDL_SCANCODE_UP]) {
            rb.acceleration.y += movementAcceleration;
        } else if (keyboardState[SDL_SCANCODE_DOWN]) {
            rb.acceleration.y -= movementAcceleration;
        }

        rb.acceleration.y += -(rb.acceleration.y / 2.0f);
    }
};

int main() {
    std::string engineAssetPath = "../3rdParty/GarnishEngine/";
    garnish::App::CreateInfo createInfo{.backend = garnish::RenderingBackend::OpenGL};
    createInfo.assetPath = engineAssetPath;
    garnish::App app{createInfo};

    app.get_controller().register_component<LeftPaddle>();
    app.get_controller().register_component<RightPaddle>();

    LeftPaddleMovement leftPaddleMovement;
    RightPaddleMovement rightPaddleMovement;

    app.register_update_function(LeftPaddleMovement::update);
    app.register_update_function(RightPaddleMovement::update);

    uint32_t unitCube =
        app.get_render_device()->setup_mesh(createUnitCubeGeometry());

    // TODO need to sort out these paths
    uint32_t whiteTexture = app.get_render_device()->load_texture(
        engineAssetPath + "../../assets/white-square.png");

    auto ball = app.get_controller().create_entity_with_components(
        garnish::Renderable{.meshHandle = unitCube, .texHandle = whiteTexture},
        garnish::Transform{.position = glm::vec3{0.0f, 0.0f, 0.0f}},
        garnish::RigidBody{.velocity = glm::vec3{2.0f, 0.0f, 0.0f},
                           .acceleration = glm::vec3{0.0f},
                           .inv_mass = 100.0f,
                           .dampening = 1.0f},
        garnish::SphereCollider{.radius = 0.5f,
                                .restitutionCoefficient = 1.0f});

    auto leftPaddle = app.get_controller().create_entity_with_components(
        LeftPaddle{},
        garnish::Renderable{.meshHandle = unitCube, .texHandle = whiteTexture},
        garnish::Transform{.position = glm::vec3{-8.0f, 0.0f, 0.0f}},
        garnish::RigidBody{.velocity = glm::vec3{0.0f, 0.0f, 0.0f},
                           .acceleration = glm::vec3{0.0f},
                           .inv_mass = 0.000001f,
                           .dampening = 0.1f},
        garnish::SphereCollider{.radius = 0.5f,
                                .restitutionCoefficient = 1.0f});

    auto rightPaddle = app.get_controller().create_entity_with_components(
        RightPaddle{},
        garnish::Renderable{.meshHandle = unitCube, .texHandle = whiteTexture},
        garnish::Transform{.position = glm::vec3{8.0f, 0.0f, 0.0f}},
        garnish::RigidBody{.velocity = glm::vec3{0.0f, 0.0f, 0.0f},
                           .acceleration = glm::vec3{0.0f},
                           .inv_mass = 0.000001f,
                           .dampening = 0.1f},
        garnish::SphereCollider{.radius = 0.5f,
                                .restitutionCoefficient = 1.0f});

    int leftSide = -11;
    int rightSide = 11;
    int top = 8;
    int bottom = -8;

    for (int x = leftSide; x < rightSide; ++x) {
        app.get_controller().create_entity_with_components(
            garnish::Renderable{.meshHandle = unitCube,
                                .texHandle = whiteTexture},
            garnish::Transform{.position =
                                   glm::vec3{(float)x, (float)top, 0.0f}},
            garnish::RigidBody{.velocity = glm::vec3{0.0f, 0.0f, 0.0f},
                               .acceleration = glm::vec3{0.0f},
                               .inv_mass = 0.00000001f,
                               .dampening = 0.1f},
            garnish::SphereCollider{.radius = 0.4f,
                                    .restitutionCoefficient = 1.0f});

        app.get_controller().create_entity_with_components(
            garnish::Renderable{.meshHandle = unitCube,
                                .texHandle = whiteTexture},
            garnish::Transform{.position =
                                   glm::vec3{(float)x, (float)bottom, 0.0f}},
            garnish::RigidBody{.velocity = glm::vec3{0.0f, 0.0f, 0.0f},
                               .acceleration = glm::vec3{0.0f},
                               .inv_mass = 0.00000001f,
                               .dampening = 0.1f},
            garnish::SphereCollider{.radius = 0.4f,
                                    .restitutionCoefficient = 1.0f});
    }

    for (int y = bottom; y < top; ++y) {
        app.get_controller().create_entity_with_components(
            garnish::Renderable{.meshHandle = unitCube,
                                .texHandle = whiteTexture},
            garnish::Transform{
                .position = glm::vec3{(float)leftSide - 0.5f, (float)y, 0.0f}},
            garnish::RigidBody{.velocity = glm::vec3{0.0f, 0.0f, 0.0f},
                               .acceleration = glm::vec3{0.0f},
                               .inv_mass = 0.00000001f,
                               .dampening = 0.1f},
            garnish::SphereCollider{.radius = 0.4f,
                                    .restitutionCoefficient = 1.0f});

        app.get_controller().create_entity_with_components(
            garnish::Renderable{.meshHandle = unitCube,
                                .texHandle = whiteTexture},
            garnish::Transform{
                .position = glm::vec3{(float)rightSide + 0.5f, (float)y, 0.0f}},
            garnish::RigidBody{.velocity = glm::vec3{0.0f, 0.0f, 0.0f},
                               .acceleration = glm::vec3{0.0f},
                               .inv_mass = 0.00000001f,
                               .dampening = 0.1f},
            garnish::SphereCollider{.radius = 0.4f,
                                    .restitutionCoefficient = 1.0f});
    }

    garnish::Camera cam{};
    cam.position.z = 15.0f;
    app.get_controller().create_entity_with_components(cam);

    app.run();
}