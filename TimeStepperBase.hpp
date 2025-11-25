#ifndef TIMESTEPPER_BASE_HPP__
#define TIMESTEPPER_BASE_HPP__

#include "GridData.hpp"
#include "Operators.hpp"



template <typename T_, std::size_t NArraySize_, std::size_t NConstArraySize_>
class TimeStepperBase
{
protected:
	const std::array<GridData<T_>,NConstArraySize_> &const_vars;
	const Config<T_> &config;

public:
	TimeStepperBase(
		const std::array<GridData<T_>,NConstArraySize_> &i_const_vars,
		const Config<T_> &i_config
	)	:
		const_vars(i_const_vars),
		config(i_config)
	{
	}



public:
	/**
	 * General time integration interface to be called by individual time steppers
	 */
	virtual
	void time_integrate(
		std::array<GridData<T_>,NArraySize_> &io_U,	///< simulation state at t_n for input, output is t_n + dt
		Operators<T_> &i_ops,
		T_ i_dt		///< time step size
	) = 0;



public:
	/**
	 * Compute the time derivatives for a given state
	 */
	void df_dt(
		const std::array<GridData<T_>,NArraySize_> &i_U,
		const Operators<T_> &i_ops,
		std::array<GridData<T_>,NArraySize_> &o_U
	)
	{
		// Just return zero so far
		o_U[0].set_zero();
		o_U[1].set_zero();

		/**
		 * Hints:
		 *  - Gravitational accelleration is availabe via config.sim_g
		 *  - Average height field is available via config.sim_bavg
		 *    You need to use the absolute value of it for the average height!
		 *  - Make use of the operator overloading in GridData
		 */
	}


};

#endif
