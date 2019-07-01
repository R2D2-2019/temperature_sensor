#include <comm.hpp>
#include <cstring>
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
    r2d2::frame_display_8x8_character_s display_temperature_frame_amb;
    r2d2::frame_display_8x8_character_s display_temperature_frame_obj;
    display_temperature_frame_amb.x = 0;
    display_temperature_frame_amb.y = 0;
    display_temperature_frame_amb.red = 255;
    display_temperature_frame_amb.green = 0;
    display_temperature_frame_amb.blue = 0;
    char temprature_a[243] = {'A', '_', 't', 'e', 'm', 'p', ':', ' '}; // 8 char : x = 64

    display_temperature_frame_obj.x = 0;
    display_temperature_frame_obj.y = 8;
    display_temperature_frame_obj.red = 255;
    display_temperature_frame_obj.green = 0;
    display_temperature_frame_obj.blue = 0;
    char temprature_o[243] = {'O', '_', 't', 'e', 'm', 'p', ':', ' '}; // 8 char : x = 64

    strcpy(display_temperature_frame_amb.characters, temprature_a);
    comm.send(display_temperature_frame_amb);
    
    strcpy(display_temperature_frame_obj.characters, temprature_o);
    comm.send(display_temperature_frame_obj);
    while (true) {
        module.process();
        hwlib::wait_ms(1000);

    }

}