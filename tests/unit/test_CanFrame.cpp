#include <gtest/gtest.h>
#include "CanFrame.h"
#include <cstring>

// 测试 CANFrame 结构体
TEST(CanFrameTest, CANFrameStructure) {
    CANFrame frame;
    
    // 初始化测试
    frame.can_id = 0x123;
    frame.can_dlc = 8;
    memset(frame.data, 0, sizeof(frame.data));
    
    // 验证结构体成员
    EXPECT_EQ(frame.can_id, 0x123);
    EXPECT_EQ(frame.can_dlc, 8);
    
    // 验证数据数组大小
    EXPECT_EQ(sizeof(frame.data), 8);
}

// 测试 CANFrame 数据设置和读取
TEST(CanFrameTest, CANFrameData) {
    CANFrame frame;
    
    frame.can_id = 0x456;
    frame.can_dlc = 4;
    
    // 设置数据
    frame.data[0] = 0x01;
    frame.data[1] = 0x02;
    frame.data[2] = 0x03;
    frame.data[3] = 0x04;
    
    // 验证数据
    EXPECT_EQ(frame.data[0], 0x01);
    EXPECT_EQ(frame.data[1], 0x02);
    EXPECT_EQ(frame.data[2], 0x03);
    EXPECT_EQ(frame.data[3], 0x04);
    
    // 验证 can_dlc 与实际数据长度一致
    EXPECT_EQ(frame.can_dlc, 4);
}

// 测试 CANFrame 边界值
TEST(CanFrameTest, CANFrameBoundaries) {
    CANFrame frame;
    
    // 测试最大 can_dlc
    frame.can_dlc = 8;
    for (int i = 0; i < 8; ++i) {
        frame.data[i] = static_cast<uint8_t>(i);
    }
    
    EXPECT_EQ(frame.can_dlc, 8);
    for (int i = 0; i < 8; ++i) {
        EXPECT_EQ(frame.data[i], static_cast<uint8_t>(i));
    }
    
    // 测试最小 can_dlc
    frame.can_dlc = 0;
    EXPECT_EQ(frame.can_dlc, 0);
    
    // 测试 can_dlc = 1
    frame.can_dlc = 1;
    frame.data[0] = 0xFF;
    EXPECT_EQ(frame.can_dlc, 1);
    EXPECT_EQ(frame.data[0], 0xFF);
}

// 测试 CANFrame 的 can_id 范围
TEST(CanFrameTest, CANFrameIdRange) {
    CANFrame frame;
    
    // 测试标准 CAN ID (11位，0-0x7FF)
    frame.can_id = 0x000;
    EXPECT_EQ(frame.can_id, 0x000);
    
    frame.can_id = 0x7FF;
    EXPECT_EQ(frame.can_id, 0x7FF);
    
    // 测试扩展 CAN ID (29位，可以更大)
    frame.can_id = 0x1FFFFFFF;
    EXPECT_EQ(frame.can_id, 0x1FFFFFFF);
    
    // 测试常见 ID 值
    frame.can_id = 0x123;
    EXPECT_EQ(frame.can_id, 0x123);
}

// 测试 CANFrame 数据清零
TEST(CanFrameTest, CANFrameDataZero) {
    CANFrame frame;
    
    frame.can_id = 0x789;
    frame.can_dlc = 8;
    
    // 设置一些数据
    memset(frame.data, 0xFF, sizeof(frame.data));
    
    // 清零数据
    memset(frame.data, 0, sizeof(frame.data));
    
    // 验证所有数据都是 0
    for (int i = 0; i < 8; ++i) {
        EXPECT_EQ(frame.data[i], 0);
    }
}

// 测试 CANFrame 数据复制
TEST(CanFrameTest, CANFrameDataCopy) {
    CANFrame frame1, frame2;
    
    // 设置 frame1
    frame1.can_id = 0xABC;
    frame1.can_dlc = 5;
    for (int i = 0; i < 5; ++i) {
        frame1.data[i] = static_cast<uint8_t>(0x10 + i);
    }
    
    // 复制到 frame2
    frame2.can_id = frame1.can_id;
    frame2.can_dlc = frame1.can_dlc;
    memcpy(frame2.data, frame1.data, frame1.can_dlc);
    
    // 验证复制结果
    EXPECT_EQ(frame2.can_id, frame1.can_id);
    EXPECT_EQ(frame2.can_dlc, frame1.can_dlc);
    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(frame2.data[i], frame1.data[i]);
    }
}

// 测试 CANFrame 结构体大小
TEST(CanFrameTest, CANFrameSize) {
    CANFrame frame;
    
    // 验证结构体大小合理（can_id + can_dlc + data[8] + 可能的填充）
    size_t expected_min_size = sizeof(uint32_t) + sizeof(uint8_t) + 8;
    EXPECT_GE(sizeof(frame), expected_min_size);
    
    // 验证数据数组确实是 8 字节
    EXPECT_EQ(sizeof(frame.data), 8);
}

