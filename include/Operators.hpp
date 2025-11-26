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

		for (std::size_t i = 1; i < o.size-1; i++){
      o.data[i] = (i_d.data[i+1]-i_d.data[i-1])*0.5*discConfig->inv_dx;
    }

    // periodic boundaries
    o.data[0] = (i_d.data[1]-i_d.data[o.size-1])*0.5*discConfig->inv_dx;
    o.data[o.size-1] = (i_d.data[0]-i_d.data[o.size-2])*0.5*discConfig->inv_dx;

		//o.set_zero();
		return o;
	}
};

#endif
