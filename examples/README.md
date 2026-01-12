# 示例代码说明

本文档介绍 LinkerHand-CPP-SDK 提供的示例代码及其使用方法。

## 目录

- [示例列表](#示例列表)
- [如何运行示例](#如何运行示例)
- [示例详细说明](#示例详细说明)
- [学习路径](#学习路径)
- [常见问题](#常见问题)

---

## 示例列表

| 示例文件 | 功能描述 | 适用型号 | 难度 |
|---------|---------|---------|------|
| `toolset_example.cpp` | 交互式工具集，演示所有 API 功能 | 所有型号 | 中级 |
| `action_group_show_l10.cpp` | L10 型号的动作组演示 | L10 | 初级 |

---

## 如何运行示例

### 方法一：使用安装脚本（推荐）

```bash
./script.sh
# 选择选项 [6]: Run examples
```

### 方法二：手动编译和运行

```bash
# 1. 构建项目
mkdir build && cd build
cmake ..
make

# 2. 运行示例
./toolset_example
./action_group_show_l10
```

### 方法三：直接编译示例

```bash
# 编译 toolset_example
g++ -std=c++11 examples/toolset_example.cpp -I./include \
    -L./lib/x86_64 -llinkerhand_cpp_sdk -lpthread -o toolset_example

# 运行
./toolset_example
```

---

## 示例详细说明

### toolset_example.cpp

**功能描述**
交互式工具集，提供菜单界面，可以测试所有 API 功能。适合学习和调试。

**主要功能**:
1. 获取版本信息
2. 获取温度数据
3. 获取故障码
4. 获取电流数据
5. 获取扭矩数据
6. 获取速度数据
7. 获取压力传感信息
8. 循环获取关节状态
9. 执行预设动作
10. 清除故障码

**使用步骤**:
1. 运行程序
2. 选择机械手型号（L6/O6、L7、L10、L20、L21、L25）
3. 选择手部方向（左手/右手）
4. 选择通信接口（CAN0、CAN1、ModBus、EtherCAT）
5. 进入交互菜单，选择要测试的功能

**代码结构**:
```cpp
// 1. 选择型号
// 2. 选择手部方向
// 3. 选择通信接口
// 4. 创建 API 实例
LinkerHandApi hand(linkerhand, handType, channel);

// 5. 进入交互模式
interactiveMode(hand);
```

**预设动作**:
- **L6**: 单指循环弯曲
- **L7**: 握拳和张开
- **L10**: 
  - 手指循环弯曲
  - 拇指与其他手指循环对指
  - 手指侧摆
  - 握拳和张开
- **L20**: 握拳和张开
- **L21/L25**: 握拳和张开

**使用示例**:
```bash
$ ./toolset_example

=========================
        Example
=========================

Run Choose LinkerHand:
-------------------------
[1]: L6/O6
-------------------------
[2]: L7
-------------------------
[3]: L10
-------------------------
...
```

---

### action_group_show_l10.cpp

**功能描述**
专门为 L10 型号设计的动作组演示程序。展示如何实现连续的动作序列。

**主要功能**:
- 演示 L10 型号的各种动作组合
- 展示动作序列的编程方式
- 适合学习动作控制的基本方法

**适用型号**: L10（适配球形拇指根部关节版本）

**代码特点**:
- 使用关节映射表管理关节状态
- 实现动作序列的循环执行
- 支持左右手（默认右手，修改 `HAND_TYPE::RIGHT` 为 `HAND_TYPE::LEFT` 可切换为左手）

**关节映射**:
```cpp
// L10 关节顺序
vector<string> joint_order = {
    "joint1",  // 拇指根部弯曲
    "joint2",  // 拇指侧摆
    "joint3",  // 食指根部弯曲
    "joint4",  // 中指根部弯曲
    "joint5",  // 无名指根部弯曲
    "joint6",  // 小指根部弯曲
    "joint7",  // 食指侧摆
    "joint8",  // 中指侧摆
    "joint9",  // 无名指侧摆
    "joint10"  // 拇指旋转
};
```

**使用示例**:
```bash
$ ./action_group_show_l10
# 程序会自动执行预设的动作序列
```

**注意事项**:
- 本示例仅支持 L10 型号
- 默认使用右手，如需左手请修改代码中的 `HAND_TYPE::RIGHT` 为 `HAND_TYPE::LEFT`
- 确保设备已正确连接
- 确保通信接口已正确配置（CAN 总线、ModBus 或 EtherCAT）

---

## 学习路径

### 初学者

1. **第一步**: 阅读 [README.md](../README.md) 了解基本概念
2. **第二步**: 运行 `action_group_show_l10.cpp` 查看基本动作
3. **第三步**: 阅读代码，理解关节控制的基本方法
4. **第四步**: 尝试修改代码，实现自己的动作

### 中级用户

1. **第一步**: 运行 `toolset_example.cpp` 熟悉所有 API
2. **第二步**: 阅读 [API 参考文档](../docs/API-Reference.md) 了解详细接口
3. **第三步**: 参考示例代码实现自己的应用
4. **第四步**: 学习传感器数据读取和处理

### 高级用户

1. **第一步**: 深入研究示例代码的实现细节
2. **第二步**: 优化代码性能
3. **第三步**: 实现复杂的动作序列
4. **第四步**: 集成到自己的项目中

---

## 代码学习要点

### 1. 初始化 API

```cpp
// 创建 API 实例
LinkerHandApi hand(LINKER_HAND::L10, HAND_TYPE::RIGHT);
```

### 2. 设置速度和扭矩

```cpp
// 设置速度（5 个元素对应 5 根手指）
std::vector<uint8_t> speed = {200, 200, 200, 200, 200};
hand.setSpeed(speed);

// 设置扭矩
std::vector<uint8_t> torque = {255, 255, 255, 255, 255};
hand.setTorque(torque);
```

### 3. 控制关节运动

```cpp
// L10 需要 10 个关节值
std::vector<uint8_t> pose = {128, 128, 128, 128, 128, 128, 128, 128, 128, 128};
hand.fingerMove(pose);

// 等待动作完成
std::this_thread::sleep_for(std::chrono::seconds(1));
```

### 4. 读取传感器数据

```cpp
// 获取压力数据
auto force = hand.getForce();

// 获取关节状态
auto state = hand.getState();

// 获取温度
auto temperature = hand.getTemperature();
```

### 5. 错误处理

```cpp
// 检查故障码
auto fault_code = hand.getFaultCode();
for (size_t i = 0; i < fault_code.size(); i++) {
    if (fault_code[i] != 0) {
        std::cout << "警告: 电机 " << i << " 故障码: " 
                  << static_cast<int>(fault_code[i]) << std::endl;
    }
}
```

---

## 常见问题

### Q1: 示例程序无法运行？

**A**: 检查以下几点：
1. 确保已正确编译
2. 检查库文件路径是否正确
3. 确保设备已连接
4. 检查通信接口配置（CAN 总线等）

详细排查请参考 [故障排查指南](../docs/TROUBLESHOOTING.md)。

---

### Q2: 如何修改示例代码适配其他型号？

**A**: 
1. 修改型号参数：
   ```cpp
   // 从 L10 改为 L20
   LinkerHandApi hand(LINKER_HAND::L20, HAND_TYPE::RIGHT);
   ```

2. 修改关节数组长度：
   ```cpp
   // L20 需要 20 个关节值
   std::vector<uint8_t> pose(20, 128);
   ```

3. 参考 [关节映射表](../README.md#关节映射表) 了解不同型号的关节配置

---

### Q3: 如何实现自己的动作序列？

**A**: 
1. 定义动作数组：
   ```cpp
   std::vector<std::vector<uint8_t>> actions = {
       {255, 104, 255, 255, 255, 255, 255, 255, 255, 71},  // 动作1
       {101, 60, 0, 0, 0, 0, 255, 255, 255, 51},            // 动作2
       // ...
   };
   ```

2. 循环执行：
   ```cpp
   for (const auto& pose : actions) {
       hand.fingerMove(pose);
       std::this_thread::sleep_for(std::chrono::seconds(1));
   }
   ```

---

### Q4: 如何读取和处理传感器数据？

**A**: 参考 `toolset_example.cpp` 中的示例：

```cpp
// 获取压力数据
auto force_data = hand.getForce();

// 遍历每根手指
for (size_t finger = 0; finger < force_data.size(); finger++) {
    // 处理数据...
}
```

详细说明请参考 [API 参考文档](../docs/API-Reference.md#getforce)。

---

### Q5: 示例代码中的延时时间如何设置？

**A**: 延时时间取决于：
- 动作的复杂度
- 设置的速度
- 设备的响应时间

**建议**:
- 简单动作: 0.5-1 秒
- 复杂动作: 1-2 秒
- 连续动作: 根据实际效果调整

```cpp
// 快速动作
std::this_thread::sleep_for(std::chrono::milliseconds(500));

// 标准动作
std::this_thread::sleep_for(std::chrono::seconds(1));

// 慢速动作
std::this_thread::sleep_for(std::chrono::seconds(2));
```

---

## 下一步

- 阅读 [API 参考文档](../docs/API-Reference.md) 了解完整的 API
- 查看 [故障排查指南](../docs/TROUBLESHOOTING.md) 解决遇到的问题
- 参考 [常见问题解答](../docs/FAQ.md) 获取更多帮助
- 贡献您的示例代码到项目

如有问题，请参考 [故障排查指南](../docs/TROUBLESHOOTING.md) 或联系技术支持。
