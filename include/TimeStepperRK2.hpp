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

		// k1 = f(y_n)
		this->df_dt(io_U, i_ops, k1);

		// y_tmp = y_n + (dt/2) * k1
		for (int i = 0; i < NArraySize_; i++)
		{
			tmp[i] = io_U[i] + (i_dt * static_cast<T_>(0.5)) * k1[i];
		}

		// k2 = f(y_tmp)
		this->df_dt(tmp, i_ops, k2);

		// y_{n+1} = y_n + dt * k2
		for (int i = 0; i < NArraySize_; i++)
		{
			io_U[i] = io_U[i] + i_dt * k2[i];
		}
	}
};

#endif
