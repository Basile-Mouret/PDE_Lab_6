#ifndef OPERATORS_HPP__
#define OPERATORS_HPP__

#include "DiscConfig.hpp"
#include "GridData.hpp"



template <typename T = double>
class Operators
{
public:
	const DiscConfig<T> *discConfig;

	/*
	 * Default constructor doing nothing
	 */
	Operators()	:
		discConfig(nullptr)
	{
	}

	/*
	 * Setup constructor
	 */
	Operators(const DiscConfig<T> &i_discConfig)
	{
		setup(i_discConfig);
	}

	void setup(const DiscConfig<T> &i_discConfig)
	{
		discConfig = &i_discConfig;
	}


	/*
	 * Approximate
	 *  * first derivative with
	 *  * second order centered finite difference 
	 */
	GridData<T> diff1(const GridData<T> &i_d) const
	{
		GridData<T> o;
		o.setup_like(i_d);

		std::cout << "TODO" << std::endl;

		o.set_zero();
		return o;
	}
};

#endif
