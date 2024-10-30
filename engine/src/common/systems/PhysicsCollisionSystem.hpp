/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include <system/ISystem.hpp>
#include <cmath>

namespace RType {

class PhysicsSystem : public ISystem {
public:
    PhysicsSystem() {}
    ~PhysicsSystem() {}

    void update(mobs::Registry& registry, GameContext& gameContext) override {
        auto view = registry.view<RigidBody, Transform>();
        for (auto entity : view) {
            auto& rb = registry.get<RigidBody>(entity);
            auto& transform = registry.get<Transform>(entity);

            applyGravity(rb, gameContext._deltaT);
            updateVelocityAndPosition(transform, rb, gameContext._deltaT);
        }

        auto view2 = registry.view<Transform, Collider>();
        for (auto entity : view2) {
            auto& transform = registry.get<Transform>(entity);
            auto& collider = registry.get<Collider>(entity);

            for (auto otherEntity : view2) {
                if (entity == otherEntity) {
                    continue;
                }

                auto& otherTransform = registry.get<Transform>(otherEntity);
                auto& otherCollider = registry.get<Collider>(otherEntity);

                int result = collider.isColliding(otherEntity, otherTransform.position, otherCollider.size);
                if (collider.isTrigger) {
                    try {
                        if (result == ENTER)
                            registry.get<CppScriptComponent>(entity).onCollisionEnterAll(registry, gameContext, otherEntity);
                        else if (result == EXIT)
                            ;//registry.get<CppScriptComponent>(entity).onCollisionStayAll(registry, gameContext, otherEntity);
                        else
                            ;//registry.get<CppScriptComponent>(entity).onCollisionExitAll(registry, gameContext, otherEntity);
                    } catch (const std::exception& e) {
                        std::cerr << e.what() << '\n';
                    }

                } else {
                    // if (result == ENTER) {
                    //     rb.velocity.y = -rb.velocity.y * rb.restitution;
                    // }
                }
            }
        }
    }

private:
    void applyGravity(RigidBody& rb, float deltaTime) {
        const float gravity = 9.8f;

        mlg::vec3 gravitationalForce(0.0f, rb.mass * gravity, 0.0f);

        rb.acceleration.y += gravitationalForce.y / rb.mass; 

        rb.acceleration.y += (rb.mass * 0.1f);
    }

    void updateVelocityAndPosition(Transform& transform, RigidBody& rb, float deltaTime) {
        rb.velocity += rb.acceleration * deltaTime;
        transform.position += rb.velocity * deltaTime;

        rb.acceleration = mlg::vec3(0.0f, 0.0f, 0.0f);
    }

    
};

}  // namespace RType
