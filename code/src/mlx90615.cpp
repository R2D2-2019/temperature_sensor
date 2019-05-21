#include <mlx90615.hpp>

namespace r2d2::temperature_sensor {
    uint16_t mlx90615::read_register(const uint8_t reg) {
        hwlib::wait_us(100);
        uint8_t raw_data[3] = {0, 0, 0};
        uint16_t data = 0;
        i2c_bus.read(MLX90615_SLAVE_ADDRESS, raw_data, 3, reg, 1);
        // Do nothing with raw_data[2]
        // discard PEC
        data = (raw_data[1] << 8) | raw_data[0];
        return data;
    }

    mlx90615::mlx90615(r2d2::i2c::i2c_bus_c &i2c_bus) : i2c_bus(i2c_bus) {
        id = read_register(MLX90615_ID_LOW);
        id |= static_cast<uint32_t>(read_register(MLX90615_ID_HIGH) << 16);
    }

    float mlx90615::get_ambient_temperature() {
        // To convert a read object temperature into degrees Celsius the equation is:
        // temperature *C = RAW IR DATA * SCALE - KELVIN
        return read_register(AMBIENT_TEMPERATURE) * SCALE - KELVIN;
    }

    float mlx90615::get_object_temperature() {
        // To convert a read object temperature into degrees Celsius the equation is:
        // temperature *C = RAW IR DATA * SCALE - KELVIN
        return read_register(OBJECT_TEMPERATURE) * SCALE - KELVIN;
    }

    uint32_t mlx90615::get_id() {
        return id;
    }
} // namespace r2d2::temperature_sensor