#include <gtest/gtest.h>
#include "mobs/mobs.hpp"

using namespace mobs;

class TestComponentManager : public ::testing::Test {
protected:
    ComponentManager componentManager;
};

TEST_F(TestComponentManager, RegisterComponent) {
    componentManager.registerComponent<int>();
    ComponentType intType = componentManager.getComponentType<int>();

    EXPECT_EQ(intType, 0);
}

TEST_F(TestComponentManager, GetComponentType) {
    componentManager.registerComponent<int>();
    ComponentType intType = componentManager.getComponentType<int>();

    EXPECT_EQ(intType, 0);

    componentManager.registerComponent<float>();
    ComponentType floatType = componentManager.getComponentType<float>();

    EXPECT_EQ(floatType, 1);
}

TEST_F(TestComponentManager, GetComponentArray) {
    componentManager.registerComponent<int>();
    auto intArray = componentManager.getComponentArray<int>();

    intArray->insertComponent(1, 42);
    EXPECT_EQ(intArray->getComponent(1), 42);

    intArray->removeComponent(1);
    EXPECT_THROW(intArray->getComponent(1), std::bad_optional_access);
}

TEST_F(TestComponentManager, GetComponentArrayNonExistent) {
    // EXPECT_THROW(componentManager.getComponentArray<int>(), std::out_of_range);
}