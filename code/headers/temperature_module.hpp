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
            bool has_send = false;
            while (comm.has_data()) {
                auto frame = comm.get_data();
                if (!frame.request && !has_send) {
                    continue;
                }
                frame_temperature_s temperatures{
                    mlx.get_id(),
                    static_cast<int16_t>(mlx.get_ambient_temperature() * 10),
                    static_cast<int16_t>(mlx.get_object_temperature() * 10)};
                comm.send(temperatures);
                has_send = true;
            }
        }
    };
} // namespace r2d2::temperature_sensor