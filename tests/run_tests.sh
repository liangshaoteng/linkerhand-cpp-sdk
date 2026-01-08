#!/bin/bash

# 测试运行脚本
# 用法: ./run_tests.sh [build_dir]

set -e

# 获取构建目录，默认为 ../build
BUILD_DIR=${1:-../build}

# 检查构建目录是否存在
if [ ! -d "$BUILD_DIR" ]; then
    echo "错误: 构建目录 '$BUILD_DIR' 不存在"
    echo "请先运行: mkdir build && cd build && cmake .. -DBUILD_TESTING=ON && make"
    exit 1
fi

# 进入构建目录
cd "$BUILD_DIR"

# 检查是否启用了测试
if [ ! -f "CMakeCache.txt" ]; then
    echo "错误: CMakeCache.txt 不存在，请先运行 cmake"
    exit 1
fi

# 运行测试
echo "运行所有测试..."
echo "=========================================="
ctest --output-on-failure

echo ""
echo "=========================================="
echo "测试完成！"

