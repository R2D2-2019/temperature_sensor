#include <cstdint>
#include <i2c_bus.hpp>

#pragma once

namespace r2d2::temperature_sensor {
    class mlx90615 {
        // MLX90615 registers
        enum : uint8_t {
            AMBIENT_TEMPERATURE = 0x26,
            OBJECT_TEMPERATURE = 0x27,
            MLX90615_SLAVE_ADDRESS = 0x5B,
            MLX90615_ID_LOW = 0x1E,
            MLX90615_ID_HIGH = 0x1F
        };
        /**
         * Data sheet refers to multiplying the RAW IR data with a scale of 2.02f
         * */
        constexpr static float SCALE = 0.02f;
        /**
         * To convert a read object temperature into degrees Celsius the equation is:
         * temperature *C = RAW IR DATA * SCALE - KELVIN
         * */
        constexpr static float KELVIN = 273.15f;
        /**
         * I2C bus from R2D2
         * */
        r2d2::i2c::i2c_bus_c &i2c_bus;

        /**
         * Unique ID of the chip
         * Assigned in constructor
         * */
        uint32_t id;
        /**
         * Reads a register from the chip
         * 
         * @param uint8_t
         * @return uint16_t
         * */
        uint16_t read_register(const uint8_t reg);

    public:
        mlx90615(r2d2::i2c::i2c_bus_c &i2c_bus);
        /**
         * Gets the ambient temperature of the chip.
         * @return float
         * */
        float get_ambient_temperature();

        /**
         * Gets the temperature of the object the sensor is pointed at.
         * AKA 'object' temperature.
         * @return float
         * */
        float get_object_temperature();

        /**
         * Gets the ID of the chip.
         * */
        uint32_t get_id();
    };
} // namespace r2d2::temperature_sensor