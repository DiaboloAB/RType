#include <gtest/gtest.h>
#include "EntityManager.hpp" // Make sure this path is correct

using namespace RType::ECS;

class EntityManagerTest : public ::testing::Test {
protected:
    EntityManager entityManager;  // The EntityManager we will test
};

// Test that a new entity can be created
TEST_F(EntityManagerTest, create) {
    Entity entity = entityManager.create();
    EXPECT_EQ(entity, 0);  // The first entity should have ID 0
}

// Test that an entity is properly destroyed
TEST_F(EntityManagerTest, Create2Entity) {
    Entity entity = entityManager.create();
    Entity entity2 = entityManager.create();

    EXPECT_EQ(entity, 0);
    EXPECT_EQ(entity2, 1);
}

// Test that signatures can be set and retrieved correctly
TEST_F(EntityManagerTest, SetAndGetSignature) {
    Entity entity = entityManager.create();
    Signature signature;
    signature.set(1);  // For example, set the first bit of the signature

    entityManager.setSignature(entity, signature);
    Signature retrievedSignature = entityManager.getSignature(entity);

    EXPECT_EQ(signature, retrievedSignature);  // Signatures should match
}

// Test entity overflow: trying to create more than MAX_ENTITIES
TEST_F(EntityManagerTest, TooManyEntities) {
    for (Entity i = 0; i < MAX_ENTITIES; ++i) {
        entityManager.create();
    }

    // This should trigger an assert or error because we've created the maximum number of entities
    ASSERT_DEATH(entityManager.create(), "Too many entities in existence.");
}

// Test destroying an invalid entity (out of range)
TEST_F(EntityManagerTest, DestroyInvalidEntity) {
    // This should trigger an assertion as we're trying to destroy an entity out of bounds
    ASSERT_DEATH(entityManager.kill(MAX_ENTITIES + 1), "Entity out of range.");
}
