#pragma once

#include <base_module.hpp>
#include <mlx90615.hpp>

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
            while (comm.has_data()) {
                auto frame = comm.get_data();
                // This module doesn't handle requests

                if (!frame.request) {
                    continue;
                }
                frame_temperature_s temperatures;

                temperatures.ambient_temperature =
                    mlx.get_ambient_temperature() * 10;
                temperatures.object_temperature =
                    mlx.get_object_temperature() * 10;

                comm.send(temperatures);
            }
        }
    };
} // namespace r2d2::temperature_sensor