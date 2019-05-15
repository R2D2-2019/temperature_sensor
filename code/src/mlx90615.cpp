#include <mlx90615.hpp>

namespace r2d2::temperature_sensor {
    uint16_t mlx90615::read_register(const uint8_t reg) {
        
    }

    mlx90615::mlx90615(): 
        i2c_bus(r2d2::i2c::i2c_bus_c::interface::interface_0, 50000) {
    } 

    float mlx90615::get_chip_temperature() {
        return 1;
    }

    float mlx90615::get_object_temperature() {
        return 1;
    }
}