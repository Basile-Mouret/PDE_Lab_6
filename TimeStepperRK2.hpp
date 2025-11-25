#ifndef TIMESTEPPER_RK2_HPP__
#define TIMESTEPPER_RK2_HPP__


#include "TimeStepperBase.hpp"

template <typename T_, std::size_t NArraySize_, std::size_t NConstArraySize_>
class TimeStepperRK2:
	public TimeStepperBase<T_, NArraySize_, NConstArraySize_>
{
	const Config<T_> &config;

public:
	TimeStepperRK2(
		const std::array<GridData<T_>,NConstArraySize_> &i_const_vars,
		const Config<T_> &i_config
	)	:
		TimeStepperBase<T_, NArraySize_, NConstArraySize_>(i_const_vars, i_config),
		config(i_config)
	{
	}


	/**
	 * RK2 time integrator
	 */
	void time_integrate(
		std::array<GridData<T_>,NArraySize_> &io_U,	///< simulation state at t_n for input, output is t_n + dt
		Operators<T_> &i_ops,
		T_ i_dt		///< time step size
	)
	{
		std::array<GridData<T_>,NArraySize_> k1, k2, tmp;

		// setup GridData which we might use for the different stages of the PDE solver
		for (int i = 0; i < NArraySize_; i++)
		{
			k1[i].setup_like(io_U[i]);
			k2[i].setup_like(io_U[i]);
			tmp[i].setup_like(io_U[i]);
		}

		/*
		 * We do nothing here so far.
		 *
		 * You need to implement some time integration method here.
		 *
		 * It's recommended that you first implement a forward Euler
		 * (even if it's not stable, but you can test your algorithm)
		 * and then to implement a higher order method.
		 */

		/*
		 * Hints:
		 *
		 * 1) Wiki
		 * ==============================
		 * See, e.g.,
		 *   https://en.wikipedia.org/wiki/Runge%E2%80%93Kutta_methods#Second-order_methods_with_two_stages
		 * for more information
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
