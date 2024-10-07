#include <gtest/gtest.h>
#include "mlg/mlg.hpp"

namespace mlg {

TEST(Vec3Test, DefaultConstructor) {
    vec3 v;
    EXPECT_FLOAT_EQ(v.x, 0);
    EXPECT_FLOAT_EQ(v.y, 0);
    EXPECT_FLOAT_EQ(v.z, 0);
}

TEST(Vec3Test, ParameterizedConstructor) {
    vec3 v(1.0f, 2.0f, 3.0f);
    EXPECT_FLOAT_EQ(v.x, 1.0f);
    EXPECT_FLOAT_EQ(v.y, 2.0f);
    EXPECT_FLOAT_EQ(v.z, 3.0f);
}

TEST(Vec3Test, CrossProduct) {
    vec3 v1(1.0f, 0.0f, 0.0f);
    vec3 v2(0.0f, 1.0f, 0.0f);
    vec3 result = v1.cross(v2);
    EXPECT_FLOAT_EQ(result.x, 0.0f);
    EXPECT_FLOAT_EQ(result.y, 0.0f);
    EXPECT_FLOAT_EQ(result.z, 1.0f);
}

TEST(Vec3Test, DotProduct) {
    vec3 v1(1.0f, 2.0f, 3.0f);
    vec3 v2(4.0f, 5.0f, 6.0f);
    float result = v1.dot(v2);
    EXPECT_FLOAT_EQ(result, 32.0f);
}

TEST(Vec3Test, Length) {
    vec3 v(3.0f, 4.0f, 0.0f);
    EXPECT_FLOAT_EQ(v.length(), 5.0f);
}

TEST(Vec3Test, Normalize) {
    vec3 v(3.0f, 4.0f, 0.0f);
    vec3 norm = v.normalize();
    EXPECT_FLOAT_EQ(norm.length(), 1.0f);
    EXPECT_FLOAT_EQ(norm.x, 0.6f);
    EXPECT_FLOAT_EQ(norm.y, 0.8f);
    EXPECT_FLOAT_EQ(norm.z, 0.0f);
}

TEST(Vec3Test, Addition) {
    vec3 v1(1.0f, 2.0f, 3.0f);
    vec3 v2(4.0f, 5.0f, 6.0f);
    vec3 result = v1 + v2;
    EXPECT_FLOAT_EQ(result.x, 5.0f);
    EXPECT_FLOAT_EQ(result.y, 7.0f);
    EXPECT_FLOAT_EQ(result.z, 9.0f);
}

TEST(Vec3Test, Subtraction) {
    vec3 v1(4.0f, 5.0f, 6.0f);
    vec3 v2(1.0f, 2.0f, 3.0f);
    vec3 result = v1 - v2;
    EXPECT_FLOAT_EQ(result.x, 3.0f);
    EXPECT_FLOAT_EQ(result.y, 3.0f);
    EXPECT_FLOAT_EQ(result.z, 3.0f);
}

TEST(Vec3Test, ScalarMultiplication) {
    vec3 v(1.0f, 2.0f, 3.0f);
    vec3 result = v * 2.0f;
    EXPECT_FLOAT_EQ(result.x, 2.0f);
    EXPECT_FLOAT_EQ(result.y, 4.0f);
    EXPECT_FLOAT_EQ(result.z, 6.0f);
}

}
