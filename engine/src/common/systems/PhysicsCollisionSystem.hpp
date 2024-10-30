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
