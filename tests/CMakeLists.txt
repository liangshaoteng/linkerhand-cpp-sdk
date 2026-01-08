# 测试配置
# 只有在启用测试时才构建测试

if(BUILD_TESTING)
    # 查找或下载 Google Test
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
        # GIT_REPOSITORY https://github.com/google/googletest.git
        # GIT_TAG v1.17.0
    )
    # 对于 Windows: 防止覆盖父项目的编译器/链接器设置
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    # 启用测试
    enable_testing()

    # 包含目录
    include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
        ${LINKER_HAND_INCLUDE_DIR}
    )

    # 测试可执行文件列表
    set(TEST_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/unit/test_Common.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/unit/test_RangeToArc.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/unit/test_IHand_Utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/unit/test_CanFrame.cpp
    )

    # 为每个测试文件创建可执行文件
    foreach(TEST_SOURCE ${TEST_SOURCES})
        # 获取测试名称（从路径中提取）
        get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)
        
        # 创建测试可执行文件
        add_executable(${TEST_NAME} ${TEST_SOURCE})
        
        # 链接库
        target_link_libraries(${TEST_NAME}
            PRIVATE
            gtest
            gtest_main
            pthread
        )
        
        # 如果测试需要 SDK 库，链接它
        # RangeToArc 函数在 SDK 库中实现
        if(TEST_SOURCE MATCHES "test_RangeToArc|test_LinkerHandApi|test_Hand")
            target_link_libraries(${TEST_NAME}
                PRIVATE
                ${LINKER_HAND_LIB}
            )
        endif()
        
        # 注册测试
        add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
        
        # 设置测试属性
        set_tests_properties(${TEST_NAME} PROPERTIES
            TIMEOUT 60
        )
    endforeach()

    # 创建运行所有测试的便捷目标
    add_custom_target(run_tests
        COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
        DEPENDS ${TEST_SOURCES}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Running all tests"
    )
endif()

