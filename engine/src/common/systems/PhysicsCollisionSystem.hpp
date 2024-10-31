/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include <cmath>
#include <system/ISystem.hpp>

namespace RType
{

class PhysicsSystem : public ISystem
{
   public:
    PhysicsSystem() {}
    ~PhysicsSystem() {}

    void update(mobs::Registry& registry, GameContext& gameContext) override
    {
        if (gameContext._runtime->getKeyDown(KeyCode::C))
        {
            displayCollider = !displayCollider;
        }
        auto view = registry.view<RigidBody, Transform>();
        for (auto entity : view)
        {
            auto& rb = registry.get<RigidBody>(entity);
            auto& transform = registry.get<Transform>(entity);

            applyGravity(rb, gameContext._deltaT);
            updateVelocityAndPosition(transform, rb, gameContext._deltaT);
        }

        auto view2 = registry.view<Transform, Collider>();
        for (auto entity : view2)
        {
            auto& transform = registry.get<Transform>(entity);
            auto& collider = registry.get<Collider>(entity);

            for (auto otherEntity : view2)
            {
                if (entity == otherEntity)
                {
                    continue;
                }
                auto& otherTransform = registry.get<Transform>(otherEntity);
                auto& otherCollider = registry.get<Collider>(otherEntity);
                if (std::find(collider.layerMask.begin(), collider.layerMask.end(),
                              registry.get<Basics>(otherEntity).layer) == collider.layerMask.end())
                {
                    continue;
                }

                int result = collider.isColliding(transform.position + collider.offset, otherEntity,
                                                  otherTransform.position + otherCollider.offset,
                                                  otherCollider.size);
                if (collider.isTrigger)
                {
                    try
                    {
                        if (result == ENTER)
                        {
                            registry.get<CppScriptComponent>(entity).onCollisionEnterAll(
                                registry, gameContext, otherEntity);
                        }
                        else if (result == STAY)
                        {
                            registry.get<CppScriptComponent>(entity).onCollisionStayAll(
                                registry, gameContext, otherEntity);
                        }
                        else if (result == EXIT)
                        {
                            registry.get<CppScriptComponent>(entity).onCollisionExitAll(
                                registry, gameContext, otherEntity);
                        }
                    }
                    catch (const std::exception& e)
                    {
                    }
                }
                else
                {
                    if (result == ENTER)
                    {
                    }
                }
            }
        }
    }
    void draw(mobs::Registry& registry, GameContext& gameContext) override
    {
        if (displayCollider == 0) return;
        auto view = registry.view<Transform, Collider>();
        for (auto entity : view)
        {
            auto& transform = registry.get<Transform>(entity);
            auto& collider = registry.get<Collider>(entity);
            mlg::vec4 spriteCoords(transform.position.x + collider.offset.x,
                                   transform.position.y + collider.offset.y, collider.size.x,
                                   collider.size.y);
            gameContext._runtime->drawRectangle(spriteCoords, false, mlg::vec3(255.0f, 0.0f, 0.0f));
        }
    }

   private:
    int displayCollider = 0;

    void applyGravity(RigidBody& rb, float deltaTime)
    {
        const float gravity = 9.8f;

        mlg::vec3 gravitationalForce(0.0f, rb.mass * gravity, 0.0f);

        rb.acceleration.y += gravitationalForce.y / rb.mass;

        rb.acceleration.y += (rb.mass * 0.1f);
    }

    void updateVelocityAndPosition(Transform& transform, RigidBody& rb, float deltaTime)
    {
        rb.velocity += rb.acceleration * deltaTime;
        transform.position += rb.velocity * deltaTime;

        rb.acceleration = mlg::vec3(0.0f, 0.0f, 0.0f);
    }
};

}  // namespace RType
