#include <cstdint>
#include <i2c_bus.hpp>

#pragma once

namespace r2d2::temperature_sensor {
    class mlx90615 {
        enum mlx_registers : uint8_t {
            EMISSIVITY              = 0x13,
            AMBIENT_TEMPERATURE     = 0x26,
            OBJECT_TEMPERATURE      = 0x27,
            MLX90615_SLAVE_ADDRESS  = 0x5B
        };

        r2d2::i2c::i2c_bus_c i2c_bus;

        uint16_t read_register(const uint8_t reg);

    public:
        mlx90615();
        /**
         * Gets the temperature of the chip.
         * AKA 'ambient' temperature.
         * @return float
         * */
        float get_chip_temperature();

        /**
         * Gets the temperature of the object the sensor is pointed at.
         * AKA 'object' temperature.
         * @return float
         * */
        float get_object_temperature();
    };
} // namespace r2d2::temperature_sensor