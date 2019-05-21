#include <comm.hpp>
#include <temperature_module.hpp>

int main() {
    // kill the watchdog
    WDT->WDT_MR = WDT_MR_WDDIS;
    hwlib::wait_ms(1000);
    r2d2::comm_c comm;
    r2d2::i2c::i2c_bus_c i2c_bus(r2d2::i2c::i2c_bus_c::interface::interface_1,
                                 50'000);
    r2d2::temperature_sensor::mlx90615 mlx90615(i2c_bus);
    r2d2::temperature_sensor::module_c module(comm, mlx90615);

    while (true) {
        module.process();
        hwlib::cout << (int)(mlx90615.get_ambient_temperature() / 100) << hwlib::endl;
    }
}