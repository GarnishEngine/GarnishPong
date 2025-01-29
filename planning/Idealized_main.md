#### An idealized version of the main file assuming GarnishEngine is done

```cpp
#include "garnish_engine.hpp"
#include "garnish_ecs.hpp"

namespace Pong {
    struct LeftPaddle{ };
    struct RightPaddle{ };

    struct LeftDetectionZone{ };
    struct RightDetectionZone{ };

    class PongApp : public garnish::GarnishApp {
    public:
        void init() override {
            ecs.NewComponent<LeftPaddle>();
            ecs.NewComponent<RightPaddle>();

            leftPaddle = ecs.NewEntityWithComponents<
                LeftPaddle,
                HitBox, // In this ideal system the hitbox would be able to call a user defined function when this hitbox is hit
                // The HitBox should also specify the shape of the collider ie circle/sphere or box etc.
                // The HitBox should not make the object collide with other objects, thats the rigid bodys job
                RigidBody, // The rigid body should make other objects that hit this not go through it, it should be rigid
                Transform
            >();

            rightPaddle = ecs.NewEntityWithComponents<
                RightPaddle,
                HitBox,
                RigidBody,
                Transform
            >();

            ball = ecs.NewEntityWithComponents<
                HitBox,
                RigidBody,
                Transform
            >();

            ecs.AddSystem([](){
                for (auto entity : ecs.GetEntities<LeftPaddle, Transform>()) {
                    if (garnish::GarnishKeyboard.GetKey(KEY_W) == PRESSED) {
                        /*
                        TODO this will not work if we use forces in collision detection at all, instead this will
                        need to be a force which then makes it very annoying to have percise control over the paddle.

                        Modifying the transform is simply a placeholder for now.
                        */
                        ecs.GetComponent<Transform>(entity).position.y += 5;
                    }

                    if (garnish::GarnishKeyboard.GetKey(KEY_S) == PRESSED) {
                        ecs.GetComponent<Transform>(entity).position.y -= 5;
                    }
                }
            });

            ecs.AddSystem([](){
                for (auto entity : ecs.GetEntities<RightPaddle, Transform>()) {
                    if (garnish::GarnishKeyboard.GetKey(KEY_UP_ARROW) == PRESSED) {
                        ecs.GetComponent<Transform>(entity).position.y += 5;
                    }

                    if (garnish::GarnishKeyboard.GetKey(KEY_DOWN_ARROW) == PRESSED) {
                        ecs.GetComponent<Transform>(entity).position.y -= 5;
                    }
                }
            });

            ecs.NewComponent<LeftDetectionZone>();
            ecs.NewComponent<RightDetectionZone>();

            leftDetectionZone = ecs.NewEntityWithComponents<
                LeftDetectionZone,
                HitBox,
                Transform
            >();

            rightDetectionZone = ecs.NewEntityWithComponents<
                RightDetectionZone,
                HitBox,
                Transform
            >();

            ecs.GetComponent<HitBox>(leftDetectionZone).callback = [&rightPaddleScore](){
                ++rightPaddleScore;

                if (rightPaddleScore >= 10) {
                    EndGame(); // TODO somehow pass in who won the game
                }

                ResetBall(); // TODO Super simplified for now, this should be implemented soon as it may have complex ECS interactions
            };

            ecs.GetComponent<HitBox>(rightDetectionZone).callback = [&leftPaddleScore](){
                ++leftPaddleScore;

                if (leftPaddleScore >= 10) {
                    EndGame();
                }

                ResetBall();
            };
        }

    private:
        garnish::GarnishECSManager ecs;

        garnish::GarnishEntity leftPaddle;
        garnish::GarnishEntity rightPaddle;
        garnish::GarnishEntity ball;

        garnish::GarnishEntity leftDetectionZone;
        garnish::GarnishEntity rightDetectionZone;

        int leftPaddleScore{ 0 };
        int rightPaddleScore{ 0 };
    };
}

int main() {
    PongApp app{};
    try {
        app.init();

        app.run();
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
```