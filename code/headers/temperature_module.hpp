#pragma once

#include <base_module.hpp>
#include <mlx90615.hpp>
#include <cstring>

namespace r2d2::temperature_sensor {
    class module_c : public base_module_c {
    private:
        mlx90615 &mlx;

    public:
        module_c(base_comm_c &comm, mlx90615 &mlx)
            : base_module_c(comm), mlx(mlx) {
            comm.listen_for_frames({r2d2::frame_type::TEMPERATURE});
        }

        void process() override {
            r2d2::frame_display_8x8_character_s display_temperature_frame_ambient;
            display_temperature_frame_ambient.x = 64;
            display_temperature_frame_ambient.y = 0;
            display_temperature_frame_ambient.red = 255;
            display_temperature_frame_ambient.green = 0;
            display_temperature_frame_ambient.blue = 0;

            uint16_t a_temp = static_cast<int16_t>(mlx.get_ambient_temperature());
            char a_temp_arr[243] = {0};

            a_temp_arr[5] = (a_temp % 10) + 48;
            a_temp /= 10;
            a_temp_arr[4] = (a_temp % 10) + 48;
            a_temp /= 10;
            a_temp_arr[3] = ',';
            a_temp_arr[2] = (a_temp % 10) + 48;
            a_temp /= 10;
            a_temp_arr[1] = (a_temp % 10) + 48;
            a_temp /= 10;
            a_temp_arr[0] = (a_temp % 10) + 48;

            strcpy(display_temperature_frame_ambient.characters, a_temp_arr); 
            comm.send(display_temperature_frame_ambient);

            r2d2::frame_display_8x8_character_s display_temperature_frame_object;
            display_temperature_frame_object.x = 64;
            display_temperature_frame_object.y = 8;
            display_temperature_frame_object.red = 255;
            display_temperature_frame_object.green = 0;
            display_temperature_frame_object.blue = 0;

            uint16_t o_temp = static_cast<int16_t>(mlx.get_object_temperature());
            char o_temp_arr[243] = {0};

            o_temp_arr[5] = (o_temp % 10) + 48;
            o_temp /= 10;
            o_temp_arr[4] = (o_temp % 10) + 48;
            o_temp /= 10;
            o_temp_arr[3] = ',';
            o_temp_arr[2] = (o_temp % 10) + 48;
            o_temp /= 10;
            o_temp_arr[1] = (o_temp % 10) + 48;
            o_temp /= 10;
            o_temp_arr[0] = (o_temp % 10) + 48;

            strcpy(display_temperature_frame_object.characters, o_temp_arr); 
            comm.send(display_temperature_frame_object);

            /*
            bool has_send = false;
            while (comm.has_data()) {
                auto frame = comm.get_data();
                if (!frame.request && !has_send) {
                    continue;
                }

                frame_temperature_s temperatures{
                    mlx.get_id(),
                    static_cast<int16_t>(mlx.get_ambient_temperature()),
                    static_cast<int16_t>(mlx.get_object_temperature())};
                comm.send(temperatures); 
                has_send = true;

            }
            */

        }

         
    };
} // namespace r2d2::temperature_sensor