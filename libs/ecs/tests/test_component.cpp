#include <gtest/gtest.h>
#include "ComponentArray.hpp"

using namespace RType::ECS;

class TestComponentArray : public ::testing::Test {
protected:
    ComponentArray<int> componentArray;
};

TEST_F(TestComponentArray, InsertComponent) {
    Entity entity = 1;
    int component = 42;

    componentArray.insertComponent(entity, component);

    EXPECT_EQ(componentArray.getComponent(entity), component);
}

TEST_F(TestComponentArray, RemoveComponent) {
    // Entity entity = 1;
    // int component = 42;

    // componentArray.insertComponent(entity, component);
    // componentArray.removeComponent(entity);

    // EXPECT_FALSE(componentArray.getComponent(entity).has_value());
}

TEST_F(TestComponentArray, GetComponent) {
    Entity entity = 1;
    int component = 42;

    componentArray.insertComponent(entity, component);

    EXPECT_EQ(componentArray.getComponent(entity), component);
}

TEST_F(TestComponentArray, GetComponentNonExistent) {
    // Entity entity = 1;

    // EXPECT_THROW(componentArray.getComponent(entity), std::bad_optional_access);
}