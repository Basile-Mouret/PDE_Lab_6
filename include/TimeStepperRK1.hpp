#ifndef TIMESTEPPER_RK1_HPP__
#define TIMESTEPPER_RK1_HPP__


#include "TimeStepperBase.hpp"

template <typename T_, std::size_t NArraySize_, std::size_t NConstArraySize_>
class TimeStepperRK1:
	public TimeStepperBase<T_, NArraySize_, NConstArraySize_>
{
	const Config<T_> &config;

public:
	TimeStepperRK1(
		const std::array<GridData<T_>,NConstArraySize_> &i_const_vars,
		const Config<T_> &i_config
	)	:
		TimeStepperBase<T_, NArraySize_, NConstArraySize_>(i_const_vars, i_config),
		config(i_config)
	{
	}


	/**
	 * Forward Euler
	 */
	void time_integrate(
		std::array<GridData<T_>,NArraySize_> &io_U,	///< simulation state at t_n for input, output is t_n + dt
		Operators<T_> &i_ops,
		T_ i_dt		///< time step size
	)
	{
		// Storage for first stage
		std::array<GridData<T_>,NArraySize_> k1;

		for (int i = 0; i < NArraySize_; i++)
			k1[i].setup_like(io_U[i]);
      
    this->df_dt(io_U, i_ops, k1);

		for (int i = 0; i < NArraySize_; i++)
		  io_U[i] = io_U[i] + i_dt*k1[i];

		/*
		 * You need to implement some time integration method here.
		 */

		/*
		 * Hints:
		 *
		 * 1) Wiki
		 * ==============================
		 * See, e.g.,
		 *   https://en.wikipedia.org/wiki/Runge%E2%80%93Kutta_methods#Explicit_Runge%E2%80%93Kutta_methods
		 * for more information about the explicit Euler method
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
		 * You can compute
		 *   y_new = y + dt*k1
		 * using
		 *
		 * for (int i = 0; i < NArraySize_; i++)
		 *    y_new[i] = y[i] + dt*k1[i];
		 *
		 * This iterates over all variables you have (height, velocity) and
		 * updates them according to the Runge-Kutta method for a single stage.
		 */
	}
};

#endif
