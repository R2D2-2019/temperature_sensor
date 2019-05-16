#include <mlx90615.hpp>

namespace r2d2::temperature_sensor {
    uint16_t mlx90615::read_register(const uint8_t reg) {
        uint8_t raw_data[3];
        uint16_t data = 0;
        i2c_bus.read(MLX90615_SLAVE_ADDRESS, raw_data,
                     3); // TODO: repeated start i2c implementation
        data = (data | raw_data[1]) << 8 | raw_data[0];
        // Do nothing with raw_data[2]
        // discard PEC
        return data;
    }

    mlx90615::mlx90615()
        : i2c_bus(r2d2::i2c::i2c_bus_c::interface::interface_0, 50000) {
    }

    float mlx90615::get_chip_temperature() {
        return read_register(AMBIENT_TEMPERATURE) * 0.02 - 273.15;
    }

    float mlx90615::get_object_temperature() {
        return read_register(OBJECT_TEMPERATURE) * 0.02 - 273.15;
    }
} // namespace r2d2::temperature_sensor