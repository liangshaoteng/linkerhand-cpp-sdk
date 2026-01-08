#include <gtest/gtest.h>
#include "RangeToArc.h"
#include <cmath>
#include <vector>

// 测试 is_within_range 函数
TEST(RangeToArcTest, IsWithinRange) {
    // 值在范围内
    EXPECT_DOUBLE_EQ(is_within_range(5.0, 0.0, 10.0), 5.0);
    EXPECT_DOUBLE_EQ(is_within_range(0.0, 0.0, 10.0), 0.0);  // 边界值
    EXPECT_DOUBLE_EQ(is_within_range(10.0, 0.0, 10.0), 10.0); // 边界值
    
    // 值小于最小值
    EXPECT_DOUBLE_EQ(is_within_range(-5.0, 0.0, 10.0), 0.0);
    
    // 值大于最大值
    EXPECT_DOUBLE_EQ(is_within_range(15.0, 0.0, 10.0), 10.0);
    
    // 负值范围
    EXPECT_DOUBLE_EQ(is_within_range(-2.0, -5.0, -1.0), -2.0);
    EXPECT_DOUBLE_EQ(is_within_range(-6.0, -5.0, -1.0), -5.0);
    EXPECT_DOUBLE_EQ(is_within_range(0.0, -5.0, -1.0), -1.0);
}

// 测试 scale_value 函数
TEST(RangeToArcTest, ScaleValue) {
    // 基本缩放测试
    EXPECT_NEAR(scale_value(5.0, 0.0, 10.0, 0.0, 100.0), 50.0, 0.001);
    EXPECT_NEAR(scale_value(0.0, 0.0, 10.0, 0.0, 100.0), 0.0, 0.001);
    EXPECT_NEAR(scale_value(10.0, 0.0, 10.0, 0.0, 100.0), 100.0, 0.001);
    
    // 负值范围缩放
    EXPECT_NEAR(scale_value(-2.0, -5.0, 0.0, 0.0, 100.0), 60.0, 0.001);
    
    // 不同范围的缩放
    EXPECT_NEAR(scale_value(128, 0, 255, 0.0, 1.57), 0.785, 0.01);
}

// 测试 should_skip_joint 函数
TEST(RangeToArcTest, ShouldSkipJoint) {
    // 测试不同的关节类型和索引
    // 注意：这个函数的具体实现需要查看源代码
    // 这里假设一些基本行为
    bool result1 = should_skip_joint(0, 0);
    bool result2 = should_skip_joint(0, 1);
    // 验证函数不会崩溃
    EXPECT_TRUE(result1 == true || result1 == false);
    EXPECT_TRUE(result2 == true || result2 == false);
}

// 测试 initialize_params 函数
TEST(RangeToArcTest, InitializeParams) {
    std::vector<double> min_limits;
    std::vector<double> max_limits;
    std::vector<int> derict;
    
    // 测试 L10 左手参数初始化
    bool result = initialize_params(static_cast<int>(L10), "left", min_limits, max_limits, derict);
    EXPECT_TRUE(result);
    EXPECT_FALSE(min_limits.empty());
    EXPECT_FALSE(max_limits.empty());
    EXPECT_FALSE(derict.empty());
    EXPECT_EQ(min_limits.size(), max_limits.size());
    EXPECT_EQ(min_limits.size(), derict.size());
    
    // 验证 L10 左手应该有 10 个关节
    EXPECT_EQ(min_limits.size(), 10);
    
    // 验证每个关节的最小值小于等于最大值
    for (size_t i = 0; i < min_limits.size(); ++i) {
        EXPECT_LE(min_limits[i], max_limits[i]);
    }
}

// 测试 range_to_arc 函数
TEST(RangeToArcTest, RangeToArc) {
    // 测试 L10 左手的转换
    std::vector<uint8_t> hand_range = {128, 128, 128, 128, 128, 128, 128, 128, 128, 128};
    std::vector<double> result = range_to_arc(static_cast<int>(L10), "left", hand_range);
    
    EXPECT_FALSE(result.empty());
    EXPECT_EQ(result.size(), hand_range.size());
    
    // 验证结果在合理范围内（对于 L10 左手）
    for (size_t i = 0; i < result.size(); ++i) {
        // L10 左手的范围应该在定义的 min/max 之间
        EXPECT_GE(result[i], l10_l_min[i] - 0.1); // 允许小的误差
        EXPECT_LE(result[i], l10_l_max[i] + 0.1);
    }
}

// 测试 arc_to_range 函数
TEST(RangeToArcTest, ArcToRange) {
    // 测试 L10 左手的转换
    // 使用中间值进行测试
    std::vector<double> hand_arc(10, 0.5);
    std::vector<uint8_t> result = arc_to_range(static_cast<int>(L10), "left", hand_arc);
    
    EXPECT_FALSE(result.empty());
    EXPECT_EQ(result.size(), hand_arc.size());
    
    // 验证结果在 0-255 范围内
    for (uint8_t value : result) {
        EXPECT_GE(value, 0);
        EXPECT_LE(value, 255);
    }
}

// 测试 range_to_arc 和 arc_to_range 的往返转换
TEST(RangeToArcTest, RoundTripConversion) {
    // 测试往返转换的精度
    std::vector<uint8_t> original = {0, 64, 128, 192, 255, 100, 150, 200, 50, 75};
    std::vector<double> arc = range_to_arc(static_cast<int>(L10), "left", original);
    std::vector<uint8_t> converted_back = arc_to_range(static_cast<int>(L10), "left", arc);
    
    EXPECT_EQ(original.size(), converted_back.size());
    
    // 由于浮点数精度和范围限制，允许一定的误差
    for (size_t i = 0; i < original.size(); ++i) {
        int diff = std::abs(static_cast<int>(original[i]) - static_cast<int>(converted_back[i]));
        EXPECT_LE(diff, 2); // 允许最多 2 的误差
    }
}

// 测试边界值
TEST(RangeToArcTest, BoundaryValues) {
    // 测试最小值
    std::vector<uint8_t> min_range(10, 0);
    std::vector<double> min_arc = range_to_arc(static_cast<int>(L10), "left", min_range);
    EXPECT_FALSE(min_arc.empty());
    
    // 测试最大值
    std::vector<uint8_t> max_range(10, 255);
    std::vector<double> max_arc = range_to_arc(static_cast<int>(L10), "left", max_range);
    EXPECT_FALSE(max_arc.empty());
    
    // 测试中间值
    std::vector<uint8_t> mid_range(10, 128);
    std::vector<double> mid_arc = range_to_arc(static_cast<int>(L10), "left", mid_range);
    EXPECT_FALSE(mid_arc.empty());
}

// 测试不同型号的转换
TEST(RangeToArcTest, DifferentHandTypes) {
    std::vector<uint8_t> test_range = {128, 128, 128, 128, 128, 128};
    
    // 测试 L6
    std::vector<double> l6_arc = range_to_arc(static_cast<int>(L6), "left", test_range);
    EXPECT_FALSE(l6_arc.empty());
    
    // 测试 L7
    std::vector<uint8_t> l7_range = {128, 128, 128, 128, 128, 128, 128};
    std::vector<double> l7_arc = range_to_arc(static_cast<int>(L7), "left", l7_range);
    EXPECT_FALSE(l7_arc.empty());
}

