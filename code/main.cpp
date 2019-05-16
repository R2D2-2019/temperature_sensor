#include <mlx90615.hpp>

int main(void) {
    // kill the watchdog
    WDT->WDT_MR = WDT_MR_WDDIS;
    hwlib::wait_ms(1000);
    r2d2::temperature_sensor::mlx90615 temp_sensor;
    while (true) {
        temp_sensor.get_chip_temperature();
        // hwlib::cout << "Object: " <<
        // static_cast<int>(temp_sensor.get_object_temperature()) << '\n';
        hwlib::wait_ms(1000);
    }
}