#ifndef LINKERHAND_COMMON_H
#define LINKERHAND_COMMON_H

namespace linkerhand {

/**
 * @brief 灵巧手型号枚举
 */
enum class HandModel {
    O6,
    L6,
    L7,
    L10,
    L20,
    L21,
    L25
};

/**
 * @brief 手类型枚举（左手/右手）
 */
enum class HandType {
    LEFT = 0x28,
    RIGHT = 0x27
};

/**
 * @brief 通信类型枚举
 */
enum class CommType {
    CAN_0,
    CAN_1,
    MODBUS,
    ETHERCAT
};

/**
 * @brief 通用配置和版本信息
 */
namespace Common {
    inline float current_hand_version = 1.0;
}

} // namespace linkerhand

// 向后兼容的别名（保持旧代码可用）
using LINKER_HAND = linkerhand::HandModel;
constexpr auto O6 = linkerhand::HandModel::O6;
constexpr auto L6 = linkerhand::HandModel::L6;
constexpr auto L7 = linkerhand::HandModel::L7;
constexpr auto L10 = linkerhand::HandModel::L10;
constexpr auto L20 = linkerhand::HandModel::L20;
constexpr auto L21 = linkerhand::HandModel::L21;
constexpr auto L25 = linkerhand::HandModel::L25;

using HAND_TYPE = linkerhand::HandType;
constexpr auto LEFT = linkerhand::HandType::LEFT;
constexpr auto RIGHT = linkerhand::HandType::RIGHT;

using COMM_TYPE = linkerhand::CommType;
constexpr auto COMM_CAN_0 = linkerhand::CommType::CAN_0;
constexpr auto COMM_CAN_1 = linkerhand::CommType::CAN_1;
constexpr auto COMM_MODBUS = linkerhand::CommType::MODBUS;
constexpr auto COMM_ETHERCAT = linkerhand::CommType::ETHERCAT;

#define SEND_DEBUG 0
#define RECV_DEBUG 0

#endif // LINKERHAND_COMMON_H
