#include <gtest/gtest.h>

#include "mobs/mobs.hpp"

using namespace mobs;

class EntityManagerTest : public ::testing::Test
{
   protected:
    EntityManager entityManager;
};

TEST_F(EntityManagerTest, create)
{
    Entity entity = entityManager.create();
    EXPECT_EQ(entity, 0);
}

TEST_F(EntityManagerTest, Create2Entity)
{
    Entity entity = entityManager.create();
    Entity entity2 = entityManager.create();

    EXPECT_EQ(entity, 0);
    EXPECT_EQ(entity2, 1);
}

TEST_F(EntityManagerTest, SetAndGetSignature)
{
    Entity entity = entityManager.create();
    Signature signature;
    signature.set(1);

    entityManager.setSignature(entity, signature);
    Signature retrievedSignature = entityManager.getSignature(entity);

    EXPECT_EQ(signature, retrievedSignature);
}

// TEST_F(EntityManagerTest, TooManyEntities) {
//     for (Entity i = 0; i < MAX_ENTITIES; ++i) {
//         entityManager.create();
//     }

//     ASSERT_DEATH(entityManager.create(), "Too many entities in existence.");
// }

// TEST_F(EntityManagerTest, DestroyInvalidEntity) {
//     ASSERT_DEATH(entityManager.kill(MAX_ENTITIES + 1), "Entity out of range.");
// }
