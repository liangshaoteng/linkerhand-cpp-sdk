#ifndef LINKERHAND_HAND_FACTORY_H
#define LINKERHAND_HAND_FACTORY_H

#include "IHand.h"
#include "LinkerHandL6.h"
#include "LinkerHandL7.h"
#include "LinkerHandL10.h"
#include "LinkerHandL20.h"
#include "LinkerHandL25.h"
#include "ModbusLinkerHandL10.h"
#include "Common.h"

namespace linkerhand {
namespace factory {

/**
 * @brief 手型号工厂类
 * 
 * 根据手型号、手类型和通信类型创建对应的手实例
 */
class HandFactory {
public:
    /**
     * @brief 创建手实例
     * @param type 手型号
     * @param handId 手ID（左手/右手）
     * @param commType 通信类型
     * @return 手实例的智能指针
     * @throws std::invalid_argument 如果参数无效
     */
    static std::unique_ptr<hand::IHand> createHand(LINKER_HAND type, uint32_t handId, COMM_TYPE commType) {

        if (handId != HAND_TYPE::LEFT && handId != HAND_TYPE::RIGHT)
        {
            throw std::invalid_argument("Unsupported hand type");
        }

        std::string canChannel;
        int baudrate = 1000000;

        switch (commType)
        {
        case COMM_TYPE::COMM_CAN_0:
            canChannel = "can0";
            break;
        case COMM_TYPE::COMM_CAN_1:
            canChannel = "can1";
            break;
        case COMM_TYPE::COMM_MODBUS:
            canChannel = "modbus";
            break;
        case COMM_TYPE::COMM_ETHERCAT:
            canChannel = "ethercat";
            break;
        default:
            throw std::invalid_argument("Unknown comm type");
            break;
        }

        if (canChannel == "can0" || canChannel == "can1" || canChannel == "ethercat") {
            switch (type) {
                case LINKER_HAND::O6:
                    return std::make_unique<LinkerHandL6::LinkerHand>(handId, canChannel, baudrate);
                    break;
                case LINKER_HAND::L6:
                    return std::make_unique<LinkerHandL6::LinkerHand>(handId, canChannel, baudrate);
                    break;
                case LINKER_HAND::L7:
                    return std::make_unique<LinkerHandL7::LinkerHand>(handId, canChannel, baudrate);
                    break;
                case LINKER_HAND::L10:
                    return std::make_unique<LinkerHandL10::LinkerHand>(handId, canChannel, baudrate);
                    break;
                case LINKER_HAND::L20:
                    return std::make_unique<LinkerHandL20::LinkerHand>(handId, canChannel, baudrate);
                    break;
                case LINKER_HAND::L21:
                    return std::make_unique<LinkerHandL25::LinkerHand>(handId, canChannel, baudrate, 1);
                    break;
                case LINKER_HAND::L25:
                    return std::make_unique<LinkerHandL25::LinkerHand>(handId, canChannel, baudrate, 0);
                    break;
                default:
                    throw std::invalid_argument("Unknown hand type");
            }
        } else if (canChannel == "modbus") {
        	#if USE_RMAN
            switch (type) {
                case LINKER_HAND::L10:
                    return std::make_unique<ModbusLinkerHandL10::LinkerHand>(handId);
                default:
                    throw std::invalid_argument("Unknown hand type");
                    break;
            }
            #else
            	throw std::runtime_error("ModBus support is disabled (USE_RMAN=0)");
			#endif
        }

        return nullptr;
    }
};

} // namespace factory
} // namespace linkerhand

// 向后兼容：在全局命名空间中提供别名
using HandFactory = linkerhand::factory::HandFactory;

#endif // LINKERHAND_HAND_FACTORY_H
