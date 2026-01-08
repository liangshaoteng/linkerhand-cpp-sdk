# 测试说明

本目录包含 LinkerHand-CPP-SDK 的单元测试。

## 测试结构

```
tests/
├── unit/              # 单元测试
│   ├── test_Common.cpp          # Common.h 的测试
│   ├── test_RangeToArc.cpp     # RangeToArc.h 的测试
│   ├── test_IHand_Utils.cpp     # IHand 工具函数的测试
│   └── test_CanFrame.cpp        # CanFrame 的测试
├── CMakeLists.txt     # 测试构建配置
└── README.md          # 本文件
```

## 构建测试

### 方法一：使用 CMake 构建（推荐）

```bash
# 在项目根目录
mkdir build && cd build
cmake .. -DBUILD_TESTING=ON
make
```

### 方法二：禁用测试

如果不想构建测试：

```bash
cmake .. -DBUILD_TESTING=OFF
```

## 运行测试

### 运行所有测试

```bash
cd build
ctest
```

### 运行所有测试（显示详细输出）

```bash
cd build
ctest --output-on-failure
```

### 运行所有测试（更详细的信息）

```bash
cd build
ctest -V
```

### 运行特定测试

```bash
cd build
ctest -R test_Common
```

### 并行运行测试

```bash
cd build
ctest -j4
```

### 直接运行测试可执行文件

```bash
cd build
./test_Common
./test_RangeToArc
./test_IHand_Utils
./test_CanFrame
```

### 使用便捷目标

```bash
cd build
make run_tests
```

## 测试覆盖范围

### test_Common.cpp
- LINKER_HAND 枚举值测试
- HAND_TYPE 枚举值测试
- COMM_TYPE 枚举值测试
- Common 命名空间版本号测试
- 参数化测试

### test_RangeToArc.cpp
- `is_within_range()` 函数测试
- `scale_value()` 函数测试
- `should_skip_joint()` 函数测试
- `initialize_params()` 函数测试
- `range_to_arc()` 函数测试
- `arc_to_range()` 函数测试
- 往返转换测试
- 边界值测试
- 不同型号测试

### test_IHand_Utils.cpp
- `getSubVector()` 单参数版本测试
- `getSubVector()` 双参数版本测试
- `getCurrentTime()` 函数测试
- 边界情况测试

### test_CanFrame.cpp
- CANFrame 结构体测试
- 数据设置和读取测试
- 边界值测试
- ID 范围测试
- 数据复制测试

## 添加新测试

1. 在 `tests/unit/` 目录下创建新的测试文件，例如 `test_NewFeature.cpp`
2. 在 `tests/CMakeLists.txt` 的 `TEST_SOURCES` 列表中添加新文件
3. 如果测试需要链接 SDK 库，确保在 CMakeLists.txt 中添加相应的链接配置
4. 重新构建并运行测试

## 测试最佳实践

- 每个测试应该独立，不依赖其他测试
- 使用描述性的测试名称
- 测试正常情况、边界情况和错误情况
- 使用参数化测试测试多个输入值
- 保持测试代码简洁和可读

## 故障排查

### 找不到 Google Test

如果遇到 "Could not find gtest" 错误，CMake 会自动下载 Google Test。确保网络连接正常。

### 链接错误

如果遇到链接错误，检查：
1. SDK 库是否正确找到
2. 测试是否需要链接 SDK 库
3. 在 `tests/CMakeLists.txt` 中添加相应的链接配置

### 测试失败

如果测试失败：
1. 查看详细输出：`ctest --output-on-failure`
2. 直接运行测试可执行文件查看错误信息
3. 检查测试代码是否正确
4. 检查 SDK 库版本是否匹配

## 更多信息

详细的测试文档请参考：[测试文档](../docs/TESTING.md)

