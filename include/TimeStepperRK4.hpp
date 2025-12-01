#ifndef TIMESTEPPER_RK4_HPP__
#define TIMESTEPPER_RK4_HPP__


#include "TimeStepperBase.hpp"

template<typename T_, std::size_t NArraySize_, std::size_t NConstArraySize_>
class TimeStepperRK4 :
        public TimeStepperBase<T_, NArraySize_, NConstArraySize_> {
    const Config<T_> &config;

public:
    TimeStepperRK4(
            const std::array<GridData<T_>, NConstArraySize_> &i_const_vars,
            const Config<T_> &i_config
    ) :
            TimeStepperBase<T_, NArraySize_, NConstArraySize_>(i_const_vars, i_config),
            config(i_config) {
    }


    /**
     * RK4 time integrator which updates
     */
    void time_integrate(
            std::array<GridData<T_>, NArraySize_> &io_U,    ///< simulation state at t_n for input, output is t_n + dt
            Operators<T_> &i_ops,
            T_ i_dt        ///< time step size
    ) {
        std::array<GridData<T_>, NArraySize_> k1, k2, k3, k4, tmp;

        // setup GridData which we might use for the different stages of the PDE solver
        for (int i = 0; i < NArraySize_; i++) {
            k1[i].setup_like(io_U[i]);
            k2[i].setup_like(io_U[i]);
            k3[i].setup_like(io_U[i]);
            k4[i].setup_like(io_U[i]);
            tmp[i].setup_like(io_U[i]);
        }

        /*
         * We do nothing here so far.
         */

        /*
         * Hints:
         *
         * 1) Wiki
         * ==============================
         * See, e.g.,
         *   https://en.wikipedia.org/wiki/Runge%E2%80%93Kutta_methods#The_Runge%E2%80%93Kutta_method
         * for more information on 4th order (classical) Runge Kutta method
         *
         * Here, y = io_U
         *
         *
         * 2) Time Tendencies:
         * ==============================
         * You can compute
         *   k=df(y)/dt
         * by calling
         *
         * this->df_dt(y, i_ops, k);
         *
         * 3) Compute stage solution
         * ==============================
         * ...
         */
    }
};

#endif
